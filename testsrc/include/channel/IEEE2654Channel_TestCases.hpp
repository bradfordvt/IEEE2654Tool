/*
 *    IEEE2654Channel_TestCases.hpp
 *
 *    Class to implement the IEEE2654Channel test cases.
 *
 *    Class to implement the IEEE2654Channel test cases.
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

#ifndef INCLUDE_CHANNEL_IEEE2654CHANNEL_TESTCASES_HPP_
#define INCLUDE_CHANNEL_IEEE2654CHANNEL_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "channel/IEEE2654Channel.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class IEEE2654Channel_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( IEEE2654Channel_TestCases );
	CPPUNIT_TEST( IEEE2654Channel_001 );
	CPPUNIT_TEST( IEEE2654Channel_002 );
	CPPUNIT_TEST( IEEE2654Channel_003 );
	CPPUNIT_TEST( set_client_001);
	CPPUNIT_TEST( set_host_001 );
	CPPUNIT_TEST( send_request_001 );
	CPPUNIT_TEST( send_response_001 );
	CPPUNIT_TEST( handle_request_001 );
	CPPUNIT_TEST( handle_response_001 );
	CPPUNIT_TEST( update_request_001 );
	CPPUNIT_TEST( handle_update_request_001 );
	CPPUNIT_TEST( send_update_response_001 );
	CPPUNIT_TEST( handle_update_response_001 );
	CPPUNIT_TEST_SUITE_END();

public:
	IEEE2654Channel_TestCases();
	~IEEE2654Channel_TestCases();

protected:
	IEEE2654Channel_TestCases( const IEEE2654Channel_TestCases& tc );
	IEEE2654Channel_TestCases& operator=( const IEEE2654Channel_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void IEEE2654Channel_001();
	void IEEE2654Channel_002();
	void IEEE2654Channel_003();
	void set_client_001();
	void set_host_001();
	void send_request_001();
	void send_response_001();
	void handle_request_001();
	void handle_response_001();
	void update_request_001();
	void handle_update_request_001();
	void send_update_response_001();
	void handle_update_response_001();

private:
	// Put helper functions here
};

#endif /* INCLUDE_CHANNEL_IEEE2654CHANNEL_TESTCASES_HPP_ */
