# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolTestLlb VERSION 0.0.1 LANGUAGES CXX )

# Build the sub-directories
add_subdirectory( bus )
add_subdirectory( channel )
add_subdirectory( factory )
add_subdirectory( log )
add_subdirectory( model )
