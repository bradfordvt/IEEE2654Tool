/*
 *    TLTestIntermediate_TestCases.hpp
 *
 *    Class to implement the TLTestIntermediate test cases.
 *
 *    Class to implement the TLTestIntermediate test cases.
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

#ifndef INCLUDE_PLUGINS_TLTESTINTERMEDIATE_TLTESTINTERMEDIATE_TESTCASES_HPP_
#define INCLUDE_PLUGINS_TLTESTINTERMEDIATE_TLTESTINTERMEDIATE_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TLTestIntermediate_TestCases : public CPPUNIT_NS::TestFixture {
        CPPUNIT_TEST_SUITE( TLTestIntermediate_TestCases );
        CPPUNIT_TEST( TLTestIntermediate_001 );
        CPPUNIT_TEST( TLTestIntermediate_002 );
        CPPUNIT_TEST( TLTestIntermediate_003 );
        CPPUNIT_TEST( open_001 );
        CPPUNIT_TEST( close_001 );
        CPPUNIT_TEST( config_001 );
        CPPUNIT_TEST( select_001 );
        CPPUNIT_TEST( deselect_001 );
        CPPUNIT_TEST( is_selected_001 );
        CPPUNIT_TEST( get_error_code_001 );
        CPPUNIT_TEST( get_error_string_001 );
        CPPUNIT_TEST( get_status_code_001 );
        CPPUNIT_TEST( get_status_string_001 );
        CPPUNIT_TEST( handle_request_001 );
        CPPUNIT_TEST( handle_response_001 );
        CPPUNIT_TEST( apply_001 );
        CPPUNIT_TEST_SUITE_END();

public:
	TLTestIntermediate_TestCases();
	TLTestIntermediate_TestCases( const TLTestIntermediate_TestCases& tc );
	TLTestIntermediate_TestCases& operator=( const TLTestIntermediate_TestCases& tc );
	~TLTestIntermediate_TestCases();

	void TLTestIntermediate_001( );
	void TLTestIntermediate_002( );
	void TLTestIntermediate_003( );
	void open_001( );
	void close_001( );
	void config_001( );
	void select_001( );
	void deselect_001( );
	void is_selected_001( );
	void get_error_code_001( );
	void get_error_string_001( );
	void get_status_code_001( );
	void get_status_string_001( );
	void handle_request_001( );
	void handle_response_001( );
	void apply_001( );


	void setUp();
	void tearDown();
};

#endif /* INCLUDE_PLUGINS_TLTESTINTERMEDIATE_TLTESTINTERMEDIATE_TESTCASES_HPP_ */
