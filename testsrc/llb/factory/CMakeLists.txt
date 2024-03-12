# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolFactoryTest VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolFactory_HEADERS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/factory/CommandLibraryFactory.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/factory/CommandLibraryFactory_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/factory/CommandLibraryFactory_TestCases.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/factory/DebugLibraryFactory.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/factory/DebugLibraryFactory_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/factory/DebugLibraryFactory_TestCases.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/factory/InjectLibraryFactory.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/factory/InjectLibraryFactory_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/factory/InjectLibraryFactory_TestCases.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/factory/TransformLibraryFactory.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/factory/TransformLibraryFactory_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/factory/TransformLibraryFactory_TestCases.hpp
	)
set( IEEE2654ToolFactory_SRCS1
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/factory/CommandLibraryFactory_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/factory/CommandLibraryFactory_TestCases.cpp
	)
set( IEEE2654ToolFactory_SRCS2
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/factory/DebugLibraryFactory_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/factory/DebugLibraryFactory_TestCases.cpp
	)
set( IEEE2654ToolFactory_SRCS3
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/factory/InjectLibraryFactory_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/factory/InjectLibraryFactory_TestCases.cpp
	)
set( IEEE2654ToolFactory_SRCS4
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/factory/TransformLibraryFactory_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/factory/TransformLibraryFactory_TestCases.cpp
	)

add_executable( CommandLibraryFactory_test ${IEEE2654ToolFactory_SRCS1} )
add_executable( DebugLibraryFactory_test ${IEEE2654ToolFactory_SRCS2} )
add_executable( InjectLibraryFactory_test ${IEEE2654ToolFactory_SRCS3} )
add_executable( TransformLibraryFactory_test ${IEEE2654ToolFactory_SRCS4} )
target_link_libraries(CommandLibraryFactory_test theapplibs cppunit)
target_link_libraries(DebugLibraryFactory_test theapplibs cppunit)
target_link_libraries(InjectLibraryFactory_test theapplibs cppunit)
target_link_libraries(TransformLibraryFactory_test theapplibs cppunit)
add_test(CommandLibraryFactory ${EXECUTABLE_OUTPUT_PATH}/CommandLibraryFactory_test)
add_test(DebugLibraryFactory ${EXECUTABLE_OUTPUT_PATH}/DebugLibraryFactory_test)
add_test(InjectLibraryFactory ${EXECUTABLE_OUTPUT_PATH}/InjectLibraryFactory_test)
add_test(TransformLibraryFactory ${EXECUTABLE_OUTPUT_PATH}/TransformLibraryFactory_test)
