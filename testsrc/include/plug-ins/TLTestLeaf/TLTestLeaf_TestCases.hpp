/*
 *    TLTestLeaf_TestCases.hpp
 *
 *    Class to implement the TLTestLeaf test cases.
 *
 *    Class to implement the TLTestLeaf test cases.
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

#ifndef INCLUDE_PLUGINS_TLTESTLEAF_TLTESTLEAF_TESTCASES_HPP_
#define INCLUDE_PLUGINS_TLTESTLEAF_TLTESTLEAF_TESTCASES_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TLTestLeaf_TestCases : public CPPUNIT_NS::TestFixture {
        CPPUNIT_TEST_SUITE( TLTestLeaf_TestCases );
        CPPUNIT_TEST( TLTestLeaf_001 );
        CPPUNIT_TEST( TLTestLeaf_002 );
        CPPUNIT_TEST( TLTestLeaf_003 );
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
	TLTestLeaf_TestCases();
	TLTestLeaf_TestCases( const TLTestLeaf_TestCases& tc );
	TLTestLeaf_TestCases& operator=( const TLTestLeaf_TestCases& tc );
	~TLTestLeaf_TestCases();

	void TLTestLeaf_001( );
	void TLTestLeaf_002( );
	void TLTestLeaf_003( );
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

#endif /* INCLUDE_PLUGINS_TLTESTLEAF_TLTESTLEAF_TESTCASES_HPP_ */
