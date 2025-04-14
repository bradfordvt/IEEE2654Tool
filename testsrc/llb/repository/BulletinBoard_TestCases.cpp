/*
 *    BulletinBoard_TestCases.cpp
 *
 *    Class for the BulletinBoard test cases.
 *
 *    Class for the BulletinBoard test cases.
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
static const char __date__[] = "2024/07/06";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <iostream>
#include <sstream>
#include <string>
#include "repository/BulletinBoard_TestCases.hpp"
#include "log/Logger.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( BulletinBoard_TestCases );

BulletinBoard_TestCases::BulletinBoard_TestCases( ) : CPPUNIT_NS::TestFixture( ) {
}

BulletinBoard_TestCases::~BulletinBoard_TestCases( ) {
}

BulletinBoard_TestCases::BulletinBoard_TestCases( const BulletinBoard_TestCases& tc ) : CPPUNIT_NS::TestFixture( ) {
}

BulletinBoard_TestCases& BulletinBoard_TestCases::operator=( const BulletinBoard_TestCases& tc ) {
	return *this;
}

void BulletinBoard_TestCases::setUp( ) {
	BulletinBoard* bb = BulletinBoard::get_bulletin_board();
	bb->purge_bulletin_board();
}

void BulletinBoard_TestCases::tearDown( ) {
}

void BulletinBoard_TestCases::BulletinBoard_001() {
	BulletinBoard *p = BulletinBoard::get_bulletin_board();
	CPPUNIT_ASSERT(p != NULL);
}

void BulletinBoard_TestCases::BulletinBoard_002() {
}

void BulletinBoard_TestCases::BulletinBoard_003() {
}

void BulletinBoard_TestCases::create_var_001() {
	const char m[] = "{ \"MY.KEY\": \"MY.VALUE\" }";
	BulletinBoard *p = BulletinBoard::get_bulletin_board();
	CPPUNIT_ASSERT(p != NULL);
	CPPUNIT_ASSERT(p->create_var(m) == 0);
}

void BulletinBoard_TestCases::create_var_002() {
}

void BulletinBoard_TestCases::read_var_001() {
}

void BulletinBoard_TestCases::read_var_002() {
}

void BulletinBoard_TestCases::update_var_001() {
}

void BulletinBoard_TestCases::update_var_002() {
}

void BulletinBoard_TestCases::delete_var_001() {
}

void BulletinBoard_TestCases::delete_var_002() {
}

void BulletinBoard_TestCases::dump_001() {
	std::ostringstream os;
	BulletinBoard* bb_p = BulletinBoard::get_bulletin_board();
	std::string jm("{\"DISPLAY\": \"1234\"}");
	std::string ssjm("The content of the BulletinBoard is:\n[DISPLAY] = 1234;\n");
	bb_p->create_var(jm.c_str());
	bb_p->dump(os);
	std::string display;
	display=os.str();
	std::cerr << display;
	std::cerr << "ssjm = " << ssjm << "\n";
	std::cerr << "display = " << display << "\n";
	std::cerr.flush();
	CPPUNIT_ASSERT(ssjm == display);
}

