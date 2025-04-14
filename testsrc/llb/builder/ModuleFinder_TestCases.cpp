/*
 *    ModuleFinder_TestCases.cpp
 *
 *    Class for the ModuleFinder test cases.
 *
 *    Class for the ModuleFinder test cases.
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
#include "builder/ModuleFinder.hpp"
#include "builder/ModuleFinder_TestCases.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( ModuleFinder_TestCases );

ModuleFinder_TestCases::ModuleFinder_TestCases( ) : CPPUNIT_NS::TestFixture( ) {
}

ModuleFinder_TestCases::~ModuleFinder_TestCases( ) {
}

ModuleFinder_TestCases::ModuleFinder_TestCases( const ModuleFinder_TestCases& tc ) : CPPUNIT_NS::TestFixture( ) {
}

ModuleFinder_TestCases& ModuleFinder_TestCases::operator=( const ModuleFinder_TestCases& tc ) {
	return *this;
}

void ModuleFinder_TestCases::setUp( ) {
}

void ModuleFinder_TestCases::tearDown( ) {
}

void ModuleFinder_TestCases::ModuleFinder_001() {
	ModuleFinder p;
#ifdef TEST
	CPPUNIT_ASSERT(p.filename.length() == 0);
#endif
}

void ModuleFinder_TestCases::ModuleFinder_002() {
}

void ModuleFinder_TestCases::ModuleFinder_003() {
}

void ModuleFinder_TestCases::find_modules_001() {
	ModuleFinder* mb_p = ModuleFinder::get_ModuleFinder();
	std::string test_dir1("../../../../../examples/model/mdl");
	std::string test_dir2("../examples/model/mdl");
	DIR* di1 = opendir(test_dir1.c_str());
	DIR* di2 = opendir(test_dir2.c_str());
	std::string mname;
	std::string fname;
	std::string mod;
	std::string filename;
	if(di1) {
		closedir(di1);
		std::filesystem::path dir(test_dir1);
		int ret = mb_p->find_modules(dir);
		CPPUNIT_ASSERT(ret == 0);
		fname = test_dir1 + "/" + "BUTTON.mdl";
		mname = "button";
		mod = mb_p->get_module(fname);
		filename = mb_p->get_filename(mname);
		CPPUNIT_ASSERT(mod == mname);
		CPPUNIT_ASSERT(filename == fname);
		fname = test_dir1 + "/" + "TestController.mdl";
		mname = "TestController";
		mod = mb_p->get_module(fname);
		filename = mb_p->get_filename(mname);
		CPPUNIT_ASSERT(mod == mname);
		CPPUNIT_ASSERT(filename == fname);
		fname = test_dir1 + "/" + "TestIntermediate.mdl";
		mname = "TestIntermediate";
		mod = mb_p->get_module(fname);
		filename = mb_p->get_filename(mname);
		CPPUNIT_ASSERT(mod == mname);
		CPPUNIT_ASSERT(filename == fname);
		fname = test_dir1 + "/" + "TestLeaf.mdl";
		mname = "TestLeaf";
		mod = mb_p->get_module(fname);
		filename = mb_p->get_filename(mname);
		CPPUNIT_ASSERT(mod == mname);
		CPPUNIT_ASSERT(filename == fname);
		fname = test_dir1 + "/" + "TestTop.mdl";
		mname = "TestTop";
		mod = mb_p->get_module(fname);
		filename = mb_p->get_filename(mname);
		CPPUNIT_ASSERT(mod == mname);
		CPPUNIT_ASSERT(filename == fname);
	}
	else {
		closedir(di2);
		std::filesystem::path dir(test_dir2);
		int ret = mb_p->find_modules(dir);
		CPPUNIT_ASSERT(ret == 0);
		fname = test_dir2 + "/" + "BUTTON.mdl";
		mname = "button";
		mod = mb_p->get_module(fname);
		filename = mb_p->get_filename(mname);
		CPPUNIT_ASSERT(mod == mname);
		CPPUNIT_ASSERT(filename == fname);
		fname = test_dir2 + "/" + "TestController.mdl";
		mname = "TestController";
		mod = mb_p->get_module(fname);
		filename = mb_p->get_filename(mname);
		CPPUNIT_ASSERT(mod == mname);
		CPPUNIT_ASSERT(filename == fname);
		fname = test_dir2 + "/" + "TestIntermediate.mdl";
		mname = "TestIntermediate";
		// std::cerr << "mname = " << mname << std::endl;
		// std::cerr << "mname.length() = " << mname.length() << std::endl;
		mod = mb_p->get_module(fname);
		// std::cerr << "mod = " << mod << std::endl;
		// std::cerr << "mod.length() = " << mod.length() << std::endl;
		filename = mb_p->get_filename(mname);
		CPPUNIT_ASSERT(mod == mname);
		CPPUNIT_ASSERT(filename == fname);
		fname = test_dir2 + "/" + "TestLeaf.mdl";
		mname = "TestLeaf";
		mod = mb_p->get_module(fname);
		filename = mb_p->get_filename(mname);
		CPPUNIT_ASSERT(mod == mname);
		CPPUNIT_ASSERT(filename == fname);
		fname = test_dir2 + "/" + "TestTop.mdl";
		mname = "TestTop";
		mod = mb_p->get_module(fname);
		filename = mb_p->get_filename(mname);
		CPPUNIT_ASSERT(mod == mname);
		CPPUNIT_ASSERT(filename == fname);
	}
}

void ModuleFinder_TestCases::find_module_001() {
	ModuleFinder* mb_p = ModuleFinder::get_ModuleFinder();
	std::string test_file1("../../../../../examples/model/mdl/BUTTON.mdl");
	std::string test_file2("../examples/model/mdl/BUTTON.mdl");
	FILE* fp1 = fopen(test_file1.c_str(), "rb");
	FILE* fp2 = fopen(test_file2.c_str(), "rb");
	std::string mod;
	if(fp1) {
		mod = mb_p->find_module(test_file1.c_str());
		CPPUNIT_ASSERT(mod == std::string("button"));
		fclose(fp1);
	}
	else {
		mod = mb_p->find_module(test_file2.c_str());
		CPPUNIT_ASSERT(mod == std::string("button"));
		fclose(fp2);
	}
}

void ModuleFinder_TestCases::find_module_002() {
	ModuleFinder* mb_p = ModuleFinder::get_ModuleFinder();
	std::string test_file1("../../../../../examples/model/mdl/TestController.mdl");
	std::string test_file2("../examples/model/mdl/TestController.mdl");
	FILE* fp1 = fopen(test_file1.c_str(), "rb");
	FILE* fp2 = fopen(test_file2.c_str(), "rb");
	std::string mod;
	if(fp1) {
		mod = mb_p->find_module(test_file1.c_str());
		CPPUNIT_ASSERT(mod == std::string("TestController"));
		fclose(fp1);
	}
	else {
		mod = mb_p->find_module(test_file2.c_str());
		CPPUNIT_ASSERT(mod == std::string("TestController"));
		fclose(fp2);
	}
}

void ModuleFinder_TestCases::find_module_003() {
	ModuleFinder* mb_p = ModuleFinder::get_ModuleFinder();
	std::string test_file1("../../../../../examples/model/mdl/TestIntermediate.mdl");
	std::string test_file2("../examples/model/mdl/TestIntermediate.mdl");
	FILE* fp1 = fopen(test_file1.c_str(), "rb");
	FILE* fp2 = fopen(test_file2.c_str(), "rb");
	std::string mod;
	if(fp1) {
		mod = mb_p->find_module(test_file1.c_str());
		CPPUNIT_ASSERT(mod == std::string("TestIntermediate"));
		fclose(fp1);
	}
	else {
		mod = mb_p->find_module(test_file2.c_str());
		CPPUNIT_ASSERT(mod == std::string("TestIntermediate"));
		fclose(fp2);
	}
}

void ModuleFinder_TestCases::find_module_004() {
	ModuleFinder* mb_p = ModuleFinder::get_ModuleFinder();
	std::string test_file1("../../../../../examples/model/mdl/TestLeaf.mdl");
	std::string test_file2("../examples/model/mdl/TestLeaf.mdl");
	FILE* fp1 = fopen(test_file1.c_str(), "rb");
	FILE* fp2 = fopen(test_file2.c_str(), "rb");
	std::string mod;
	if(fp1) {
		mod = mb_p->find_module(test_file1.c_str());
		CPPUNIT_ASSERT(mod == std::string("TestLeaf"));
		fclose(fp1);
	}
	else {
		mod = mb_p->find_module(test_file2.c_str());
		CPPUNIT_ASSERT(mod == std::string("TestLeaf"));
		fclose(fp2);
	}
}

void ModuleFinder_TestCases::find_module_005() {
	ModuleFinder* mb_p = ModuleFinder::get_ModuleFinder();
	std::string test_file1("../../../../../examples/model/mdl/TestTop.mdl");
	std::string test_file2("../examples/model/mdl/TestTop.mdl");
	FILE* fp1 = fopen(test_file1.c_str(), "rb");
	FILE* fp2 = fopen(test_file2.c_str(), "rb");
	std::string mod;
	if(fp1) {
		mod = mb_p->find_module(test_file1.c_str());
		CPPUNIT_ASSERT(mod == std::string("TestTop"));
		fclose(fp1);
	}
	else {
		mod = mb_p->find_module(test_file2.c_str());
		CPPUNIT_ASSERT(mod == std::string("TestTop"));
		fclose(fp2);
	}
}

