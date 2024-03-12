/*
 *    CommandBus_TestCases.hpp
 *
 *    Class to implement the CommandBus test cases.
 *
 *    Class to implement the CommandBus test cases.
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

#ifndef INCLUDE_BUS_COMMANDBUS_TESTCASES_HPP_
#define INCLUDE_BUS_COMMANDBUS_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "bus/CommandBus.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class CommandBus_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( CommandBus_TestCases );
	CPPUNIT_TEST( CommandBus_001 );
	CPPUNIT_TEST( CommandBus_002 );
	CPPUNIT_TEST( CommandBus_003 );
	CPPUNIT_TEST( operatoreq_001 );
	CPPUNIT_TEST( operatoreq_002 );
	CPPUNIT_TEST( send_command_request_001 );
	CPPUNIT_TEST( handle_command_request_001 );
	CPPUNIT_TEST( send_command_response_001 );
	CPPUNIT_TEST( handle_command_response_001 );
	CPPUNIT_TEST_SUITE_END();

public:
	CommandBus_TestCases();
	~CommandBus_TestCases();

protected:
	CommandBus_TestCases( const CommandBus_TestCases& tc );
	CommandBus_TestCases& operator=( const CommandBus_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void CommandBus_001();
	void CommandBus_002();
	void CommandBus_003();
	void operatoreq_001();
	void operatoreq_002();
	void send_command_request_001();
	void handle_command_request_001();
	void send_command_response_001();
	void handle_command_response_001();

private:
	// Put helper functions here
};

#endif /* INCLUDE_BUS_COMMANDBUS_TESTCASES_HPP_ */
