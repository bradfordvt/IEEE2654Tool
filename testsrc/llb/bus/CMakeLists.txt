# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolBus_test VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolBus_HEADERS
		${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/bus/CommandBus.hpp
		${IEEE2654Tool_SOURCE_DIR}/testsrc/include/bus/CommandBus_test.hpp
		${IEEE2654Tool_SOURCE_DIR}/testsrc/include/bus/CommandBus_TestCases.hpp
	)
set( IEEE2654ToolBus_SRCS
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/bus/CommandBus_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/bus/CommandBus_TestCases.cpp
	)

# add_executable( ${PROJECT_NAME} ${IEEE2654ToolBus_SRCS} )
# add_library(theapplibs
#         $<TARGET_OBJECTS:IEEE2654ToolBus>
#         $<TARGET_OBJECTS:IEEE2654ToolChannel>
#         $<TARGET_OBJECTS:IEEE2654ToolFactory>
#         $<TARGET_OBJECTS:IEEE2654ToolLog>
#         $<TARGET_OBJECTS:IEEE2654ToolModel>)
# add_executable( ${PROJECT_NAME} ${IEEE2654ToolApp_SRCS} )
add_executable( CommandBus_test ${IEEE2654ToolBus_SRCS} )
target_link_libraries(CommandBus_test theapplibs cppunit)
add_test(CommandBus ${EXECUTABLE_OUTPUT_PATH}/CommandBus_test)
