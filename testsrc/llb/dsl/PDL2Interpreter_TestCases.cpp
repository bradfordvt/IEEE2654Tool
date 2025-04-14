/*
 *    PDL2Interpreter_TestCases.cpp
 *
 *    Class for the PDL2Interpreter test cases.
 *
 *    Class for the PDL2Interpreter test cases.
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
static const char __date__[] = "2024/09/22";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <cstdio>
#include <filesystem>
#include "log/Logger.hpp"
#include "dsl/PDL2Interpreter_TestCases.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( PDL2Interpreter_TestCases );

PDL2Interpreter_TestCases::PDL2Interpreter_TestCases( ) : CPPUNIT_NS::TestFixture( ) {
}

PDL2Interpreter_TestCases::~PDL2Interpreter_TestCases( ) {
}

PDL2Interpreter_TestCases::PDL2Interpreter_TestCases( const PDL2Interpreter_TestCases& tc ) : CPPUNIT_NS::TestFixture( ) {
}

PDL2Interpreter_TestCases& PDL2Interpreter_TestCases::operator=( const PDL2Interpreter_TestCases& tc ) {
	return *this;
}

void PDL2Interpreter_TestCases::setUp( ) {
}

void PDL2Interpreter_TestCases::tearDown( ) {
}

void PDL2Interpreter_TestCases::PDL2Interpreter_001() {
	PDL2Interpreter p;
#ifdef TEST
	CPPUNIT_ASSERT(p.filename.length() == 0);
#endif
}

void PDL2Interpreter_TestCases::PDL2Interpreter_002() {
}

void PDL2Interpreter_TestCases::PDL2Interpreter_003() {
}

void PDL2Interpreter_TestCases::iPDLLevel_001() {
	PDL2Interpreter p;
	int ret = p.Eval("iPDLLevel 0;");
	CPPUNIT_ASSERT(ret == 0);
}

void PDL2Interpreter_TestCases::iPDLLevel_002() {
	PDL2Interpreter p;
	int ret = p.Eval("iPDLLevel 1;");
	CPPUNIT_ASSERT(ret == 0);
}

void PDL2Interpreter_TestCases::iPDLLevel_003() {
	PDL2Interpreter p;
	int ret = p.Eval("iPDLLevel 2;");
	CPPUNIT_ASSERT(ret == 0);
}

#if 0
void PDL2Interpreter_TestCases::iPDLLevel_001() {
	PDL2Interpreter p;

	// find the current path
	std::filesystem::path cwd = std::filesystem::current_path();
	std::string msg("PDL2Interpreter_TestCases::parse_001(): ");
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
		CPPUNIT_ASSERT(r_p->get_num_translators() == 19);
		fclose(fp1);
	}
	else {
		CPPUNIT_ASSERT(p.parse(test_file2));
		CPPUNIT_ASSERT(r_p->get_num_translators() == 19);
		fclose(fp2);
	}
}
#endif

