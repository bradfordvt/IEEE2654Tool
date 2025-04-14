# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolRepository VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolRepository_HEADERS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/repository/Repository.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/repository/BulletinBoard.hpp
)
set( IEEE2654ToolRepository_SRCS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/repository/Repository.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/repository/BulletinBoard.cpp
)

add_library( ${PROJECT_NAME} ${IEEE2654ToolRepository_SRCS} )
set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION "1.0.0")
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION "1")
target_link_libraries(${PROJECT_NAME} PUBLIC ieee2654_compiler_flags)
