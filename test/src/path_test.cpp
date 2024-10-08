#include <unordered_set>
#include "os.hpp"
#include "gtest/gtest.h"

namespace path = os::path;
using CopyOption = os::path::CopyOption;
using Traversal = os::path::TraversalOption;

std::string test_path = path::joinPath(path::sourcePath(), "../test_path");
std::string temp_path = path::joinPath(test_path, "temp");

TEST(isValidFilenameChar, check)
{
    #if defined(_WIN32)
        EXPECT_EQ(path::isValidFilenameChar('<'), false);
        EXPECT_EQ(path::isValidFilenameChar('>'), false);
        EXPECT_EQ(path::isValidFilenameChar('|'), false);
        EXPECT_EQ(path::isValidFilenameChar(':'), false);
        EXPECT_EQ(path::isValidFilenameChar('\"'), false);
        EXPECT_EQ(path::isValidFilenameChar('\\'), false);
        EXPECT_EQ(path::isValidFilenameChar('/'), false);
        EXPECT_EQ(path::isValidFilenameChar('?'), false);
        EXPECT_EQ(path::isValidFilenameChar('*'), false);
    #elif defined(__linux__)
        EXPECT_EQ(path::isValidFilenameChar('/'), false);
    #endif
    
    EXPECT_EQ(path::isValidFilenameChar('t'), true);
}

TEST(hasFileExtension, check)
{
    EXPECT_EQ(path::hasFileExtension("test.txt"), true);
    EXPECT_EQ(path::hasFileExtension(".git"), false);
    EXPECT_EQ(path::hasFileExtension(".txt"), false);
    EXPECT_EQ(path::hasFileExtension("a.txt"), true);
    EXPECT_EQ(path::hasFileExtension("/at.txt"), true);
    EXPECT_EQ(path::hasFileExtension("/.txt"), false);
    EXPECT_EQ(path::hasFileExtension("/test.txt/"), true);
    EXPECT_EQ(path::hasFileExtension("test..txt"), true);
    EXPECT_EQ(path::hasFileExtension("test.txt//"), true);
    EXPECT_EQ(path::hasFileExtension("test.num.txt"), true);
    EXPECT_EQ(path::hasFileExtension("test..num..txt"), true);
    EXPECT_EQ(path::hasFileExtension("sandbox/file.txt"), true);
    EXPECT_EQ(path::hasFileExtension("foo/bar/koo"), false);
    EXPECT_EQ(path::hasFileExtension("foo/bar/koo.cpp"), true);
    EXPECT_EQ(path::hasFileExtension("foo/bar/koo.cpp//"), true);
    EXPECT_EQ(path::hasFileExtension("foo/bar/file."), false);
}

TEST(fileExtension, getExtension)
{
    EXPECT_EQ(path::fileExtension("test.txt"), "txt");
    EXPECT_EQ(path::fileExtension(".git"), "");
    EXPECT_EQ(path::fileExtension(".txt"), "");
    EXPECT_EQ(path::fileExtension("a.txt"), "txt");
    EXPECT_EQ(path::fileExtension("/at.txt"), "txt");
    EXPECT_EQ(path::fileExtension("/.txt"), "");
    EXPECT_EQ(path::fileExtension("/test.txt/"), "txt");
    EXPECT_EQ(path::fileExtension("test..txt"), "txt");
    EXPECT_EQ(path::fileExtension("test.txt//"), "txt");
    EXPECT_EQ(path::fileExtension("test.num.txt"), "txt");
    EXPECT_EQ(path::fileExtension("test..num..txt"), "txt");
    EXPECT_EQ(path::fileExtension("sandbox/file.txt"), "txt");
    EXPECT_EQ(path::fileExtension("foo/bar/koo"), "");
    EXPECT_EQ(path::fileExtension("foo/bar/koo.cpp"), "cpp");
    EXPECT_EQ(path::fileExtension("foo/bar/koo.cpp//"), "cpp");
    EXPECT_EQ(path::fileExtension("foo/bar/file."), "");
}

TEST(appendFileExtension, join)
{
    EXPECT_EQ(path::appendFileExtension("tt", "json"), "tt.json");
    EXPECT_EQ(path::appendFileExtension("hello.", "json"), "hello..json");
    EXPECT_EQ(path::appendFileExtension("hello..", "json"), "hello...json");
    EXPECT_EQ(path::appendFileExtension("hello", ".json"), "hello.json");
    EXPECT_EQ(path::appendFileExtension("hello", "..json"), "hello.json");
    EXPECT_EQ(path::appendFileExtension("hello.", ".json"), "hello..json");
    EXPECT_EQ(path::appendFileExtension("hello.json", "json"), "hello.json");
    EXPECT_EQ(path::appendFileExtension("hello.json", ".json"), "hello.json");
    EXPECT_EQ(path::appendFileExtension("hello.json", "json", true), "hello.json.json");
    EXPECT_EQ(path::appendFileExtension("hello.json", ".json", true), "hello.json.json");
    EXPECT_EQ(path::appendFileExtension("hello.json", ".jtson"), "hello.json.jtson");
}

TEST(joinPath, edge_case)
{
    EXPECT_EQ(path::joinPath("", ""), "");
    EXPECT_EQ(path::joinPath("a/b/c", ""), path::normalizePath("a/b/c"));
    EXPECT_EQ(path::joinPath("a/b/c/", ""), path::normalizePath("a/b/c/"));
    EXPECT_EQ(path::joinPath("", "a/b/c"), path::normalizePath("a/b/c"));
    EXPECT_EQ(path::joinPath("", "a/b/c/"), path::normalizePath("a/b/c/"));
    EXPECT_EQ(path::joinPath({}), "");
    EXPECT_EQ(path::joinPath({"", "", "", ""}), "");
    EXPECT_EQ(path::joinPath({"", "a/b", "", "c/d"}), path::normalizePath("a/b/c/d"));
    EXPECT_EQ(path::joinPath({"", "a/b", "", "c/d/"}), path::normalizePath("a/b/c/d/"));
}

TEST(joinPath, concatenate)
{
    EXPECT_EQ(path::joinPath("a/b/c", "d/e"), path::normalizePath("a/b/c/d/e"));
    EXPECT_EQ(path::joinPath("a/b/c", "d/e/"), path::normalizePath("a/b/c/d/e/"));
    EXPECT_EQ(path::joinPath("a/b/c/", "d/e"), path::normalizePath("a/b/c/d/e"));
    EXPECT_EQ(path::joinPath({"a/b/c"}), path::normalizePath("a/b/c"));
    EXPECT_EQ(path::joinPath({"a/b/c/"}), path::normalizePath("a/b/c/"));
    EXPECT_EQ(path::joinPath({"a/b/c", "d/e"}), path::normalizePath("a/b/c/d/e"));
    EXPECT_EQ(path::joinPath({"a/b/c", "d/e/"}), path::normalizePath("a/b/c/d/e/"));
    EXPECT_EQ(path::joinPath({"a/b/c/d", "e", "f", "g/h"}), path::normalizePath("a/b/c/d/e/f/g/h"));
    EXPECT_EQ(path::joinPath({"a/b/c/d", "e", "f", "g/h/"}), path::normalizePath("a/b/c/d/e/f/g/h/"));
    EXPECT_EQ(path::joinPath({"a/b/c/d", "e/", "f/", "g/h/"}), path::normalizePath("a/b/c/d/e/f/g/h/"));
}

TEST(joinPath, end_separator)
{
    EXPECT_EQ(path::joinPath("a/b/c/d", ".."), path::normalizePath("a/b/c"));
    EXPECT_EQ(path::joinPath("a/b/c/d", "../"), path::normalizePath("a/b/c/"));
    EXPECT_EQ(path::joinPath("a/b/c/d", "../.."), path::normalizePath("a/b"));
    EXPECT_EQ(path::joinPath("a/b/c/d", "../../"), path::normalizePath("a/b/"));
    EXPECT_EQ(path::joinPath("a/b/c/d", "."), path::normalizePath("a/b/c/d"));
    EXPECT_EQ(path::joinPath("a/b/c/d", "./"), path::normalizePath("a/b/c/d/"));
    EXPECT_EQ(path::joinPath("a/b/c/d/..", ""), path::normalizePath("a/b/c"));
    EXPECT_EQ(path::joinPath("a/b/c/d/../", ""), path::normalizePath("a/b/c/"));
    EXPECT_EQ(path::joinPath("a/b/c/d/../../e", ""), path::normalizePath("a/b/e"));
    EXPECT_EQ(path::joinPath("a/b/c/d/../../e/", ""), path::normalizePath("a/b/e/"));
    EXPECT_EQ(path::joinPath("", "a/b/c/d/../../e"), path::normalizePath("a/b/e"));
    EXPECT_EQ(path::joinPath("", "a/b/c/d/../../e/"), path::normalizePath("a/b/e/"));
    EXPECT_EQ(path::joinPath({"a/b/c/d/../.."}), path::normalizePath("a/b"));
    EXPECT_EQ(path::joinPath({"a/b/c/d/../../"}), path::normalizePath("a/b/"));
    EXPECT_EQ(path::joinPath({"a/b/c/d/../../", "e/f/..", "g"}), path::normalizePath("a/b/e/g"));
    EXPECT_EQ(path::joinPath({"a/b/c/d/../../", "e/f/..", "g/"}), path::normalizePath("a/b/e/g/"));
}

TEST(hasSameContent, not_exist)
{
    EXPECT_THROW(path::hasSameContent("__wassup__.txt", "__hello.txt"), std::exception);
    EXPECT_THROW(path::hasSameContent(path::joinPath(test_path, "same3/shaggy.txt"), "__wassup__.txt"), std::exception);
    EXPECT_THROW(path::hasSameContent("__wassup.txt", path::joinPath(test_path, "same3/shaggy.txt")), std::exception);
}

TEST(hasSameContent, not_same_type)
{
    std::string test_suite_path = path::joinPath(test_path, "hasSameContent");
    EXPECT_THROW(path::hasSameContent(path::joinPath(test_suite_path, "same3"), path::joinPath(test_suite_path, "same3/shaggy.txt")), std::exception);
    EXPECT_THROW(path::hasSameContent(path::joinPath(test_suite_path, "same3/shaggy.txt"), path::joinPath(test_suite_path, "same3")), std::exception);
}

TEST(hasSameContent, directories)
{
    std::string test_suite_path = path::joinPath(test_path, "hasSameContent");
    ASSERT_TRUE(path::hasSameContent(path::joinPath(test_suite_path, "same1"), path::joinPath(test_suite_path, "same2")));
    ASSERT_FALSE(path::hasSameContent(path::joinPath(test_suite_path, "same1"), path::joinPath(test_suite_path, "same3")));
}

TEST(hasSameContent, files)
{
    std::string test_suite_path = path::joinPath(test_path, "hasSameContent");
    ASSERT_TRUE(path::hasSameContent(path::joinPath(test_suite_path, "same3/shaggy.txt"), path::joinPath(test_suite_path, "same3/shaggy1.txt")));
    ASSERT_FALSE(path::hasSameContent(path::joinPath(test_suite_path, "same3/sand1.txt"), path::joinPath(test_suite_path, "same3/shaggy.txt")));
}

TEST(isDirectoryString, working)
{
    ASSERT_FALSE(path::isDirectoryString("hello"));
    ASSERT_TRUE(path::isDirectoryString("hello/"));
    ASSERT_TRUE(path::isDirectoryString("hello/int//"));
}

TEST(isDirectoryString, empty_string)
{
    ASSERT_FALSE(path::isDirectoryString(""));
    ASSERT_TRUE(path::isDirectoryString("/"));
}

TEST(copy, copy_with_directory)
{
    std::string test_suite_path = path::joinPath(test_path, "copy");
    std::string from = path::joinPath(test_suite_path, "source");
    std::string to = path::joinPath(test_suite_path, "destination");

    ASSERT_TRUE(path::isEmpty(to));

    path::copy(from, to);

    ASSERT_TRUE(path::exists(path::joinPath(to, "source")));

    path::remove(to + path::directorySeparator());
}

TEST(copy, copy_with_only_subdirectory)
{
    std::string test_suite_path = path::joinPath(test_path, "copy");
    std::string from = path::joinPath(test_suite_path, "source");
    std::string to = path::joinPath(test_suite_path, "destination");

    ASSERT_TRUE(path::isEmpty(to));

    path::copy(from + path::directorySeparator(), to);

    ASSERT_TRUE(path::hasSameContent(from, to));

    path::remove(to + path::directorySeparator());
}

TEST(copy, directory_to_file)
{
    std::string test_suite_path = path::joinPath(test_path, "copy");
    std::string from = path::joinPath(test_suite_path, "source");
    std::string to = path::joinPath(test_suite_path, "destination");
    std::string temp_file = path::joinPath(to, "test.txt");

    path::createFile(temp_file, "wassup", CopyOption::OverwriteExisting);

    EXPECT_THROW(path::copy(from, temp_file), std::runtime_error);

    path::remove(to + path::directorySeparator());
}

TEST(copy, skip_existing)
{
    std::string test_suite_path = path::joinPath(test_path, "copy");
    std::string from = path::joinPath(test_suite_path, "source");
    std::string to = path::joinPath(test_suite_path, "destination");
    std::string compare_file = path::joinPath(test_suite_path, "temp/compare.txt");

    path::remove(to + path::directorySeparator());

    path::copy(path::joinPath(from, "test1.txt"), to);

    ASSERT_TRUE(path::exists(path::joinPath(to, "test1.txt")));

    path::createFile(compare_file, "hello", CopyOption::OverwriteExisting);
    path::createFile(path::joinPath(to, "test1.txt"), "hello", CopyOption::OverwriteExisting);

    path::copy(from + path::directorySeparator(), to, CopyOption::SkipExisting);

    ASSERT_TRUE(path::hasSameContent(from, to));
    ASSERT_TRUE(path::hasSameContent(path::joinPath(to, "test1.txt"), compare_file));

    path::remove(to + path::directorySeparator());
}

TEST(copy, overwrite_existing)
{
    std::string test_suite_path = path::joinPath(test_path, "copy");
    std::string from = path::joinPath(test_suite_path, "source");
    std::string to = path::joinPath(test_suite_path, "destination");
    std::string compare_file = path::joinPath(test_suite_path, "temp/compare.txt");

    path::remove(to + path::directorySeparator());

    path::copy(path::joinPath(from, "test1.txt"), to);

    ASSERT_TRUE(path::exists(path::joinPath(to, "test1.txt")));

    path::createFile(compare_file, "hello", CopyOption::OverwriteExisting);
    path::createFile(path::joinPath(to, "test1.txt"), "hello", CopyOption::OverwriteExisting);

    path::copy(from + path::directorySeparator(), to, CopyOption::OverwriteExisting);

    ASSERT_TRUE(path::hasSameContent(from, to));
    ASSERT_FALSE(path::hasSameContent(path::joinPath(to, "test1.txt"), compare_file));

    path::remove(to + path::directorySeparator());
}

TEST(copy, overwrite_all)
{
    std::string test_suite_path = path::joinPath(test_path, "copy");
    std::string from = path::joinPath(test_suite_path, "source");
    std::string to = path::joinPath(test_suite_path, "destination");
    std::string compare_file = path::joinPath(test_suite_path, "temp/compare.txt");

    path::remove(to + path::directorySeparator());

    path::copy(compare_file, to);

    ASSERT_TRUE(path::exists(path::joinPath(to, "compare.txt")));

    path::copy(from + path::directorySeparator(), to, CopyOption::OverwriteAll);

    ASSERT_FALSE(path::exists(path::joinPath(to, "compare.txt")));

    path::remove(to + path::directorySeparator());
}

TEST(copy, non_recursive)
{
    std::string test_suite_path = path::joinPath(test_path, "copy");
    std::string from = path::joinPath(test_suite_path, "source");
    std::string to = path::joinPath(test_suite_path, "destination");

    ASSERT_FALSE(path::exists(path::joinPath(to, "source")));

    path::copy(from, to, Traversal::NonRecursive);

    ASSERT_TRUE(path::exists(path::joinPath(to, "source")));
    ASSERT_TRUE(path::isEmpty(path::joinPath(to, "source")));

    path::remove(to + path::directorySeparator());
}

TEST(copy, non_recursive_with_trailing_separator)
{
    std::string test_suite_path = path::joinPath(test_path, "copy");
    std::string from = path::joinPath(test_suite_path, "source");
    std::string to = path::joinPath(test_suite_path, "destination");

    ASSERT_FALSE(path::exists(path::joinPath(to, "source")));

    path::copy(from + path::directorySeparator(), to, Traversal::NonRecursive);

    ASSERT_FALSE(path::isEmpty(to));
    ASSERT_TRUE(path::exists(path::joinPath(to, "folder1")));
    ASSERT_TRUE(path::exists(path::joinPath(to, "test1.txt")));
    ASSERT_TRUE(path::exists(path::joinPath(to, "test2.txt")));
    ASSERT_TRUE(path::isEmpty(path::joinPath(to, "folder1")));

    path::remove(to + path::directorySeparator());
}

TEST(copy, custom_paths)
{
    std::string test_suite_path = path::joinPath(test_path, "copy");
    std::string from = path::joinPath(test_suite_path, "source");
    std::string to = path::joinPath(test_suite_path, "destination");
    std::set<std::string> paths = {path::joinPath(from, "folder1"), path::joinPath(from, "test1.txt"), path::joinPath(from, "folder1/test1.txt")};

    path::remove(to + path::directorySeparator());

    path::copy(from, paths, to, CopyOption::OverwriteExisting);

    ASSERT_TRUE(path::exists(path::joinPath(to, "folder1")));
    ASSERT_TRUE(path::exists(path::joinPath(to, "test1.txt")));
    ASSERT_TRUE(path::exists(path::joinPath(to, "folder1/test1.txt")));

    path::remove(to + path::directorySeparator());
}

TEST(copy, custom_paths_no_parent)
{
    std::string test_suite_path = path::joinPath(test_path, "copy");
    std::string from = path::joinPath(test_suite_path, "source");
    std::string to = path::joinPath(test_suite_path, "destination");
    std::set<std::string> paths = {path::joinPath(from, "test1.txt"), path::joinPath(from, "folder1/test1.txt")};

    path::remove(to + path::directorySeparator());

    path::copy(from, paths, to, CopyOption::OverwriteExisting);

    ASSERT_TRUE(path::exists(path::joinPath(to, "folder1")));
    ASSERT_TRUE(path::exists(path::joinPath(to, "test1.txt")));
    ASSERT_TRUE(path::exists(path::joinPath(to, "folder1/test1.txt")));

    path::remove(to + path::directorySeparator());
}

TEST(move, working)
{
    std::string test_suite_path = path::joinPath(test_path, "copy");
    std::string from = path::joinPath(test_suite_path, "source");
    std::string to = path::joinPath(test_suite_path, "destination");

    ASSERT_TRUE(path::isEmpty(to));
    ASSERT_FALSE(path::isEmpty(from));

    path::move(from + path::directorySeparator(), to);

    ASSERT_TRUE(path::isEmpty(from));

    path::move(to + path::directorySeparator(), from);

    ASSERT_TRUE(path::isEmpty(to));
}

TEST(move, custom_paths)
{
    std::string test_suite_path = path::joinPath(test_path, "copy");
    std::string from = path::joinPath(test_suite_path, "source");
    std::string to = path::joinPath(test_suite_path, "destination");
    std::set<std::string> paths = {path::joinPath(from, "folder1"), path::joinPath(from, "test1.txt"), path::joinPath(from, "folder1/test1.txt")};

    path::remove(to + path::directorySeparator());

    path::move(from, paths, to, CopyOption::OverwriteExisting);

    ASSERT_TRUE(path::exists(path::joinPath(to, "folder1")));
    ASSERT_TRUE(path::exists(path::joinPath(to, "test1.txt")));
    ASSERT_TRUE(path::exists(path::joinPath(to, "folder1/test1.txt")));

    ASSERT_TRUE(path::exists(path::joinPath(from, "folder1")));
    ASSERT_FALSE(path::exists(path::joinPath(from, "folder1/test1.txt")));
    ASSERT_FALSE(path::exists(path::joinPath(from, "test1.txt")));

    path::copy(path::joinPath(test_suite_path, "source_copy") + path::directorySeparator(), from, CopyOption::OverwriteAll);

    path::remove(to + path::directorySeparator());
}