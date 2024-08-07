## os::path::copy
Defined in header `os.hpp`

| Declarations |
| --- |
| bool copy(const std::filesystem::path& from, const std::filesystem::path& to, const TraversalOption& traversal_option, const CopyOption& copy_option = CopyOption::None) |
| bool copy(const std::filesystem::path& from, const std::filesystem::path& to, const CopyOption& copy_option, const TraversalOption& traversal_option = TraversalOption::Recursive)
| bool copy(const std::filesystem::path& from, const std::filesystem::path& to) |

## Parameters
`from` - the source file/directory to copy \
`to` - the destination file/directory to copy to \
`copy_option` - option what to do with existing files \
`traversal_option` - option if traversal is recursive or not

## Return Value
Returns `true` if the copy operation was completed, `false` otherwise.

## Notes
- If there is a directory separator at the end of the `from` path, it will only copy the contents of the source directory.

## Example
### Example 1
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    // create a directory "sandbox" in "temp" then copy its contents
    path::copy("sandbox", "temp"); 

    return 0;
}
```
Before running code:
```
Debug/
+-- sandbox/
|   +-- sand.txt
|   +-- sandmore.txt
|   +-- subbox/
|       +-- stuff.txt
+-- temp/
    +-- temp.txt
    +-- test.txt
```
After running code:
```
Debug/
+-- sandbox/
|   +-- sand.txt
|   +-- sandmore.txt
|   +-- subbox/
|       +-- stuff.txt
+-- temp/
    +-- sandbox/
    |   +-- sand.txt
    |   +-- sandmore.txt
    |   +-- subbox/
    |       +-- stuff.txt
    +-- temp.txt
    +-- test.txt
```

### Example 2
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    // only copy the contents of "sandbox" into "temp"
    path::copy("sandbox/", "temp"); // directory separator at the end of "sandbox"

    return 0;
}
```
Before running code:
```
Debug/
+-- sandbox/
|   +-- sand.txt
|   +-- sandmore.txt
|   +-- subbox/
|       +-- stuff.txt
+-- temp/
    +-- temp.txt
    +-- test.txt
```
After running code:
```
Debug/
+-- sandbox/
|   +-- sand.txt
|   +-- sandmore.txt
|   +-- subbox/
|       +-- stuff.txt
+-- temp/
    +-- sand.txt
    +-- sandmore.txt
    +-- subbox/
    |   +-- stuff.txt
    +-- temp.txt
    +-- test.txt
```

### Example 3
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    // will overwrite the whole "temp" directory with the contents of "sandbox"
    path::copy("sandbox/", "temp", path::CopyOption::OverwriteAll); // "sandbox" has end separator

    return 0;
}
```
Before running code:
```
Debug/
+-- sandbox/
|   +-- sand1.txt
|   +-- sand2.txt
+-- temp/
    +-- subtemp/
    |   +-- subtemp.txt
    +-- temp1.txt
```
After running code:
```
Debug/
+-- sandbox/
|   +-- sand1.txt
|   +-- sand2.txt
+-- temp/
    +-- sand1.txt
    +-- sand2.txt
```

## References
| | |
| --- | --- |
| [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) | represents a path |
| [CopyOption](../Enums/CopyOption.md) | specifies the type of copy operation to use |