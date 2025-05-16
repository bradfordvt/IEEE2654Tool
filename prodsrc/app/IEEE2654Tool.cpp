/*
 *    IEEE2654Tool.cpp
 *
 *    Top level of the IEEE2654Tool application.
 *
 *    Top level of the IEEE2654Tool application.
 *    This file is the entry point into the IEEE2654Tool EDA application.
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
static const char __date__[] = "2024/03/03";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include <string>
#include <iostream>
#include <getopt.h>
#include "IEEE2654Tool.hpp"
#include "builder/JSONBuilder.hpp"
#include "dsl/TestInterpreter.hpp"
#include "debug/Verify.hpp"

#define TRACE_INIT_LEVEL 10

void displayHelp() {
	std::cout << "IEEE2654Tool -m<module_name> -t<test_name>" << std::endl;
	std::cout << "\t-h or -? to print this help message" << std::endl;
	std::cout << "\twhere <module_name> is the name of the JSON file without extension" << std::endl;
	std::cout << "\tand" << std::endl;
	std::cout << "\twhere <test_name> is the name of the test program file with extension" << std::endl;
	std::cout << "\te.g., test1_calculator.py" << std::endl;
}

int doBatchProcess(const std::string& module_name, const std::string& test_name) {
	JSONBuilder jb;
	int ret = jb.build_root(module_name);
	if(ret == 0) {
		// IEEE2654Tree model has now been made successfully
		// Now apply the test to that model
		TestInterpreter ti;
		std::vector<std::string> argv;
		ret = ti.runTest(test_name, argv);
		if(ret == 0) {
			return 0;
		}
		else {
			return ret;
		}
	}
	else {
		return ret;
	}
}

int doBatchMode(int argc, char **argv) {
	int c;
	std::string module_name;
	std::string test_name;
	while((c = getopt(argc, argv, "m:t:h")) != -1) {
		switch(c) {
			case '?':
			case 'h':
			default:
				displayHelp();
				break;
			case 'm':
				module_name = optarg;
				break;
			case 't':
				test_name = optarg;
				break;
		}
	}
	if(module_name.length() && test_name.length()) {
		int ret = doBatchProcess(module_name, test_name);
		if(ret == -1) {
			displayHelp();
			return -1;
		}
		else {
			return ret;
		}
	}
	else {
		displayHelp();
		return -1;
	}
}

int main(int argc, char **argv) {
	if(argc > 1) { // The user wants to run in batch mode instead of GUI mode
		static const char Func_name[ ] = "main";
		SwDebug trace_init;
		trace_init.setValue( TRACE_INIT_LEVEL, Verify::TRACE );
		SwDebug trace( 5, Verify::TRACE, Func_name );
		// Batch mode
		int ret = doBatchMode(argc, argv);
		return ret;
	}
	else {
		// GUI mode
		return -1;
	}
	return 0;
}

