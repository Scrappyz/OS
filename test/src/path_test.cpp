#include <unordered_set>
#include "os.hpp"
#include "gtest/gtest.h"

namespace path = os::path;

std::string test_path = path::joinPath(path::sourcePath(), "../test_path");
std::string temp_path = path::joinPath(test_path, "temp");

std::unordered_set<std::filesystem::path> getPathContent(const std::filesystem::path& path, bool include_parent = false)
{
    std::unordered_set<std::filesystem::path> result;
    std::filesystem::path relative_to = include_parent ? path.parent_path() : path;

    for(const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
        result.insert(path::relativePath(entry.path(), relative_to));
    }

    return result;
}

bool testCopy(const std::filesystem::path& from, std::filesystem::path to) // good
{
    path::copy(from, to, path::CopyOption::SkipExisting);

    std::unordered_set<std::filesystem::path> c1 = getPathContent(from, !from.filename().empty());
    std::unordered_set<std::filesystem::path> c2 = getPathContent(to, false);

    bool result = true;
    for(const auto& i : c1) {
        if(c2.count(i) < 1) {
            result = false;
            continue;
        }
        path::remove(path::joinPath(to, i));
    }

    if(!from.filename().empty()) {
        path::remove(path::joinPath(to, from.filename()));
    }

    return result;
}

TEST(isValidFilenameChar, check)
{
    EXPECT_EQ(path::isValidFilenameChar('<'), false);
    EXPECT_EQ(path::isValidFilenameChar('>'), false);
    EXPECT_EQ(path::isValidFilenameChar('|'), false);
    EXPECT_EQ(path::isValidFilenameChar(':'), false);
    EXPECT_EQ(path::isValidFilenameChar('\"'), false);
    EXPECT_EQ(path::isValidFilenameChar('\\'), false);
    EXPECT_EQ(path::isValidFilenameChar('/'), false);
    EXPECT_EQ(path::isValidFilenameChar('?'), false);
    EXPECT_EQ(path::isValidFilenameChar('*'), false);
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
    EXPECT_EQ(path::joinPath("a/b/c", ""), "a\\b\\c");
    EXPECT_EQ(path::joinPath("a/b/c/", ""), "a\\b\\c\\");
    EXPECT_EQ(path::joinPath("", "a/b/c"), "a\\b\\c");
    EXPECT_EQ(path::joinPath("", "a/b/c/"), "a\\b\\c\\");
}

TEST(joinPath, concatenate)
{
    EXPECT_EQ(path::joinPath("a/b/c", "d/e"), "a\\b\\c\\d\\e");
    EXPECT_EQ(path::joinPath("a/b/c", "d/e/"), "a\\b\\c\\d\\e\\");
    EXPECT_EQ(path::joinPath("a/b/c/", "d/e"), "a\\b\\c\\d\\e");
}

TEST(joinPath, end_separator)
{
    EXPECT_EQ(path::joinPath("a/b/c/d", ".."), "a\\b\\c");
    EXPECT_EQ(path::joinPath("a/b/c/d", "../"), "a\\b\\c\\");
    EXPECT_EQ(path::joinPath("a/b/c/d", "../.."), "a\\b");
    EXPECT_EQ(path::joinPath("a/b/c/d", "../../"), "a\\b\\");
    EXPECT_EQ(path::joinPath("a/b/c/d", "."), "a\\b\\c\\d");
    EXPECT_EQ(path::joinPath("a/b/c/d", "./"), "a\\b\\c\\d\\");
    EXPECT_EQ(path::joinPath("a/b/c/d/..", ""), "a\\b\\c");
    EXPECT_EQ(path::joinPath("a/b/c/d/../", ""), "a\\b\\c\\");
    EXPECT_EQ(path::joinPath("a/b/c/d/../../e", ""), "a\\b\\e");
    EXPECT_EQ(path::joinPath("a/b/c/d/../../e/", ""), "a\\b\\e\\");
    EXPECT_EQ(path::joinPath("", "a/b/c/d/../../e"), "a\\b\\e");
    EXPECT_EQ(path::joinPath("", "a/b/c/d/../../e/"), "a\\b\\e\\");
}

TEST(joins, edge_case)
{
    EXPECT_EQ(path::joinPath({}), "");
    EXPECT_EQ(path::joinPath({"", "", "", ""}), "");
    EXPECT_EQ(path::joinPath({"", "a/b", "", "c/d"}), "a\\b\\c\\d");
    EXPECT_EQ(path::joinPath({"", "a/b", "", "c/d/"}), "a\\b\\c\\d\\");
}

TEST(joins, concatenate)
{
    EXPECT_EQ(path::joinPath({"a/b/c"}), "a\\b\\c");
    EXPECT_EQ(path::joinPath({"a/b/c/"}), "a\\b\\c\\");
    EXPECT_EQ(path::joinPath({"a/b/c", "d/e"}), "a\\b\\c\\d\\e");
    EXPECT_EQ(path::joinPath({"a/b/c", "d/e/"}), "a\\b\\c\\d\\e\\");
    EXPECT_EQ(path::joinPath({"a/b/c/d", "e", "f", "g/h"}), "a\\b\\c\\d\\e\\f\\g\\h");
    EXPECT_EQ(path::joinPath({"a/b/c/d", "e", "f", "g/h/"}), "a\\b\\c\\d\\e\\f\\g\\h\\");
    EXPECT_EQ(path::joinPath({"a/b/c/d", "e/", "f/", "g/h/"}), "a\\b\\c\\d\\e\\f\\g\\h\\");
}

TEST(joins, end_separator)
{
    EXPECT_EQ(path::joinPath({"a/b/c/d/../.."}), "a\\b");
    EXPECT_EQ(path::joinPath({"a/b/c/d/../../"}), "a\\b\\");
    EXPECT_EQ(path::joinPath({"a/b/c/d/../../", "e/f/..", "g"}), "a\\b\\e\\g");
    EXPECT_EQ(path::joinPath({"a/b/c/d/../../", "e/f/..", "g/"}), "a\\b\\e\\g\\");
}

TEST(hasSameContent, not_exist)
{
    EXPECT_THROW(path::hasSameContent("__wassup__.txt", "__hello.txt"), std::exception);
    EXPECT_THROW(path::hasSameContent(path::joinPath(test_path, "same3/shaggy.txt"), "__wassup__.txt"), std::exception);
    EXPECT_THROW(path::hasSameContent("__wassup.txt", path::joinPath(test_path, "same3/shaggy.txt")), std::exception);
}

TEST(hasSameContent, not_same_type)
{
    EXPECT_THROW(path::hasSameContent(path::joinPath(test_path, "same3"), path::joinPath(test_path, "same3/shaggy.txt")), std::exception);
    EXPECT_THROW(path::hasSameContent(path::joinPath(test_path, "same3/shaggy.txt"), path::joinPath(test_path, "same3")), std::exception);
}

TEST(hasSameContent, directories)
{
    ASSERT_TRUE(path::hasSameContent(path::joinPath(test_path, "same1"), path::joinPath(test_path, "same2")));
    ASSERT_FALSE(path::hasSameContent(path::joinPath(test_path, "same1"), path::joinPath(test_path, "same3")));
}

TEST(hasSameContent, files)
{
    ASSERT_TRUE(path::hasSameContent(path::joinPath(test_path, "same3/shaggy.txt"), path::joinPath(test_path, "same3/shaggy1.txt")));
    ASSERT_FALSE(path::hasSameContent(path::joinPath(test_path, "same3/sand1.txt"), path::joinPath(test_path, "same3/shaggy.txt")));
}

TEST(copy, copying)
{
    std::string from = path::joinPath(test_path, "same1");
    path::copy(from, temp_path);

    std::string copied_path = path::joinPath(temp_path, "same1");
    ASSERT_TRUE(path::exists(copied_path));
    path::remove(copied_path);
}