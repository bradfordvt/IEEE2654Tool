/*
 *    Repository_TestCases.hpp
 *
 *    Class to implement the Repository test cases.
 *
 *    Class to implement the Repository test cases.
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

#ifndef INCLUDE_REPOSITORY_REPOSITORY_TESTCASES_HPP_
#define INCLUDE_REPOSITORY_REPOSITORY_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "repository/Repository.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class Repository_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( Repository_TestCases );
	CPPUNIT_TEST( Repository_001 );
	CPPUNIT_TEST( Repository_002 );
	CPPUNIT_TEST( Repository_003 );
	CPPUNIT_TEST( parse_001 );
	CPPUNIT_TEST( parse_002 );
	CPPUNIT_TEST( insert_Channel_001 );
	CPPUNIT_TEST_SUITE_END();

public:
	Repository_TestCases();
	~Repository_TestCases();

protected:
	Repository_TestCases( const Repository_TestCases& tc );
	Repository_TestCases& operator=( const Repository_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void Repository_001();
	void Repository_002();
	void Repository_003();
	void parse_001();
	void parse_002();
	void insert_Channel_001();

private:
	// Put helper functions here
};

#endif /* INCLUDE_REPOSITORY_REPOSITORY_TESTCASES_HPP_ */
