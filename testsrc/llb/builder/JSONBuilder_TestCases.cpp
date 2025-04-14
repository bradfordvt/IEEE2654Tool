/*
 *    JSONBuilder_TestCases.cpp
 *
 *    Class for the JSONBuilder test cases.
 *
 *    Class for the JSONBuilder test cases.
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
static const char __date__[] = "2024/08/24";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <dirent.h>
#include <cstdio>
#include <cstring>
#include "stdlib.h" // for putenv()
#include "builder/JSONBuilder.hpp"
#include "builder/JSONBuilder_TestCases.hpp"
#include "repository/Repository.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( JSONBuilder_TestCases );

JSONBuilder_TestCases::JSONBuilder_TestCases( ) : CPPUNIT_NS::TestFixture( ) {
}

JSONBuilder_TestCases::~JSONBuilder_TestCases( ) {
}

JSONBuilder_TestCases::JSONBuilder_TestCases( const JSONBuilder_TestCases& tc ) : CPPUNIT_NS::TestFixture( ) {
}

JSONBuilder_TestCases& JSONBuilder_TestCases::operator=( const JSONBuilder_TestCases& tc ) {
	return *this;
}

void JSONBuilder_TestCases::setUp( ) {
}

void JSONBuilder_TestCases::tearDown( ) {
}

void JSONBuilder_TestCases::JSONBuilder_001() {
	char mpath[] = "IEEE2654MODULES=${HOME}/VisualStudioCode/IEEE2654Tool/examples/model/tree";

	putenv(mpath);
	JSONBuilder p;
#ifdef TEST
	CPPUNIT_ASSERT(p.filename.length() == 0);
#endif
}

void JSONBuilder_TestCases::JSONBuilder_002() {
}

void JSONBuilder_TestCases::JSONBuilder_003() {
}

void JSONBuilder_TestCases::build_root_001() {
	char mpath[] = "IEEE2654MODULES=${HOME}/VisualStudioCode/IEEE2654Tool/examples/model/tree";

	putenv(mpath);
	JSONBuilder jb;

// #ifdef DEBUG
#if 1
	int ret = jb.build_root(std::string("TestTop_d"));
	CPPUNIT_ASSERT(ret == 0);
	Translator* root_p = jb.get_root();
	CPPUNIT_ASSERT(!strcmp(root_p->get_module_name(), "TestTop"));
	CPPUNIT_ASSERT(!strcmp(root_p->get_instance_name(), "TestTop"));
#else
	int ret = jb.build_root(std::string("TestTop"));
	CPPUNIT_ASSERT(ret == 0);
	Translator* root_p = jb.get_root();
	CPPUNIT_ASSERT(!strcmp(root_p->get_module_name(), "TestTop"));
	CPPUNIT_ASSERT(!strcmp(root_p->get_instance_name(), "TestTop"));
#endif
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
}

