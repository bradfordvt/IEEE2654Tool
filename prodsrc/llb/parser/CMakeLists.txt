# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolParser VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolParser_INCL
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/parser/TranslatorRep.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/parser/DebugLibraryRep.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/parser/TransformLibraryRep.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/parser/CommandLibraryRep.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/parser/InjectLibraryRep.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/parser/ChannelRep.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/parser/HostInterfaceRep.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/parser/ClientInterfaceRep.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/parser/CommandInterfaceRep.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/parser/InjectInterfaceRep.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/parser/TopModuleRep.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/parser/JSONParser.hpp
)
set( IEEE2654ToolParser_SRCS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/parser/TranslatorRep.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/parser/DebugLibraryRep.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/parser/TransformLibraryRep.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/parser/CommandLibraryRep.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/parser/InjectLibraryRep.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/parser/ChannelRep.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/parser/HostInterfaceRep.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/parser/ClientInterfaceRep.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/parser/CommandInterfaceRep.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/parser/InjectInterfaceRep.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/parser/TopModuleRep.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/parser/JSONParser.cpp
)

add_library( ${PROJECT_NAME} ${IEEE2654ToolParser_SRCS} )
set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION "1.0.0")
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION "1")
target_link_libraries(${PROJECT_NAME} PUBLIC ieee2654_compiler_flags)
