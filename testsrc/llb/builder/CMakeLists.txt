# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolBuilderTest VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolBuilder_HEADERS1
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/builder/ModuleFinder.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/builder/ModuleFinder_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/builder/ModuleFinder_TestCases.hpp
)
set( IEEE2654ToolBuilder_HEADERS2
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/builder/JSONBuilder.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/builder/JSONBuilder_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/builder/JSONBuilder_TestCases.hpp
)
set( IEEE2654ToolBuilder_HEADERS3
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/builder/PathManager.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/builder/PathManager_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/builder/PathManager_TestCases.hpp
)
set( IEEE2654ToolBuilderTest_SRCS1
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/builder/ModuleFinder_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/builder/ModuleFinder_TestCases.cpp)

set( IEEE2654ToolBuilderTest_SRCS2
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/builder/JSONBuilder_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/builder/JSONBuilder_TestCases.cpp)

set( IEEE2654ToolBuilderTest_SRCS3
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/builder/PathManager_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/builder/PathManager_TestCases.cpp)

if(CMAKE_BUILD_TYPE EQUAL "Debug")
	add_executable( ModuleFinder_testd ${IEEE2654ToolBuilderTest_SRCS1} )
	set_target_properties(ModuleFinder_testd PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(ModuleFinder_testd PUBLIC IEEE2654ToolBuilderd IEEE2654ToolLogd IEEE2654ToolModeld IEEE2654ToolWrapperd IEEE2654ToolFactoryd IEEE2654ToolChanneld IEEE2654ToolBusd IEEE2654ToolRepositoryd IEEE2654ToolDebugd cppunit ieee2654_compiler_flags)
	add_test(ModuleFinderd ${EXECUTABLE_OUTPUT_PATH}/ModuleFinder_testd)
	add_executable( JSONBuilder_testd ${IEEE2654ToolBuilderTest_SRCS2} )
	set_target_properties(JSONBuilder_testd PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(JSONBuilder_testd PUBLIC IEEE2654ToolBuilderd IEEE2654ToolLogd IEEE2654ToolModeld IEEE2654ToolWrapperd IEEE2654ToolFactoryd IEEE2654ToolChanneld IEEE2654ToolBusd IEEE2654ToolParserd IEEE2654ToolRepositoryd IEEE2654ToolLogd IEEE2654ToolDebugd cppunit ieee2654_compiler_flags)
	add_test(JSONBuilderd ${EXECUTABLE_OUTPUT_PATH}/JSONBuilder_testd)
	add_executable( PathManager_testd ${IEEE2654ToolBuilderTest_SRCS3} )
	set_target_properties(PathManager_testd PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(PathManager_testd PUBLIC IEEE2654ToolBuilderd IEEE2654ToolLogd IEEE2654ToolModeld IEEE2654ToolWrapperd IEEE2654ToolFactoryd IEEE2654ToolChanneld IEEE2654ToolBusd IEEE2654ToolParserd IEEE2654ToolRepositoryd IEEE2654ToolLogd IEEE2654ToolDebugd IEEE2654ToolLogd cppunit ieee2654_compiler_flags)
	add_test(PathManagerd ${EXECUTABLE_OUTPUT_PATH}/PathManager_testd)
elseif(CMAKE_BUILD_TYPE EQUAL "Release")
	add_executable( ModuleFinder_test ${IEEE2654ToolBuilderTest_SRCS1} )
	set_target_properties(ModuleFinder_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(ModuleFinder_test PUBLIC IEEE2654ToolBuilder IEEE2654ToolLog IEEE2654ToolModel IEEE2654ToolWrapper IEEE2654ToolFactory IEEE2654ToolChannel IEEE2654ToolBus IEEE2654ToolRepository IEEE2654ToolDebug cppunit ieee2654_compiler_flags)
	add_test(JSONBuilder ${EXECUTABLE_OUTPUT_PATH}/JSONBuilder_test)
	add_executable( JSONBuilder_test ${IEEE2654ToolBuilderTest_SRCS2} )
	set_target_properties(JSONBuilder_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(JSONBuilder_test PUBLIC IEEE2654ToolBuilder IEEE2654ToolLog IEEE2654ToolModel IEEE2654ToolWrapper IEEE2654ToolFactory IEEE2654ToolChannel IEEE2654ToolBus IEEE2654ToolParser IEEE2654ToolRepository IEEE2654ToolDebug cppunit ieee2654_compiler_flags)
	add_test(JSONBuilder ${EXECUTABLE_OUTPUT_PATH}/JSONBuilder_test)
	add_executable( PathManager_test ${IEEE2654ToolBuilderTest_SRCS3} )
	set_target_properties(PathManager_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(PathManager_test PUBLIC IEEE2654ToolBuilder IEEE2654ToolLog IEEE2654ToolModel IEEE2654ToolWrapper IEEE2654ToolFactory IEEE2654ToolChannel IEEE2654ToolBus IEEE2654ToolParser IEEE2654ToolRepository IEEE2654ToolDebug cppunit ieee2654_compiler_flags)
	add_test(PathManager ${EXECUTABLE_OUTPUT_PATH}/PathManager_test)
else()
	add_executable( ModuleFinder_test ${IEEE2654ToolBuilderTest_SRCS1} )
	set_target_properties(ModuleFinder_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(ModuleFinder_test PUBLIC IEEE2654ToolBuilder IEEE2654ToolLog IEEE2654ToolModel IEEE2654ToolWrapper IEEE2654ToolFactory IEEE2654ToolChannel IEEE2654ToolBus IEEE2654ToolRepository IEEE2654ToolLog IEEE2654ToolDebug cppunit ieee2654_compiler_flags)
	add_test(ModuleFinder ${EXECUTABLE_OUTPUT_PATH}/ModuleFinder_test)
	add_executable( JSONBuilder_test ${IEEE2654ToolBuilderTest_SRCS2} )
	set_target_properties(JSONBuilder_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(JSONBuilder_test PUBLIC IEEE2654ToolBuilder IEEE2654ToolLog IEEE2654ToolModel IEEE2654ToolWrapper IEEE2654ToolFactory IEEE2654ToolChannel IEEE2654ToolBus IEEE2654ToolParser IEEE2654ToolRepository IEEE2654ToolLog IEEE2654ToolDebug cppunit ieee2654_compiler_flags)
	add_test(JSONBuilder ${EXECUTABLE_OUTPUT_PATH}/JSONBuilder_test)
	add_executable( PathManager_test ${IEEE2654ToolBuilderTest_SRCS3} )
	set_target_properties(PathManager_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
	target_link_libraries(PathManager_test PUBLIC IEEE2654ToolBuilder IEEE2654ToolLog IEEE2654ToolModel IEEE2654ToolWrapper IEEE2654ToolFactory IEEE2654ToolChannel IEEE2654ToolBus IEEE2654ToolParser IEEE2654ToolRepository IEEE2654ToolLog IEEE2654ToolDebug cppunit ieee2654_compiler_flags)
	add_test(PathManager ${EXECUTABLE_OUTPUT_PATH}/PathManager_test)
endif()
