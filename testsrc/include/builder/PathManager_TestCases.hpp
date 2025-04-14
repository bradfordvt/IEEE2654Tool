/*
 *    PathManager_TestCases.hpp
 *
 *    Class to implement the PathManager test cases.
 *
 *    Class to implement the PathManager test cases.
 * 
 * Copyright (C) 2024 Bradford G. Van Treuren
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef INCLUDE_BUILDER_JSONBUILDER_TESTCASES_HPP_
#define INCLUDE_BUILDER_JSONBUILDER_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "builder/PathManager.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class PathManager_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( PathManager_TestCases );
	CPPUNIT_TEST( PathManager_001 );
	CPPUNIT_TEST( PathManager_002 );
	CPPUNIT_TEST( PathManager_003 );
	CPPUNIT_TEST( get_paths_001 );
	CPPUNIT_TEST_SUITE_END();

public:
	PathManager_TestCases();
	~PathManager_TestCases();

protected:
	PathManager_TestCases( const PathManager_TestCases& tc );
	PathManager_TestCases& operator=( const PathManager_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void PathManager_001();
	void PathManager_002();
	void PathManager_003();
	void get_paths_001();

private:
	// Put helper functions here
	std::string __expand_environment_variables( const std::string &s );
};

#endif /* INCLUDE_BUILDER_JSONBUILDER_TESTCASES_HPP_ */
