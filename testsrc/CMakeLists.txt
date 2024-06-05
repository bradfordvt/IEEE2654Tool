# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolTest VERSION 0.0.1 LANGUAGES CXX )

include_directories( ${IEEE2654Tool_SOURCE_DIR}/testsrc/include )

# Build the sub-directories
add_subdirectory( app )
add_subdirectory( llb )
add_subdirectory( plug-ins )

# Usefull to get CPPUNIT ...
# I would love to find a way to have cppunit
# only required for builds where unit test make sense ...
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")
FIND_PACKAGE(CPPUNIT REQUIRED)
