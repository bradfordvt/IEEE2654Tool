/*
 *    TCLInterpreter_TestCases.hpp
 *
 *    Class to implement the TCLInterpreter test cases.
 *
 *    Class to implement the TCLInterpreter test cases.
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

#ifndef INCLUDE_PARSER_TCLINTERPRETER_TESTCASES_HPP_
#define INCLUDE_PARSER_TCLINTERPRETER_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "dsl/TCLInterpreter.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class TCLInterpreter_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( TCLInterpreter_TestCases );
	CPPUNIT_TEST( TCLInterpreter_001 );
	CPPUNIT_TEST( TCLInterpreter_002 );
	CPPUNIT_TEST( TCLInterpreter_003 );
	CPPUNIT_TEST( set_001 );
	CPPUNIT_TEST( puts_001 );
	CPPUNIT_TEST( puts_002 );
	CPPUNIT_TEST_SUITE_END();

public:
	TCLInterpreter_TestCases();
	~TCLInterpreter_TestCases();

protected:
	TCLInterpreter_TestCases( const TCLInterpreter_TestCases& tc );
	TCLInterpreter_TestCases& operator=( const TCLInterpreter_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void TCLInterpreter_001();
	void TCLInterpreter_002();
	void TCLInterpreter_003();
	void set_001();
	void puts_001();
	void puts_002();

private:
	// Put helper functions here
};

#endif /* INCLUDE_PARSER_TCLINTERPRETER_TESTCASES_HPP_ */
