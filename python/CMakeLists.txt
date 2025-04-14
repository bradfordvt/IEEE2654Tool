# CMakeLists.txt

# We are using version 3.10 of CMake for this application
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( PyCommandBus VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolSWIG_HEADERS
        ${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/dsl/PyCommandBus.hpp
        )

set( IEEE2654ToolSWIG_SRCS
        ${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/dsl/PyCommandBus.cpp
        )

cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)
find_package (SWIG)
include (UseSWIG)

set_property(SOURCE PyCommandBus.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE ${IEEE2654ToolSWIG_SRCS} PROPERTY CPLUSPLUS ON)
set_property(SOURCE PyCommandBus.i PROPERTY SWIG_MODULE_NAME PyCommandBus)
set_property(SOURCE PyCommandBus.i PROPERTY SWIG_FLAGS "-py3")
swig_add_library(${PROJECT_NAME}
	# TYPE MODULE
	TYPE SHARED
  LANGUAGE python
  OUTPUT_DIR ${CMAKE_BINARY_DIR}/PyCommandBus
  SOURCES PyCommandBus.i ${IEEE2654ToolSWIG_SRCS})

# add_library( ${PROJECT_NAME} ${IEEE2654ToolSWIG_SRCS} )
set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION "1.0.0")
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION "1")
target_link_libraries(${PROJECT_NAME} PUBLIC ieee2654_compiler_flags)

target_include_directories(${PROJECT_NAME}
  PRIVATE
  ../prodsrc/include
  /usr/include/python3.10
  ${Python3_INCLUDE_DIRS}
  )
set_property(TARGET ${PROJECT_NAME} PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES ON)
add_library(${PROJECT_NAMESPACE}::PyCommandBus ALIAS ${PROJECT_NAME})

# note: macOS is APPLE and also UNIX !
if(APPLE)
	set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX ".so"
    INSTALL_RPATH "@loader_path;@loader_path/../../${PYTHON_PROJECT}/.libs"
    )
  set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY
    LINK_FLAGS "-flat_namespace -undefined suppress"
    )
elseif(UNIX)
	set_target_properties(${PROJECT_NAME} PROPERTIES
    INSTALL_RPATH "$ORIGIN:$ORIGIN/../../${PYTHON_PROJECT}/.libs"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAMESPACE}::PyCommandBus)

# Variable PYTHON_LIBRARIES can contains keyword `optimized`
# which won't be interpreted inside a generator expression.
# i.e. we can't use: $<$<PLATFORM_ID:Windows>:${PYTHON_LIBRARIES}>
# see: https://cmake.org/cmake/help/git-stage/command/target_link_libraries.html#command:target_link_libraries
if(MSVC)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${Python3_LIBRARIES})
endif()
