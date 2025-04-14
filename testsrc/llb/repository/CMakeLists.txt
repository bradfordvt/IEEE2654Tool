# CMakeLists.txt

# We are using version 3.10 of CMake for this application 
cmake_minimum_required( VERSION 3.10 )

# Workspace is IEEE2654Tool
project( IEEE2654ToolRepositoryTest VERSION 0.0.1 LANGUAGES CXX )

# Set the directory where bin will be built.
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

# The CACHE variable *IEEE2654Tool_SOURCE_DIR* stores the absolute path of
# the directory where CMakeLists is located.
set( IEEE2654ToolRepository_HEADERS
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/repository/Repository.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/repository/Repository_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/repository/Repository_TestCases.hpp
)
set( IEEE2654ToolRepository_HEADERS1
	${IEEE2654Tool_SOURCE_DIR}/prodsrc/include/repository/BulletinBoard.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/repository/BulletinBoard_test.hpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/include/repository/BulletinBoard_TestCases.hpp
)
set( IEEE2654ToolRepositoryTest_SRCS1
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/repository/Repository_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/repository/Repository_TestCases.cpp)
set( IEEE2654ToolRepositoryTest_SRCS2
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/repository/BulletinBoard_test.cpp
	${IEEE2654Tool_SOURCE_DIR}/testsrc/llb/repository/BulletinBoard_TestCases.cpp)

add_executable( Repository_test ${IEEE2654ToolRepositoryTest_SRCS1} )
set_target_properties(Repository_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(Repository_test PUBLIC theapplibs cppunit ieee2654_compiler_flags)
add_test(Repository ${EXECUTABLE_OUTPUT_PATH}/Repository_test)
add_executable( BulletinBoard_test ${IEEE2654ToolRepositoryTest_SRCS2} )
set_target_properties(BulletinBoard_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(BulletinBoard_test PUBLIC theapplibs cppunit ieee2654_compiler_flags)
add_test(BulletinBoard ${EXECUTABLE_OUTPUT_PATH}/BulletinBoard_test)
