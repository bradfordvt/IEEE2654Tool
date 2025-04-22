# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolDSLTest VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolDSL_HEADERS1
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/dsl/PDL2CoreParser.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/dsl/PDL2CoreInterpreter.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/dsl/TCLInterpreter.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/dsl/TCLInterpreter_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/dsl/TCLInterpreter_TestCases.hpp
)
set( IEEE2654ToolDSL_HEADERS2
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/dsl/PDL2CoreParser.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/dsl/PDL2CoreInterpreter.hpp
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/dsl/PDL2Interpreter.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/dsl/PDL2Interpreter_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/dsl/PDL2Interpreter_TestCases.hpp
)

set( IEEE2654ToolDSLTest_SRCS1
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/dsl/TCLInterpreter_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/dsl/TCLInterpreter_TestCases.cpp)

set( IEEE2654ToolDSLTest_SRCS2
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/dsl/PDL2Interpreter_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/dsl/PDL2Interpreter_TestCases.cpp)

if(CMAKE_BUILD_TYPE EQUAL "Debug")
	add_executable( TCLInterpreter_testd ${IEEE2654ToolDSLTest_SRCS1} )
	set_target_properties(TCLInterpreter_testd PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_compile_options(TCLInterpreter_testd INTERFACE -D=DEBUG)
	target_link_libraries(TCLInterpreter_testd PUBLIC IEEE2654ToolDSLd IEEE2654ToolLogd IEEE2654ToolModeld IEEE2654ToolWrapperd IEEE2654ToolFactoryd IEEE2654ToolChanneld IEEE2654ToolBusd IEEE2654ToolRepositoryd cppunit ieee2654_compiler_flags)
	add_test(TCLInterpreterd COMMAND ${EXECUTABLE_OUTPUT_PATH}/PDL2Interpreter_testd)
	add_executable( PDL2Interpreter_testd ${IEEE2654ToolDSLTest_SRCS2} )
	set_target_properties(PDL2Interpreter_testd PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(PDL2Interpreter_testd PUBLIC IEEE2654ToolDSLd IEEE2654ToolLogd IEEE2654ToolModeld IEEE2654ToolWrapperd IEEE2654ToolFactoryd IEEE2654ToolChanneld IEEE2654ToolBusd IEEE2654ToolParserd IEEE2654ToolRepositoryd IEEE2654ToolLogd cppunit ieee2654_compiler_flags)
	add_test(PDL2Interpreterd COMMAND ${EXECUTABLE_OUTPUT_PATH}/PDL2Interpreter_testd)
elseif(CMAKE_BUILD_TYPE EQUAL "Release")
	add_executable( TCLInterpreter_test ${IEEE2654ToolDSLTest_SRCS1} )
	set_target_properties(TCLInterpreter_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(TCLInterpreter_test PUBLIC IEEE2654ToolDSL IEEE2654ToolLog IEEE2654ToolModel IEEE2654ToolWrapper IEEE2654ToolFactory IEEE2654ToolChannel IEEE2654ToolBus IEEE2654ToolRepository cppunit ieee2654_compiler_flags)
	add_test(TCLInterpreter COMMAND ${EXECUTABLE_OUTPUT_PATH}/PDL2Interpreter_test)
	add_executable( PDL2Interpreter_test ${IEEE2654ToolDSLTest_SRCS2} )
	set_target_properties(PDL2Interpreter_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(PDL2Interpreter_test PUBLIC IEEE2654ToolDSL IEEE2654ToolLog IEEE2654ToolModel IEEE2654ToolWrapper IEEE2654ToolFactory IEEE2654ToolChannel IEEE2654ToolBus IEEE2654ToolParser IEEE2654ToolRepository cppunit ieee2654_compiler_flags)
	add_test(PDL2Interpreter COMMAND ${EXECUTABLE_OUTPUT_PATH}/PDL2Interpreter_test)
else()
	add_executable( TCLInterpreter_test ${IEEE2654ToolDSLTest_SRCS1} )
	set_target_properties(TCLInterpreter_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(TCLInterpreter_test PUBLIC IEEE2654ToolDSL IEEE2654ToolLog IEEE2654ToolModel IEEE2654ToolWrapper IEEE2654ToolFactory IEEE2654ToolChannel IEEE2654ToolBus IEEE2654ToolRepository IEEE2654ToolLog cppunit ieee2654_compiler_flags)
	add_test(TCLInterpreter COMMAND ${EXECUTABLE_OUTPUT_PATH}/TCLInterpreter_test)
	add_executable( PDL2Interpreter_test ${IEEE2654ToolDSLTest_SRCS2} )
	set_target_properties(PDL2Interpreter_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(PDL2Interpreter_test PUBLIC IEEE2654ToolDSL IEEE2654ToolLog IEEE2654ToolModel IEEE2654ToolWrapper IEEE2654ToolFactory IEEE2654ToolChannel IEEE2654ToolBus IEEE2654ToolParser IEEE2654ToolRepository IEEE2654ToolLog cppunit ieee2654_compiler_flags)
	add_test(PDL2Interpreter COMMAND ${EXECUTABLE_OUTPUT_PATH}/PDL2Interpreter_test)
endif()
