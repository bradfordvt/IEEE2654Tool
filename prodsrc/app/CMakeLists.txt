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
message(STATUS "CMAKE_BUILD_TYPE = " ${CMAKE_BUILD_TYPE})
include_directories( "${CMAKE_SOURCE_DIR}/prodsrc/include" )
if(CMAKE_BUILD_TYPE EQUAL "Debug")
add_executable( IEEE2654Tool ${IEEE2654Tool_SRCS} )
target_include_directories( IEEE2654Tool PUBLIC "${IEEE2654Tool_SOURCE_DIR}/prodsrc/include" )
set_target_properties(IEEE2654Tool PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(IEEE2654Tool PUBLIC theapplibsd python3.10 ieee2654_compiler_flags)
elseif(CMAKE_BUILD_TYPE EQUAL "Release")
add_executable( IEEE2654Tool ${IEEE2654Tool_SRCS} )
target_include_directories( IEEE2654Tool PUBLIC "${IEEE2654Tool_SOURCE_DIR}/prodsrc/include" )
set_target_properties(IEEE2654Tool PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(IEEE2654Tool PUBLIC theapplibs python3.10 ieee2654_compiler_flags)
else()
add_executable( IEEE2654Tool ${IEEE2654Tool_SRCS} )
target_include_directories( IEEE2654Tool PUBLIC "${IEEE2654Tool_SOURCE_DIR}/prodsrc/include" )
set_target_properties(IEEE2654Tool PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(IEEE2654Tool PUBLIC theapplibs python3.10 ieee2654_compiler_flags)
endif()

