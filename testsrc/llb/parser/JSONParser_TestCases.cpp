/*
 *    JSONParser_TestCases.cpp
 *
 *    Class for the JSONParser test cases.
 *
 *    Class for the JSONParser test cases.
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

static const char __authors__[] = "Bradford G. Van Treuren";
static const char __contact__[] = "bradvt59@gmail.com";
static const char __copyright__[] = "Copyright (C) 2024, Bradford G. Van Treuren";
static const char __credits__[] = "Bradford G. Van Treuren";
static const char __date__[] = "2024/07/03";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <cstdio>
#include <filesystem>
#include "log/Logger.hpp"
#include "parser/JSONParser.hpp"
#include "parser/JSONParser_TestCases.hpp"
#include "repository/Repository.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( JSONParser_TestCases );

JSONParser_TestCases::JSONParser_TestCases( ) : CPPUNIT_NS::TestFixture( ) {
}

JSONParser_TestCases::~JSONParser_TestCases( ) {
}

JSONParser_TestCases::JSONParser_TestCases( const JSONParser_TestCases& tc ) : CPPUNIT_NS::TestFixture( ) {
}

JSONParser_TestCases& JSONParser_TestCases::operator=( const JSONParser_TestCases& tc ) {
	return *this;
}

void JSONParser_TestCases::setUp( ) {
}

void JSONParser_TestCases::tearDown( ) {
}

void JSONParser_TestCases::JSONParser_001() {
	JSONParser p;
#ifdef TEST
	CPPUNIT_ASSERT(p.filename.length() == 0);
#endif
}

void JSONParser_TestCases::JSONParser_002() {
}

void JSONParser_TestCases::JSONParser_003() {
}

void JSONParser_TestCases::parse_001() {
	JSONParser p;

	// find the current path
	std::filesystem::path cwd = std::filesystem::current_path();
	std::string msg("JSONParser_TestCases::parse_001(): ");
	msg += "Current working directory for test is: ";
	msg += cwd.string();
	std::cerr << msg << std::endl;

#ifdef DEBUG
	std::string test_file1("../../../../../examples/model/tree/TestTop_d.json");
	std::string test_file2("../examples/model/tree/TestTop_d.json");
#else
	std::string test_file1("../../../../../examples/model/tree/TestTop.json");
	std::string test_file2("../examples/model/tree/TestTop.json");
#endif
	FILE* fp1 = fopen(test_file1.c_str(), "rb");
	FILE* fp2 = fopen(test_file2.c_str(), "rb");
	if(fp1) {
		CPPUNIT_ASSERT(p.parse(test_file1));
		Repository* r_p = Repository::get_repository();
		CPPUNIT_ASSERT(r_p->get_num_translators() == 19);
		CPPUNIT_ASSERT(r_p->get_num_channels() == 17);
		CPPUNIT_ASSERT(r_p->get_num_host_interfaces() == 17);
		CPPUNIT_ASSERT(r_p->get_num_client_interfaces() == 17);
		CPPUNIT_ASSERT(r_p->get_num_command_interfaces() == 16);
		CPPUNIT_ASSERT(r_p->get_num_inject_interfaces() == 17);
		CPPUNIT_ASSERT(r_p->get_Translator(0)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(0)->get_path()) == std::string("TestTop.EXPR.RPN.B0"));
		CPPUNIT_ASSERT(r_p->get_Translator(1)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(1)->get_path()) == std::string("TestTop.EXPR.RPN.B1"));
		CPPUNIT_ASSERT(r_p->get_Translator(2)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(2)->get_path()) == std::string("TestTop.EXPR.RPN.B2"));
		CPPUNIT_ASSERT(r_p->get_Translator(3)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(3)->get_path()) == std::string("TestTop.EXPR.RPN.B3"));
		CPPUNIT_ASSERT(r_p->get_Translator(4)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(4)->get_path()) == std::string("TestTop.EXPR.RPN.B4"));
		CPPUNIT_ASSERT(r_p->get_Translator(5)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(5)->get_path()) == std::string("TestTop.EXPR.RPN.B5"));
		CPPUNIT_ASSERT(r_p->get_Translator(6)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(6)->get_path()) == std::string("TestTop.EXPR.RPN.B6"));
		CPPUNIT_ASSERT(r_p->get_Translator(7)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(7)->get_path()) == std::string("TestTop.EXPR.RPN.B7"));
		CPPUNIT_ASSERT(r_p->get_Translator(8)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(8)->get_path()) == std::string("TestTop.EXPR.RPN.B8"));
		CPPUNIT_ASSERT(r_p->get_Translator(9)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(9)->get_path()) == std::string("TestTop.EXPR.RPN.B9"));
		CPPUNIT_ASSERT(r_p->get_Translator(10)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(10)->get_path()) == std::string("TestTop.EXPR.RPN.BPLUS"));
		CPPUNIT_ASSERT(r_p->get_Translator(11)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(11)->get_path()) == std::string("TestTop.EXPR.RPN.BMINUS"));
		CPPUNIT_ASSERT(r_p->get_Translator(12)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(12)->get_path()) == std::string("TestTop.EXPR.RPN.BMULTIPLY"));
		CPPUNIT_ASSERT(r_p->get_Translator(13)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(13)->get_path()) == std::string("TestTop.EXPR.RPN.BDIVIDE"));
		CPPUNIT_ASSERT(r_p->get_Translator(14)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(14)->get_path()) == std::string("TestTop.EXPR.RPN.BENTER"));
		CPPUNIT_ASSERT(r_p->get_Translator(15)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(15)->get_path()) == std::string("TestTop.EXPR.RPN.DISPLAY"));
		CPPUNIT_ASSERT(r_p->get_Translator(16)->get_num_children() == 16);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(16)->get_path()) == std::string("TestTop.EXPR.RPN"));
		CPPUNIT_ASSERT(r_p->get_Translator(17)->get_num_children() == 1);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(17)->get_path()) == std::string("TestTop.EXPR"));
		CPPUNIT_ASSERT(r_p->get_Translator(18)->get_num_children() == 1);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(18)->get_path()) == std::string("TestTop"));
		fclose(fp1);
	}
	else {
		CPPUNIT_ASSERT(p.parse(test_file2));
		Repository* r_p = Repository::get_repository();
		CPPUNIT_ASSERT(r_p->get_num_translators() == 19);
		CPPUNIT_ASSERT(r_p->get_num_channels() == 17);
		CPPUNIT_ASSERT(r_p->get_num_host_interfaces() == 17);
		CPPUNIT_ASSERT(r_p->get_num_client_interfaces() == 17);
		CPPUNIT_ASSERT(r_p->get_num_command_interfaces() == 16);
		CPPUNIT_ASSERT(r_p->get_num_inject_interfaces() == 17);
		CPPUNIT_ASSERT(r_p->get_Translator(0)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(0)->get_path()) == std::string("TestTop.EXPR.RPN.B0"));
		CPPUNIT_ASSERT(r_p->get_Translator(1)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(1)->get_path()) == std::string("TestTop.EXPR.RPN.B1"));
		CPPUNIT_ASSERT(r_p->get_Translator(2)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(2)->get_path()) == std::string("TestTop.EXPR.RPN.B2"));
		CPPUNIT_ASSERT(r_p->get_Translator(3)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(3)->get_path()) == std::string("TestTop.EXPR.RPN.B3"));
		CPPUNIT_ASSERT(r_p->get_Translator(4)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(4)->get_path()) == std::string("TestTop.EXPR.RPN.B4"));
		CPPUNIT_ASSERT(r_p->get_Translator(5)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(5)->get_path()) == std::string("TestTop.EXPR.RPN.B5"));
		CPPUNIT_ASSERT(r_p->get_Translator(6)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(6)->get_path()) == std::string("TestTop.EXPR.RPN.B6"));
		CPPUNIT_ASSERT(r_p->get_Translator(7)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(7)->get_path()) == std::string("TestTop.EXPR.RPN.B7"));
		CPPUNIT_ASSERT(r_p->get_Translator(8)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(8)->get_path()) == std::string("TestTop.EXPR.RPN.B8"));
		CPPUNIT_ASSERT(r_p->get_Translator(9)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(9)->get_path()) == std::string("TestTop.EXPR.RPN.B9"));
		CPPUNIT_ASSERT(r_p->get_Translator(10)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(10)->get_path()) == std::string("TestTop.EXPR.RPN.BPLUS"));
		CPPUNIT_ASSERT(r_p->get_Translator(11)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(11)->get_path()) == std::string("TestTop.EXPR.RPN.BMINUS"));
		CPPUNIT_ASSERT(r_p->get_Translator(12)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(12)->get_path()) == std::string("TestTop.EXPR.RPN.BMULTIPLY"));
		CPPUNIT_ASSERT(r_p->get_Translator(13)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(13)->get_path()) == std::string("TestTop.EXPR.RPN.BDIVIDE"));
		CPPUNIT_ASSERT(r_p->get_Translator(14)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(14)->get_path()) == std::string("TestTop.EXPR.RPN.BENTER"));
		CPPUNIT_ASSERT(r_p->get_Translator(15)->get_num_children() == 0);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(15)->get_path()) == std::string("TestTop.EXPR.RPN.DISPLAY"));
		CPPUNIT_ASSERT(r_p->get_Translator(16)->get_num_children() == 16);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(16)->get_path()) == std::string("TestTop.EXPR.RPN"));
		CPPUNIT_ASSERT(r_p->get_Translator(17)->get_num_children() == 1);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(17)->get_path()) == std::string("TestTop.EXPR"));
		CPPUNIT_ASSERT(r_p->get_Translator(18)->get_num_children() == 1);
		CPPUNIT_ASSERT(std::string(r_p->get_Translator(18)->get_path()) == std::string("TestTop"));
		fclose(fp2);
	}
}

void JSONParser_TestCases::parse_002() {
}

