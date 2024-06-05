# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( protodef VERSION 0.0.1 )

find_package(Protobuf REQUIRED)

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

FILE(TO_NATIVE_PATH ${IEEE2654Tool_SOURCE_DIR}/prodsrc/protodef PROTOMODEL_PATH)
FILE(TO_NATIVE_PATH ${IEEE2654Tool_SOURCE_DIR}/prodsrc/protodef/generated PROTOBINDING_PATH)

FILE(GLOB DATAMODEL_PROTOS "${IEEE2654Tool_SOURCE_DIR}/prodsrc/protodef/*.proto")

FOREACH(proto ${DATAMODEL_PROTOS})
	FILE(TO_NATIVE_PATH ${proto} proto_native)
	EXECUTE_PROCESS(COMMAND ${Protobuf_PROTOC_EXECUTABLE} --proto_path=${PROTOMODEL_PATH} --cpp_out=${PROTOBINDING_PATH} ${proto_native}
	RESULT_VARIABLE rv)
	# Optional, but that can show the user if something have gone wrong with the proto generation
	IF(${rv})
	 MESSAGE("Generation of data model returned ${rv} for proto ${proto_native}")
	ENDIF()
ENDFOREACH(proto)

add_subdirectory( generated )
