# Description of Directory: build
This directory is used to be the build region for creating the CMake infrastructure.

# How to build
## Linux
```sh
$ cd build
$ rm -rf *
$ cmake ..
$ cmake --build .
$ ctest
```
## Windows
Windows is currently unsupported.

The plan is to support MinGW-w64 with CMake.
