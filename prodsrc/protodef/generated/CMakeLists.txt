# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( protoBinding VERSION 0.0.1 LANGUAGES CXX )

find_package(Protobuf REQUIRED)

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

## List generated sources files
file(GLOB HDRS "*.h")
file(GLOB SRCS "*.cc")

add_library(${PROJECT_NAME} ${HDRS} ${SRCS})
# ${Protobuf_LIBRARIES} should be defined by FIND_PACKAGE(Protobuf REQUIRED)
target_link_libraries(${PROJECT_NAME} ${Protobuf_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

