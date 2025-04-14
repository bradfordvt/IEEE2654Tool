# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolProdsrc VERSION 0.0.1 LANGUAGES CXX )

message(STATUS "IEEE2654Tool_SOURCE_DIR = ${IEEE2654Tool_SOURCE_DIR}")

# Set the directory where bin will be built.
# set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
# set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

add_subdirectory( protodef )
add_subdirectory( llb )
add_subdirectory( app )
add_subdirectory( plug-ins )
# add_subdirectory( shared )
