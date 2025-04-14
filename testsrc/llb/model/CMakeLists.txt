# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolModeliTest VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolModel_HEADERS
        ${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/model/Translator.hpp
        ${IEEE2654Tool_SOURCE_DIR}/testsrc/include/model/Translator_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/model/Translator_TestCases.hpp
)
set( IEEE2654ToolModelTest_SRCS1
        ${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/model/Translator_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/model/Translator_TestCases.cpp
)

add_executable( Translator_test ${IEEE2654ToolModelTest_SRCS1} )
set_target_properties(Translator_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(Translator_test PUBLIC theapplibs cppunit ieee2654_compiler_flags)
add_test(Translator ${EXECUTABLE_OUTPUT_PATH}/Translator_test)
