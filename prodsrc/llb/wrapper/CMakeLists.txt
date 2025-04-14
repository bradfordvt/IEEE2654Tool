# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolWrapper VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolWrapper_HEADERS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/wrapper/InjectLibraryWrapper.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/wrapper/CommandLibraryWrapper.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/wrapper/TransformLibraryWrapper.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/wrapper/DebugLibraryWrapper.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/wrapper/ModelData.hpp
	)

set( IEEE2654ToolWrapper_SRCS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/wrapper/InjectLibraryWrapper.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/wrapper/CommandLibraryWrapper.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/wrapper/TransformLibraryWrapper.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/wrapper/DebugLibraryWrapper.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/wrapper/ModelData.cpp
	)

add_library( ${PROJECT_NAME} ${IEEE2654ToolWrapper_SRCS} )
set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION "1.0.0")
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION "1")
target_link_libraries(${PROJECT_NAME} PUBLIC ieee2654_compiler_flags)
