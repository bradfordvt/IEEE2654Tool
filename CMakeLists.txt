# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654Tool VERSION 0.0.1 LANGUAGES CXX )

find_package(Python COMPONENTS Interpreter Development)
set(Python_VERSION_CORE "Python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}")
set(Python_LIBRARY_NAME "python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}")
set(Protobuf_DEBUG 1)
set(Protobuf_PROTOC_EXECUTABLE protoc)
set(CMAKE_DEBUG_POSTFIX d)
set(PROJECT_NAMESPACE IEEE2654)
add_library(ieee2654_compiler_flags INTERFACE)
target_compile_features(ieee2654_compiler_flags INTERFACE cxx_std_11)

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
# if(CMAKE_BUILD_TYPE EQUAL "Debug")
# target_compile_options(ieee2654_compiler_flags INTERFACE
# 	"$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused -DDEBUG -DUSE_SWDEBUG>>"
# 	"$<${msvc_cxx}:$<BUILD_INTERFACE:-W3 -DUSE_SWDEBUG -DDEBUG>>"
# )
# else()
# target_compile_options(ieee2654_compiler_flags INTERFACE
#   "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
#   "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
# )
# endif()
add_compile_options(
	"$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused;-DMULTI_THREAD>>"
	"$<${msvc_cxx}:$<BUILD_INTERFACE:-W3;-DMULTI_THREAD>>"
	"$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb;-DUSE_SWDEBUG>"
)
message(STATUS "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG = ${CMAKE_CXX_FLAGS_DEBUG}")

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# Usefull to get CPPUNIT ...
# I would love to find a way to have cppunit
# only required for builds where unit test make sense ...
# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")
# FIND_PACKAGE(CPPUNIT REQUIRED)

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
# set( IEEE2654Tool_HEADERS ${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/IEEE2654Tool.hpp )
# set( IEEE2654Tool_SRCS ${IEEE2654Tool_SOURCE_DIR}/prodsrc/app/IEEE2654Tool.cpp )

message(STATUS "IEEE2654Tool_SOURCE_DIR = ${IEEE2654Tool_SOURCE_DIR}")

include_directories( "${IEEE2654Tool_SOURCE_DIR}/prodsrc/include" )
include_directories( "${IEEE2654Tool_SOURCE_DIR}/prodsrc/protodef" )
include_directories( "${IEEE2654Tool_SOURCE_DIR}/prodsrc/protodef/generated" )
# enable_testing()
include( CTest )
add_subdirectory( prodsrc )
add_subdirectory( testsrc )
# add_subdirectory( python )

add_library(theapplibs STATIC
	$<TARGET_OBJECTS:IEEE2654ToolBus>
	$<TARGET_OBJECTS:IEEE2654ToolChannel>
	$<TARGET_OBJECTS:IEEE2654ToolFactory>
	$<TARGET_OBJECTS:IEEE2654ToolLog>
	$<TARGET_OBJECTS:IEEE2654ToolModel>
	$<TARGET_OBJECTS:IEEE2654ToolParser>
	$<TARGET_OBJECTS:IEEE2654ToolRepository>
	$<TARGET_OBJECTS:IEEE2654ToolWrapper>
	$<TARGET_OBJECTS:IEEE2654ToolBuilder>
	$<TARGET_OBJECTS:IEEE2654ToolDSL>
	$<TARGET_OBJECTS:IEEE2654ToolDebug>
	$<TARGET_OBJECTS:protoBinding>
	)

