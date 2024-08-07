## os::path::sourcePath
Defined in header `os.hpp`

| Declarations |
| --- |
| std::string sourcePath(bool parent_path = true) |

## Parameters
`parent_path` - if `true`, return the parent path of the source

## Return Value
Returns the absolute path to the executable.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::sourcePath() << endl;

    return 0;
}
```
Output:
```
D:\Documents\Codes\VS Code\C++\Utility\bin\Debug
```