## os::path::isDirectorySeparator
Defined in header `os.hpp`

| Declarations |
| --- |
| bool isDirectorySeparator(char ch, bool any_separator = false) |

## Parameters
`ch` - the character to check \
`any_separator` - allow any separator in any operating system

## Return Value
`true` if the character is a directory separator, `false` otherwise.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::isDirectorySeparator('/') << endl;
    cout << path::isDirectorySeparator('\\') << endl;
    cout << path::isDirectorySeparator('a') << endl;

    return 0;
}
```
Output:
```
1
1
0
```