# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolModel VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolModel_HEADERS
        ${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/model/Translator.hpp
)
set( IEEE2654ToolModel_SRCS
        ${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/model/Translator.cpp
)

add_library( ${PROJECT_NAME} ${IEEE2654ToolModel_SRCS} )
