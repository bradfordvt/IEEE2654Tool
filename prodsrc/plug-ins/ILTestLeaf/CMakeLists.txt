# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( ILTestLeaf VERSION 0.0.1 LANGUAGES CXX )

find_package(Protobuf REQUIRED)

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )
set( PLUGIN_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/plugins )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( ILTestLeaf_HEADERS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/plug-ins/ILTestLeaf/ILTestLeaf.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/protodef/generated/IEEE2654.pb.h
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/protodef/generated/BUTTON.pb.h
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/protodef/generated/Command_BUTTON.pb.h
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/debug/SwDebugLib.hpp
)
set( ILTestLeaf_SRCS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/plug-ins/ILTestLeaf/ILTestLeafWrapper.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/plug-ins/ILTestLeaf/ILTestLeaf.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/protodef/generated/IEEE2654.pb.cc
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/protodef/generated/BUTTON.pb.cc
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/protodef/generated/Command_BUTTON.pb.cc
)

add_library( ${PROJECT_NAME} SHARED ${ILTestLeaf_SRCS} )
# set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
# make sure that the built .dll or .so file is placed into the 'build' or 'bin' directory
set_target_properties(${PROJECT_NAME} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${PLUGIN_OUTPUT_PATH}"
	VERSION ${PROJECT_VERSION}
	)
target_link_libraries(${PROJECT_NAME} ${Protobuf_LIBRARIES})
