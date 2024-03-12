/*
 *    Translator_TestCases.hpp
 *
 *    Class to implement the Translator test cases.
 *
 *    Class to implement the Translator test cases.
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

#ifndef INCLUDE_MODEL_TRANSLATOR_TESTCASES_HPP_
#define INCLUDE_MODEL_TRANSLATOR_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "model/Translator.hpp"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p))

class Translator_TestCases : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( Translator_TestCases );
	CPPUNIT_TEST( Translator_001 );
	CPPUNIT_TEST( Translator_002 );
	CPPUNIT_TEST( Translator_003 );
	CPPUNIT_TEST( find_translator_by_uid_001 );
	CPPUNIT_TEST( find_translator_by_path_001 );
	CPPUNIT_TEST( transform_send_request_001 );
	CPPUNIT_TEST( inject_send_request_001 );
	CPPUNIT_TEST( send_inject_request_001 );
	CPPUNIT_TEST( send_inject_response_001 );
	CPPUNIT_TEST( send_command_response_001 );
	CPPUNIT_TEST( update_request_001 );
	CPPUNIT_TEST( send_response_001 );
	CPPUNIT_TEST( send_update_response_001 );
	CPPUNIT_TEST( logger_transform_001 );
	CPPUNIT_TEST( logger_inject_001 );
	CPPUNIT_TEST( logger_debug_001 );
	CPPUNIT_TEST( logger_command_001 );
	CPPUNIT_TEST( create_var_001 );
	CPPUNIT_TEST( read_var_001 );
	CPPUNIT_TEST( update_var_001 );
	CPPUNIT_TEST( delete_var_001 );
	CPPUNIT_TEST( get_transform_path_001 );
	CPPUNIT_TEST( get_debug_path_001 );
	CPPUNIT_TEST( get_inject_path_001 );
	CPPUNIT_TEST( get_command_path_001 );
	CPPUNIT_TEST( handle_request_001 );
	CPPUNIT_TEST( handle_response_001 );
	CPPUNIT_TEST( handle_update_request_001 );
	CPPUNIT_TEST( handle_update_response_001 );
	CPPUNIT_TEST( handle_inject_request_001 );
	CPPUNIT_TEST( handle_inject_response_001 );
	CPPUNIT_TEST( handle_command_request_001 );
	CPPUNIT_TEST( handle_command_response_001 );
	CPPUNIT_TEST( set_client_001 );
	CPPUNIT_TEST( add_host_001 );
	CPPUNIT_TEST( __lookup_translator_001 );
	CPPUNIT_TEST( __lookup_host_001 );
	CPPUNIT_TEST( __get_path_001 );
	CPPUNIT_TEST_SUITE_END();

public:
	Translator_TestCases();
	~Translator_TestCases();

protected:
	Translator_TestCases( const Translator_TestCases& tc );
	Translator_TestCases& operator=( const Translator_TestCases& tc );

protected:
	// put static variables here

public:
	// put static class scope helper functions here

public:
	void setUp();
	void tearDown();

protected:
	// Put test cases here
	void Translator_001();
	void Translator_002();
	void Translator_003();
	void find_translator_by_uid_001();
	void find_translator_by_path_001();
	void transform_send_request_001();
	void inject_send_request_001();
	void send_inject_request_001();
	void send_inject_response_001();
	void send_command_response_001();
	void update_request_001();
	void send_response_001();
	void send_update_response_001();
	void logger_transform_001();
	void logger_inject_001();
	void logger_debug_001();
	void logger_command_001();
	void create_var_001();
	void read_var_001();
	void update_var_001();
	void delete_var_001();
	void get_transform_path_001();
	void get_debug_path_001();
	void get_inject_path_001();
	void get_command_path_001();
	void handle_request_001();
	void handle_response_001();
	void handle_update_request_001();
	void handle_update_response_001();
	void handle_inject_request_001();
	void handle_inject_response_001();
	void handle_command_request_001();
	void handle_command_response_001();
	void set_client_001();
	void add_host_001();
	void __lookup_translator_001();
	void __lookup_host_001();
	void __get_path_001();

private:
	// Put helper functions here
};

#endif /* INCLUDE_MODEL_LOGGER_TESTCASES_HPP_ */
