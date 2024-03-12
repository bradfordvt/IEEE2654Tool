# Description of Directory: build
This directory is used to be the build region for creating the CMake
infrastructure.

# How to build
## Linux
cd build
rm -rf *
cmake ..
cmake --build .
ctest
