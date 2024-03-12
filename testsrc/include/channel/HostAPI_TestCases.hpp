/*
 *    HostAPI_TestCases.hpp
 *
 *    Class to implement the HostAPI test cases.
 *
 *    Class to implement the HostAPI test cases.
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

#ifndef INCLUDE_CHANNEL_HOSTAPI_TESTCASES_HPP_
#define INCLUDE_CHANNEL_HOSTAPI_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "channel/HostAPI.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class HostAPI_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( HostAPI_TestCases );
	CPPUNIT_TEST( HostAPI_001 );
	CPPUNIT_TEST( HostAPI_002 );
	CPPUNIT_TEST( HostAPI_003 );
	CPPUNIT_TEST( set_channel_001);
	CPPUNIT_TEST( set_translator_001 );
	CPPUNIT_TEST( handle_request_001 );
	CPPUNIT_TEST( send_response_001 );
	CPPUNIT_TEST( update_request_001 );
	CPPUNIT_TEST( handle_update_response_001 );
	CPPUNIT_TEST_SUITE_END();

public:
	HostAPI_TestCases();
	~HostAPI_TestCases();

protected:
	HostAPI_TestCases( const HostAPI_TestCases& tc );
	HostAPI_TestCases& operator=( const HostAPI_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void HostAPI_001();
	void HostAPI_002();
	void HostAPI_003();
	void set_channel_001();
	void set_translator_001();
	void handle_request_001();
	void send_response_001();
	void update_request_001();
	void handle_update_response_001();

private:
	// Put helper functions here
};

#endif /* INCLUDE_CHANNEL_HOSTAPI_TESTCASES_HPP_ */
