# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolTLTestLeafTest VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolTLTestLeafTest_HEADERS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/plug-ins/TLTestLeaf/TLTestLeaf.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/plug-ins/TLTestLeaf/TLTestLeaf_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/plug-ins/TLTestLeaf/TLTestLeaf_TestCases.hpp
)
set( IEEE2654ToolTLTestLeafTest_SRCS
	${IEEE2654Tool_SOURCE_DIR}/testsrc/plug-ins/TLTestLeaf/TLTestLeaf_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/plug-ins/TLTestLeaf/TLTestLeaf_TestCases.cpp
)

add_executable( TLTestLeaf_test ${IEEE2654ToolTLTestLeafTest_SRCS} )
target_link_libraries(TLTestLeaf_test theapplibs cppunit)
add_test(TLTestLeaf_test ${EXECUTABLE_OUTTLTESTPUT_PATH}/TLTestLeaf_test)
