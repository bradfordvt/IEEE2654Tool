/*
 *    JSONParser_TestCases.hpp
 *
 *    Class to implement the JSONParser test cases.
 *
 *    Class to implement the JSONParser test cases.
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

#ifndef INCLUDE_PARSER_JSONPARSER_TESTCASES_HPP_
#define INCLUDE_PARSER_JSONPARSER_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "parser/JSONParser.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class JSONParser_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( JSONParser_TestCases );
	CPPUNIT_TEST( JSONParser_001 );
	CPPUNIT_TEST( JSONParser_002 );
	CPPUNIT_TEST( JSONParser_003 );
	CPPUNIT_TEST( parse_001 );
	CPPUNIT_TEST( parse_002 );
	CPPUNIT_TEST_SUITE_END();

public:
	JSONParser_TestCases();
	~JSONParser_TestCases();

protected:
	JSONParser_TestCases( const JSONParser_TestCases& tc );
	JSONParser_TestCases& operator=( const JSONParser_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void JSONParser_001();
	void JSONParser_002();
	void JSONParser_003();
	void parse_001();
	void parse_002();

private:
	// Put helper functions here
};

#endif /* INCLUDE_PARSER_JSONPARSER_TESTCASES_HPP_ */
