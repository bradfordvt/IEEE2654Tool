# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolLogTest VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolLog_HEADERS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/log/Logger.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/log/Logger_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/log/Logger_TestCases.hpp
	)
set( IEEE2654ToolLog_SRCS1
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/log/Logger_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/log/Logger_TestCases.cpp
	)

add_executable( Logger_test ${IEEE2654ToolLog_SRCS1} )
target_link_libraries(Logger_test theapplibs cppunit)
add_test(Logger ${EXECUTABLE_OUTPUT_PATH}/Logger_test)
