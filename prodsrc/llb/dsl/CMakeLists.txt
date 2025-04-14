# CMakeLists.txt

# We are using version 3.10 of CMake for this application
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolDSL VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolDSL_HEADERS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/dsl/TestInterpreter.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/dsl/PythonInterpreter.hpp
        )

set( IEEE2654ToolDSL_SRCS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/dsl/TestInterpreter.cpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/llb/dsl/PythonInterpreter.cpp
        )

add_library( ${PROJECT_NAME} ${IEEE2654ToolDSL_SRCS} )
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

# Variable PYTHON_LIBRARIES can contains keyword `optimized`
# which won't be interpreted inside a generator expression.
# i.e. we can't use: $<$<PLATFORM_ID:Windows>:${PYTHON_LIBRARIES}>
# see: https://cmake.org/cmake/help/git-stage/command/target_link_libraries.html#command:target_link_libraries
if(MSVC)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${Python3_LIBRARIES})
endif()
