# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolLlb VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

add_subdirectory( bus )
add_subdirectory( channel )
add_subdirectory( factory )
add_subdirectory( log )
add_subdirectory( model )
add_subdirectory( parser )
add_subdirectory( repository )
add_subdirectory( wrapper )
add_subdirectory( builder )
add_subdirectory( dsl )
add_subdirectory( debug )
