# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolDLTestControllerTest VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolDLTestControllerTest_HEADERS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/plug-ins/DLTestController/DLTestController.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/plug-ins/DLTestController/DLTestController_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/plug-ins/DLTestController/DLTestController_TestCases.hpp
)
set( IEEE2654ToolDLTestControllerTest_SRCS
	${IEEE2654Tool_SOURCE_DIR}/testsrc/plug-ins/DLTestController/DLTestController_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/plug-ins/DLTestController/DLTestController_TestCases.cpp
)

add_executable( DLTestController_test ${IEEE2654ToolDLTestControllerTest_SRCS} )
target_link_libraries(DLTestController_test theapplibs cppunit)
add_test(DLTestController_test ${EXECUTABLE_OUTTLTESTPUT_PATH}/DLTestController_test)
