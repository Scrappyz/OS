# Change Log
All notable changes to this project will be documented in this file.

## [0.1.1] - 2024-08-07

### Added
- Added `isDirectoryString()` function to check if a certain string is a directory via trailing separator.
- Added boolean parameter to `sourcePath()` to only get the parent directory.
- Added boolean parameter to `isDirectorySeparator()` to have an option to work with any separator.
- Added non-recursive copy to `copy()` and `move()` with `TraversalOption` parameter.