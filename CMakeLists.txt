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
enable_testing()
add_subdirectory( prodsrc )
add_subdirectory( testsrc )
# include_directories( "${CMAKE_SOURCE_DIR}/prodsrc/include" )

# Link the sources with the final binary. The name of the binary
# is going to be "IEEE2654Tool"
# add_executable( IEEE2654Tool ${IEEE2654Tool_SRCS} ${IEEE2654Tool_HEADERS} )

# If the flag DEBUG_MODE is set, build the test file
# if( DEBUG_MODE )
# 
# add_subdirectory( testsrc )
# # set( IEEE2654TOOL_TEST_SRCS IEEE2654ToolTest.cpp )
# # add_executable( IEEE2654Tool_test ${IEEE2654Tool_TEST_SRCS} ${IEEE2654Tool_HEADERS} )
# 
# endif()

add_library(theapplibs
        $<TARGET_OBJECTS:IEEE2654ToolBus>
        $<TARGET_OBJECTS:IEEE2654ToolChannel>
        $<TARGET_OBJECTS:IEEE2654ToolFactory>
        $<TARGET_OBJECTS:IEEE2654ToolLog>
        $<TARGET_OBJECTS:IEEE2654ToolModel>)

