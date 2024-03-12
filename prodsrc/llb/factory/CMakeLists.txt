# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolFactory VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolFactory_HEADERS
        ${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/factory/CommandLibraryFactory.hpp
        ${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/factory/DebugLibraryFactory.hpp
        ${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/factory/InjectLibraryFactory.hpp
        ${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/factory/TransformLibraryFactory.hpp
)
set( IEEE2654ToolFactory_SRCS
        ${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/factory/CommandLibraryFactory.cpp
        ${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/factory/DebugLibraryFactory.cpp
        ${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/factory/InjectLibraryFactory.cpp
        ${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/factory/TransformLibraryFactory.cpp
)

add_library( ${PROJECT_NAME} ${IEEE2654ToolFactory_SRCS} )
