/*
 *    Logger_TestCases.hpp
 *
 *    Class to implement the Logger test cases.
 *
 *    Class to implement the Logger test cases.
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

#ifndef INCLUDE_LOG_LOGGER_TESTCASES_HPP_
#define INCLUDE_LOG_LOGGER_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "log/Logger.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class Logger_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( Logger_TestCases );
	CPPUNIT_TEST( Logger_001 );
	CPPUNIT_TEST( Logger_002 );
	CPPUNIT_TEST( Logger_003 );
	CPPUNIT_TEST( log_001 );
	CPPUNIT_TEST( add_stream_001 );
	CPPUNIT_TEST_SUITE_END();

public:
	Logger_TestCases();
	~Logger_TestCases();

protected:
	Logger_TestCases( const Logger_TestCases& tc );
	Logger_TestCases& operator=( const Logger_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void Logger_001();
	void Logger_002();
	void Logger_003();
	void log_001();
	void add_stream_001();

private:
	// Put helper functions here
};

#endif /* INCLUDE_LOG_LOGGER_TESTCASES_HPP_ */
