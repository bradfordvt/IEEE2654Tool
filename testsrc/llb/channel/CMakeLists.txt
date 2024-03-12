# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolChannel_test VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolChannel_HEADERS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/channel/IEEE2654Channel.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/channel/IEEE2654Channel_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/channel/IEEE2654Channel_TestCases.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/channel/HostAPI.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/channel/HostAPI_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/channel/HostAPI_TestCases.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/channel/ClientAPI.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/channel/ClientAPI_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/channel/ClientAPI_TestCases.hpp
	)
set( IEEE2654ToolChannel_SRCS1
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/channel/IEEE2654Channel_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/channel/IEEE2654Channel_TestCases.cpp
	)
set( IEEE2654ToolChannel_SRCS2
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/channel/HostAPI_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/channel/HostAPI_TestCases.cpp
	)
set( IEEE2654ToolChannel_SRCS3
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/channel/ClientAPI_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/channel/ClientAPI_TestCases.cpp
	)

# add_executable( ${PROJECT_NAME}
# 	${IEEE2654ToolChannel_SRCS1}
# 	${IEEE2654ToolChannel_SRCS2}
# 	${IEEE2654ToolChannel_SRCS3}
#        	)
add_executable( IEEE2654Channel_test ${IEEE2654ToolChannel_SRCS1} )
add_executable( HostAPI_test ${IEEE2654ToolChannel_SRCS2} )
add_executable( ClientAPI_test ${IEEE2654ToolChannel_SRCS3} )
target_link_libraries(IEEE2654Channel_test theapplibs cppunit)
target_link_libraries(HostAPI_test theapplibs cppunit)
target_link_libraries(ClientAPI_test theapplibs cppunit)
add_test(IEEE2654Channel ${EXECUTABLE_OUTPUT_PATH}/IEEE2654Channel_test)
add_test(HostAPI ${EXECUTABLE_OUTPUT_PATH}/HostAPI_test)
add_test(ClientAPI ${EXECUTABLE_OUTPUT_PATH}/ClientAPI_test)
