# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolPlugIns VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
# set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
# set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

add_subdirectory( TLTestLeaf )
add_subdirectory( DLTestLeaf )
add_subdirectory( ILTestLeaf )
add_subdirectory( CLTestLeaf )
add_subdirectory( TLTestDisplay )
add_subdirectory( DLTestDisplay )
add_subdirectory( ILTestDisplay )
add_subdirectory( CLTestDisplay )
add_subdirectory( TLTestController )
add_subdirectory( DLTestController )
add_subdirectory( TLTestIntermediate )
add_subdirectory( DLTestIntermediate )
