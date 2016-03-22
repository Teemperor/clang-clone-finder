
# clang-clone-finder

Searches a project for copy-pasted code in three steps:

1. Gets build information by listening what the build system sens to CXX.

2. Parses the project with this build information.

3. Searches all compilation units in the project for clones.

Run with:

`clang-clone-finder COMMAND`

Example: run `clang-clone-finder make` in the `/tests/testproject1` directory.

Currently only collects build information and prints it to the command line.