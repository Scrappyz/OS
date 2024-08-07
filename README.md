## OS Library
The os library aims to simplify and improve the process of performing operations on file systems with the `<filesystem>` library.

## Minimum C++ Version
- [C++17](https://en.cppreference.com/w/cpp/17)

## Includes
- [\<iostream>](https://en.cppreference.com/w/cpp/io/basic_iostream)
- [\<string>](https://en.cppreference.com/w/cpp/string)
- [\<vector>](https://en.cppreference.com/w/cpp/container/vector)
- [\<fstream>](https://en.cppreference.com/w/cpp/io/basic_fstream)
- [\<filesystem>](https://en.cppreference.com/w/cpp/filesystem)
### Windows
- [\<windows.h>](https://learn.microsoft.com/en-us/windows/win32/api/winbase/)
### Linux
- [\<unistd.h>](https://pubs.opengroup.org/onlinepubs/7908799/xsh/unistd.h.html)
- [\<sys/stat.h>](https://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html)
### MacOS
- [\<mach-o/dyld.h>](https://opensource.apple.com/source/dyld/dyld-433.5/include/mach-o/dyld.h.auto.html)

## Enums
Defined in header `os.hpp` \
Defined in namespace `os::path`

| Enum | Description |
| --- | --- |
| [CopyOption](Enums/CopyOption.md) | specifies the type of copy operation to use |
| [TraversalOption](Enums/TraversalOption.md) | specifies what type of filesystem traversal to use |
| [SizeMetric](Enums/SizeMetric.md) | specifies what unit of measurement to use in file sizes |

## Functions
Defined in header `os.hpp` \
Defined in namespace `os::path`

| Function | Description |
| --- | --- |
| [absolutePath](Functions/absolutePath.md) | returns the absolute path of a given relative path |
| [copy](Functions/copy.md) | copies a file or directory |
| [create](Functions/create.md) | creates a new file or directory |
| [currentPath](Functions/currentPath.md) | returns the absolute path you are currently in |
| [directorySeparator](Functions/directorySeparator.md) | returns a directory separator character |
| [execute](Functions/execute.md) | execute a command |
| [exists](Functions/exists.md) | checks if the given path exists |
| [fileExtension](Functions/fileExtension.md) | returns the file extension of a given path or filename |
| [size](Functions/size.md) | returns the size of a given path |
| [filename](Functions/filename.md) | returns the filename of a given path |
| [find](Functions/find.md) | finds a given file |
| [findAll](Functions/findAll.md) | finds multiple of the same file |
| [hasFileExtension](Functions/hasFileExtension.md) | checks if a given path or filename has an extension |
| [hasSameContent](Functions/hasSameContent.md) | checks if two directories have the same files or if two files have the same data |
| [isAbsolutePath](Functions/isAbsolutePath.md) | checks if the given path is an absolute path |
| [isDirectoryString](Functions/isDirectoryString.md) | checks if the given string has a trailing separator |
| [isDirectorySeparator](Functions/isDirectorySeparator.md) | checks if a given character is a directory separator character |
| [isRelativePath](Functions/isRelativePath.md) | checks if the given path is a relative path |
| [isValidFilenameChar](Functions/isValidFilenameChar.md) | checks if the given character is valid for filenames |
| [joinPath](Functions/joinPath.md) | concatenates two or more paths together |
| [move](Functions/move.md) | moves a file or directory |
| [normalizePath](Functions/normalizePath.md) | converts a path to work with the current operating system |
| [parentPath](Functions/parentPath.md) | returns the parent directory of a path |
| [relativePath](Functions/relativePath.md) | returns a path relative to another path |
| [remove](Functions/remove.md) | deletes a path |
| [rename](Functions/rename.md) | renames a file or directory |
| [rootName](Functions/rootName.md) | returns the name of the root |
| [sourcePath](Functions/sourcePath.md) | returns the absolute path to the executable |






