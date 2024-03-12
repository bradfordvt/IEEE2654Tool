/*
 *    Logger.hpp
 *
 *    Class to implement the logging architectural element.
 *
 *    Class to implement the logging architectural element.
 *    The class implements the logging element of the application.
 *    This file implements the body of the Logger class.
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
static const char __date__[] = "2024/02/20";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "log/Logger.hpp"
#include <stdint.h>
#include <stddef.h>

Logger* Logger::inst = NULL;

Logger* Logger::get_logger() {
	if(Logger::inst == NULL) {
		Logger::inst = new Logger();
	}
	return Logger::inst;
}

Logger::Logger() {
}

Logger::~Logger() {
	std::vector<std::ostream*>::iterator it;
	for(; it != Logger::os_list.end(); ++it) {
		delete *it;
	}
}

void Logger::log(LOG_TYPE type, const char* message) {
	std::vector<std::ostream*>::iterator it;
	if(type == ERROR) {
		std::cerr << "ERROR: " << message << "\n";
	}
	else if(type == WARNING) {
		std::cerr << "WARNING: " << message << "\n";
	}
	else if(type == DEBUG) {
		std::cerr << "DEBUG: " << message << "\n";
	}
	else if(type == NOTICE) {
		std::cerr << "NOTICE: " << message << "\n";
	}
	std::cerr.flush();
	it = os_list.begin();
	for( ; it != Logger::os_list.end(); ++it) {
		if(type == ERROR) {
			**it << "ERROR: " << message << "\n";
		}
		else if(type == WARNING) {
			**it << "WARNING: " << message << "\n";
		}
		else if(type == DEBUG) {
			**it << "DEBUG: " << message << "\n";
		}
		else if(type == NOTICE) {
			**it << "NOTICE: " << message << "\n";
		}
	}
}

void Logger::add_stream(std::ostream* os) {
	Logger::os_list.push_back(os);
}
