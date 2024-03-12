# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolApp VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
# set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
# set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

message(STATUS "IEEE2654Tool_SOURCE_DIR = ${IEEE2654Tool_SOURCE_DIR}")
# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654Tool_HEADERS ${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/IEEE2654Tool.hpp )
set( IEEE2654Tool_SRCS ${IEEE2654Tool_SOURCE_DIR}/prodsrc/app/IEEE2654Tool.cpp )

message(STATUS "include_directories of app : ${CMAKE_SOURCE_DIR}/prodsrc/include")
include_directories( "${CMAKE_SOURCE_DIR}/prodsrc/include" )
add_executable( IEEE2654Tool ${IEEE2654Tool_SRCS} )
target_include_directories( IEEE2654Tool PUBLIC "${IEEE2654Tool_SOURCE_DIR}/prodsrc/include" )

