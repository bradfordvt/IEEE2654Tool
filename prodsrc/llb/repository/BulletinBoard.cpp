/*
 *    BulletinBoard.cpp
 *
 *    Class to implement the BulletinBoard architectural element.
 *
 *    Class to implement the BulletinBoard architectural element.
 *    The class implements the BulletinBoard element of the modeling
 *    data representation.  It implements the representation of the
 *    CRUD method elements.
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
static const char __date__[] = "2024/07/04";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "repository/BulletinBoard.hpp"
#include "rapidjson/document.h" // rapidjason's DOM-style API
#include "log/Logger.hpp"
#include "debug/Verify.hpp"

BulletinBoard* BulletinBoard::bb = NULL;

BulletinBoard* BulletinBoard::get_bulletin_board() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "BulletinBoard::get_bulletin_board");
	SWDEBUG1( 5, Verify::TRACE, "BulletinBoard::get_bulletin_board");
	if(BulletinBoard::bb == NULL) {
		BulletinBoard::bb = new BulletinBoard();
		if(BulletinBoard::bb == NULL) {
			// TODO handle error condition
		}
	}
	return BulletinBoard::bb;
}

bool BulletinBoard::purge_bulletin_board() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "BulletinBoard::purge_bulletin_board");
	SWDEBUG1( 5, Verify::TRACE, "BulletinBoard::purge_bulletin_board");
	bulletin_board.clear();
	return true;
}

BulletinBoard::BulletinBoard() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "BulletinBoard::BulletinBoard");
	SWDEBUG1( 5, Verify::TRACE, "BulletinBoard::BulletinBoard");
}

BulletinBoard::~BulletinBoard() {
	SWDEBUGP1( 5, Verify::REPOSITORY, "BulletinBoard::~BulletinBoard");
	SWDEBUG1( 5, Verify::TRACE, "BulletinBoard::~BulletinBoard");
	purge_bulletin_board();
	delete BulletinBoard::bb;
}

int BulletinBoard::create_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "BulletinBoard::create_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "BulletinBoard::create_var",
                        " const char* " );
	int ret = __parse_message(json_message);
	if(ret == 0) {
		return __create(my_key, my_value);
	}
	return ret;
}

int BulletinBoard::__create(const std::string& key, const std::string& value) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "BulletinBoard::__create",
                        " const std::string&, const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "BulletinBoard::__create",
                        " const std::string&, const std::string& " );
	if(auto search = bulletin_board.find(key); search != bulletin_board.end()) {
		// TODO - report variable already exists
		std::string msg("BulletinBoard::__create(): Key(");
		msg += key;
		msg += ") already exists!";
		Logger* logger = Logger::get_logger();
		logger->log(ERROR, msg.c_str());
		return -1;
	}
	bulletin_board[key] = value;
	return 0;
}

const char* BulletinBoard::read_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "BulletinBoard::read_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "BulletinBoard::read_var",
                        " const char* " );
	int ret = __parse_message(json_message);
	if(ret == 0) {
		return __read(my_key);
	}
	return NULL;
}

const char* BulletinBoard::__read(const std::string& key) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "BulletinBoard::__read",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "BulletinBoard::__read",
                        " const std::string& " );
	if(auto search = bulletin_board.find(key); search != bulletin_board.end()) {
		return bulletin_board[key].c_str();
	}
	// TODO - report variable does not exists
	std::string msg("BulletinBoard::__read(): Key(");
	msg += key;
	msg += ") does not exists!";
	Logger* logger = Logger::get_logger();
	logger->log(ERROR, msg.c_str());
	return NULL;
}

int BulletinBoard::update_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "BulletinBoard::update_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "BulletinBoard::update_var",
                        " const char* " );
	int ret = __parse_message(json_message);
	if(ret == 0) {
		return __update(my_key, my_value);
	}
	return ret;
}

int BulletinBoard::__update(const std::string& key, const std::string& value) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "BulletinBoard::__update",
                        " const std::string&, const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "BulletinBoard::__update",
                        " const std::string&, const std::string& " );
	if(auto search = bulletin_board.find(key); search != bulletin_board.end()) {
		bulletin_board[key] = value;
		return 0;
	}
	// TODO - report variable does not exists
	std::string msg("BulletinBoard::__update(): Key(");
	msg += key;
	msg += ") does not exists!";
	Logger* logger = Logger::get_logger();
	logger->log(ERROR, msg.c_str());
	return -1;
}

int BulletinBoard::delete_var(const char* json_message) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "BulletinBoard::delete_var",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "BulletinBoard::delete_var",
                        " const char* " );
	int ret = __parse_message(json_message);
	if(ret == 0) {
		return __delete(my_key);
	}
	return ret;
}

int BulletinBoard::__delete(const std::string& key) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "BulletinBoard::__delete",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "BulletinBoard::__delete",
                        " const std::string& " );
	if(auto search = bulletin_board.find(key); search != bulletin_board.end()) {
		bulletin_board.erase(search);
		return 0;
	}
	// TODO - report variable does not exists
	std::string msg("BulletinBoard::__delete(): Key(");
	msg += key;
	msg += ") does not exists!";
	Logger* logger = Logger::get_logger();
	logger->log(ERROR, msg.c_str());
	return -1;
}

int BulletinBoard::__parse_message(const char* json_message) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "BulletinBoard::__parse_message",
                        " const char* " );
	SWDEBUG2( 5, Verify::TRACE, "BulletinBoard::__parse_message",
                        " const char* " );
	rapidjson::Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.

        // In-situ parsing, decode strings directly in the source string.
        // Source must be string.
	std::string buffer(json_message);
	char *writable = new char[buffer.size() + 1];
	std::copy(buffer.begin(), buffer.end(), writable);
	writable[buffer.size()] = '\0';
        // char buffer[strlen(json_message)];
        // memcpy(buffer, json_message, sizeof(json_message));
	// buffer[sizeof(json_message)] = '\0';
        // if(document.ParseInsitu(buffer).HasParseError())
        if(document.Parse<0>(writable).HasParseError())
        {
		// TODO - handle error
		std::string msg("BulletinBoard::__parse_message(): json_message(");
		msg += json_message;
		msg += ") is not a valid JSON document!";
		msg += "\nwritable = ";
		msg += writable;
		msg += "After logger\n";
		Logger* logger = Logger::get_logger();
		logger->log(ERROR, msg.c_str());
		delete writable;
                return -1;
        }
        // Parsing to document succeeded

        // 2. Access values in document.
        if(!document.IsObject())
        {
		// TODO - handle error
		std::string msg("BulletinBoard::__parse_message(): json_message(");
		msg += json_message;
		msg += ") document is not an object!";
		Logger* logger = Logger::get_logger();
		logger->log(ERROR, msg.c_str());
		delete writable;
                return -1;
        }
	int cnt = 0;
	for (rapidjson::Value::ConstMemberIterator itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr, cnt++) {
		if(cnt > 1) {
			// TODO - report error
			// Too many variables to set
			std::string msg("BulletinBoard::__parse_message(): json_message(");
			msg += json_message;
			msg += ") contains multiple variables to set!";
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
		delete writable;
			return -1;
		}
		my_key = itr->name.GetString();
		my_value = itr->value.GetString();
	}
	delete writable;
	return 0;
}

void BulletinBoard::dump( std::ostream& os) {
	SWDEBUGP2( 5, Verify::REPOSITORY, "BulletinBoard::dump",
                        " std::ostream& " );
	SWDEBUG2( 5, Verify::TRACE, "BulletinBoard::dump",
                        " std::ostream& " );
	std::string msg("The content of the BulletinBoard is:");
	for(const auto& [key, value] : bulletin_board) {
		msg += '[';
	        msg += key;
	        msg += "] = ";
	        msg += value;
	        msg += "; \n";
	}
	os << "The content of the BulletinBoard is:\n";
	for(const auto& [key, value] : bulletin_board) {
		os << '[' << key << "] = " << value << ";\n";
		msg += "[" + key + "] = " + value + ";\n";
	}
	// os << "DONE";
	Logger* logger = Logger::get_logger();
	logger->log(ERROR, msg.c_str());
}

