# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654Tool VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# Usefull to get CPPUNIT ...
# I would love to find a way to have cppunit
# only required for builds where unit test make sense ...
# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")
# FIND_PACKAGE(CPPUNIT REQUIRED)

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
# set( IEEE2654Tool_HEADERS ${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/IEEE2654Tool.hpp )
# set( IEEE2654Tool_SRCS ${IEEE2654Tool_SOURCE_DIR}/prodsrc/app/IEEE2654Tool.cpp )

message(STATUS "IEEE2654Tool_SOURCE_DIR = ${IEEE2654Tool_SOURCE_DIR}")

include_directories( "${IEEE2654Tool_SOURCE_DIR}/prodsrc/include" )
include_directories( "${IEEE2654Tool_SOURCE_DIR}/prodsrc/protodef" )
include_directories( "${IEEE2654Tool_SOURCE_DIR}/prodsrc/protodef/generated" )
enable_testing()
add_subdirectory( prodsrc )
add_subdirectory( testsrc )

add_library(theapplibs STATIC
	$<TARGET_OBJECTS:IEEE2654ToolBus>
	$<TARGET_OBJECTS:IEEE2654ToolChannel>
	$<TARGET_OBJECTS:IEEE2654ToolFactory>
	$<TARGET_OBJECTS:IEEE2654ToolLog>
	$<TARGET_OBJECTS:IEEE2654ToolModel>
	$<TARGET_OBJECTS:protoBinding>)

