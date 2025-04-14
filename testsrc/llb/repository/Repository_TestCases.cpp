/*
 *    Repository_TestCases.cpp
 *
 *    Class for the Repository test cases.
 *
 *    Class for the Repository test cases.
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

#include "repository/Repository_TestCases.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( Repository_TestCases );

Repository_TestCases::Repository_TestCases( ) : CPPUNIT_NS::TestFixture( ) {
}

Repository_TestCases::~Repository_TestCases( ) {
}

Repository_TestCases::Repository_TestCases( const Repository_TestCases& tc ) : CPPUNIT_NS::TestFixture( ) {
}

Repository_TestCases& Repository_TestCases::operator=( const Repository_TestCases& tc ) {
	return *this;
}

void Repository_TestCases::setUp( ) {
}

void Repository_TestCases::tearDown( ) {
}

void Repository_TestCases::Repository_001() {
	Repository *p = Repository::get_repository();
	CPPUNIT_ASSERT(p != NULL);
}

void Repository_TestCases::Repository_002() {
}

void Repository_TestCases::Repository_003() {
}

void Repository_TestCases::parse_001() {
}

void Repository_TestCases::parse_002() {
}

