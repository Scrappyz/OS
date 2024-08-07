## os::path::relativePath
Defined in header `os.hpp`

| Declarations |
| --- |
| std::string relativePath(const std::filesystem::path& path, const std::filesystem::path& base_path = std::filesystem::current_path()) |

## Parameters
`path` - an existing path \
`base_path` - a path which `path` will be made relative to

## Return Value
Returns a path relative to the base path.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::relativePath("foo/bar/koo/aid", "foo/bar") << endl;

    return 0;
}
```
Output:
```
koo/aid
```

## References
| | |
| --- | --- |
| [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) | represents a path |