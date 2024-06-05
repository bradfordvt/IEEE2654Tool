# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolTestPlug-ins VERSION 0.0.1 LANGUAGES CXX )

# Build the sub-directories
add_subdirectory( TLTestLeaf )
add_subdirectory( DLTestLeaf )
add_subdirectory( ILTestLeaf )
add_subdirectory( CLTestLeaf )
add_subdirectory( TLTestIntermediate )
add_subdirectory( DLTestIntermediate )
add_subdirectory( TLTestController )
add_subdirectory( DLTestController )
