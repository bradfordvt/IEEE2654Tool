/*
 *    JSONBuilder_TestCases.hpp
 *
 *    Class to implement the JSONBuilder test cases.
 *
 *    Class to implement the JSONBuilder test cases.
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

#include "builder/JSONBuilder.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class JSONBuilder_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( JSONBuilder_TestCases );
	CPPUNIT_TEST( JSONBuilder_001 );
	CPPUNIT_TEST( JSONBuilder_002 );
	CPPUNIT_TEST( JSONBuilder_003 );
	CPPUNIT_TEST( build_root_001 );
	CPPUNIT_TEST_SUITE_END();

public:
	JSONBuilder_TestCases();
	~JSONBuilder_TestCases();

protected:
	JSONBuilder_TestCases( const JSONBuilder_TestCases& tc );
	JSONBuilder_TestCases& operator=( const JSONBuilder_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void JSONBuilder_001();
	void JSONBuilder_002();
	void JSONBuilder_003();
	void build_root_001();

private:
	// Put helper functions here
};

#endif /* INCLUDE_BUILDER_JSONBUILDER_TESTCASES_HPP_ */
