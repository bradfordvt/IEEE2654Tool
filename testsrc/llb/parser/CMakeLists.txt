# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolParserTest VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolParser_HEADERS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/parser/JSONParser.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/parser/JSONParser_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/parser/JSONParser_TestCases.hpp
)
set( IEEE2654ToolParserTest_SRCS1
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/parser/JSONParser_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/parser/JSONParser_TestCases.cpp)

if(CMAKE_BUILD_TYPE EQUAL "Debug")
add_executable( JSONParser_testd ${IEEE2654ToolParserTest_SRCS1} )
set_target_properties(JSONParser_testd PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_compile_options(JSONParser_testd INTERFACE -D=DEBUG -DUSE_SWDEBUG)
target_link_libraries(JSONParser_testd PUBLIC IEEE2654ToolDebugd IEEE2654ToolParserd IEEE2654ToolLogd IEEE2654ToolModeld IEEE2654ToolWrapperd IEEE2654ToolFactoryd IEEE2654ToolChanneld IEEE2654ToolBusd IEEE2654ToolRepositoryd IEEE2654ToolBuilderd cppunit ieee2654_compiler_flags)
add_test(NAME JSONParserd COMMAND ${EXECUTABLE_OUTPUT_PATH}/JSONParser_testd)
elseif(CMAKE_BUILD_TYPE EQUAL "Release")
add_executable( JSONParser_test ${IEEE2654ToolParserTest_SRCS1} )
set_target_properties(JSONParser_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(JSONParser_test PUBLIC IEEE2654ToolParser IEEE2654ToolLog IEEE2654ToolModel IEEE2654ToolWrapper IEEE2654ToolFactory IEEE2654ToolChannel IEEE2654ToolBus IEEE2654ToolRepository IEEE2654ToolBuilder IEEE2654ToolDebug cppunit ieee2654_compiler_flags)
add_test(NAME JSONParser COMMAND ${EXECUTABLE_OUTPUT_PATH}/JSONParser_test)
else()
add_executable( JSONParser_test ${IEEE2654ToolParserTest_SRCS1} )
set_target_properties(JSONParser_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(JSONParser_test PUBLIC IEEE2654ToolParser IEEE2654ToolLog IEEE2654ToolModel IEEE2654ToolWrapper IEEE2654ToolFactory IEEE2654ToolChannel IEEE2654ToolBus IEEE2654ToolRepository IEEE2654ToolBuilder IEEE2654ToolDebug cppunit ieee2654_compiler_flags)
add_test(NAME JSONParser COMMAND ${EXECUTABLE_OUTPUT_PATH}/JSONParser_test)
endif()
