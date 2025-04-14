/*
 *    TCLInterpreter_TestCases.cpp
 *
 *    Class for the TCLInterpreter test cases.
 *
 *    Class for the TCLInterpreter test cases.
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
#include "dsl/TCLInterpreter.hpp"
#include "dsl/TCLInterpreter_TestCases.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( TCLInterpreter_TestCases );

TCLInterpreter_TestCases::TCLInterpreter_TestCases( ) : CPPUNIT_NS::TestFixture( ) {
}

TCLInterpreter_TestCases::~TCLInterpreter_TestCases( ) {
}

TCLInterpreter_TestCases::TCLInterpreter_TestCases( const TCLInterpreter_TestCases& tc ) : CPPUNIT_NS::TestFixture( ) {
}

TCLInterpreter_TestCases& TCLInterpreter_TestCases::operator=( const TCLInterpreter_TestCases& tc ) {
	return *this;
}

void TCLInterpreter_TestCases::setUp( ) {
}

void TCLInterpreter_TestCases::tearDown( ) {
}

void TCLInterpreter_TestCases::TCLInterpreter_001() {
	TCLInterpreter p;
#ifdef TEST
	CPPUNIT_ASSERT(p.filename.length() == 0);
#endif
}

void TCLInterpreter_TestCases::TCLInterpreter_002() {
}

void TCLInterpreter_TestCases::TCLInterpreter_003() {
}

void TCLInterpreter_TestCases::set_001() {
	// find the current path
	std::filesystem::path cwd = std::filesystem::current_path();
	std::string msg("TCLInterpreter_TestCases::set_001(): ");
	msg += "Current working directory for test is: ";
	msg += cwd.string();
	std::cerr << msg << std::endl;

#if 0
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
#endif
	char tcl_cmd[] = "set v \"foobar\"\n";
	TCLInterpreter interp;
	interp.RegisterCoreCommands();
	int rcode = interp.Eval(tcl_cmd);
	if(rcode != retcode::PICOL_OK) {
		std::cerr << "set_001() failed!\nrcode = " << rcode << std::endl;
		std::cerr << "result = " << interp.GetResult() << std::endl;
	}
	CPPUNIT_ASSERT(rcode == retcode::PICOL_OK);
}

void TCLInterpreter_TestCases::puts_001() {
}

void TCLInterpreter_TestCases::puts_002() {
}

