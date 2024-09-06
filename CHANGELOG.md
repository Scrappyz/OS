# Change Log
All notable changes to this project will be documented in this file.

## [0.1.3] - 2024-09-06

### Changed
- Changed return value of `execute()` to `bool` and added a string reference parameter to acquire command output.

### Fixed
- Fixed some Linux specific code.

## [0.1.2] - 2024-08-11

### Changed
- Changed `normalizePath()` algorithm to just change path separators.

## [0.1.1] - 2024-08-07

### Added
- Added `isDirectoryString()` function to check if a certain string is a directory via trailing separator.
- Added boolean parameter to `sourcePath()` to only get the parent directory.
- Added boolean parameter to `isDirectorySeparator()` to have an option to work with any separator.
- Added non-recursive copy to `copy()` and `move()` with `TraversalOption` parameter.
- Added `normalizePath()` function to convert paths to work with other operating system.