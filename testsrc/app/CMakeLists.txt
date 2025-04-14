# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654Tool_test VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolApp_HEADERS ${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/IEEE2654Tool.hpp )
set( IEEE2654ToolApp_SRCS ${IEEE2654Tool_SOURCE_DIR}/testsrc/app/IEEE2654Tool_test.cpp )

# add_library(theapplibs
# 	$<TARGET_OBJECTS:IEEE2654ToolBus>
# 	$<TARGET_OBJECTS:IEEE2654ToolChannel>
# 	$<TARGET_OBJECTS:IEEE2654ToolFactory>
# 	$<TARGET_OBJECTS:IEEE2654ToolLog>
# 	$<TARGET_OBJECTS:IEEE2654ToolModel>)
# # add_executable( ${PROJECT_NAME} ${IEEE2654ToolApp_SRCS} )
add_executable( ${PROJECT_NAME} ${IEEE2654ToolApp_SRCS} )
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(${PROJECT_NAME} PUBLIC theapplibs cppunit ieee2654_compiler_flags)
add_test(IEEE2654Tool ${EXECUTABLE_OUTPUT_PATH}/IEEE2654Tool_test)
