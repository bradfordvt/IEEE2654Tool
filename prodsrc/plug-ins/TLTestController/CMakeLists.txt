# CMakeLists.txt
# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( TLTestController VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )
set( PLUGIN_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/plugins )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( TLTestController_HEADERS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/plug-ins/TLTestController/TLTestController.hpp
)
set( TLTestController_SRCS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/plug-ins/TLTestController/TLTestControllerWrapper.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/plug-ins/TLTestController/TLTestController.cpp
)

add_library( ${PROJECT_NAME} SHARED ${TLTestController_SRCS} )
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
# make sure that the built .dll or .so file is placed into the 'build' or 'bin' directory
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PLUGIN_OUTPUT_PATH}")
