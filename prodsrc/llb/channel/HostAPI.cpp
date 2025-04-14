/*
 *    HostAPI.cpp
 *
 *    Class to implement the Host API interface element.
 *
 *    Class to implement the Hostt API interface element.
 *    The class implements the interface used between the Channel
 *    element and the Translator node.   This file implements the
 *    body of the class.
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

#include "channel/HostAPI.hpp"
#include "repository/Repository.hpp"
#include "debug/Verify.hpp"

HostAPI::HostAPI() : hrep() {
	SWDEBUGP1( 5, Verify::CHANNEL, "HostAPI::HostAPI");
	SWDEBUG1( 5, Verify::TRACE, "HostAPI::HostAPI");
}

HostAPI::HostAPI(const HostInterfaceRep& hr) : hrep(hr) {
	SWDEBUGP2( 5, Verify::CHANNEL, "HostAPI::HostAPI",
			" const HostInterfaceRep& " );
	SWDEBUG2( 5, Verify::TRACE, "HostAPI::HostAPI",
			" const HostInterfaceRep& " );
}

HostAPI::~HostAPI() {
	SWDEBUGP1( 5, Verify::CHANNEL, "HostAPI::~HostAPI");
	SWDEBUG1( 5, Verify::TRACE, "HostAPI::~HostAPI");
}

bool operator==(const HostAPI& lhs, const HostAPI& rhs) {
	SWDEBUGP1( 5, Verify::CHANNEL, "HostAPI::operator==");
	SWDEBUG1( 5, Verify::TRACE, "HostAPI::operator==");
	return lhs.hrep == rhs.hrep;
}

// DONE
int HostAPI::send_response(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "HostAPI::send_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "HostAPI::send_response",
			" uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	int ch = hrep.get_channel();
	IEEE2654Channel* channel = rep->get_Channel(ch);
	if(channel != NULL) {
		return channel->send_response(uid, len, message);
	}
	else {
		return -1;
	}
}

// DONE
int HostAPI::handle_request(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "HostAPI::handle_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "HostAPI::handle_request",
			" uint32_t, size_t, uint8_t* " );
	// std::cerr << "uid = " << uid << std::endl;
	// std::cerr << "len = " << len << std::endl;
	// std::cerr << "message = " << (const char*)message << std::endl;
	Repository* rep = Repository::get_repository();
	int t = hrep.get_translator();
	// std::cerr << "t = " << t << std::endl;
	Translator* translator = rep->lookup_translator(t);
	// std::cerr << "translator.get_translator_uid() = " << translator.get_translator_uid() << std::endl;
	// dump(0);
	if(translator != NULL) {
		return translator->handle_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int HostAPI::update_request(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "HostAPI::update_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "HostAPI::update_request",
			" uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	int ch = hrep.get_channel();
	IEEE2654Channel* channel = rep->get_Channel(ch);
	if(channel != NULL) {
		return channel->update_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int HostAPI::handle_update_response(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "HostAPI::handle_update_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "HostAPI::handle_update_response",
			" uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	int t = hrep.get_translator();
	Translator* translator = rep->lookup_translator(t);
	if(translator != NULL) {
		return translator->handle_update_response(uid, len, message);
	}
	else {
		return -1;
	}
}

void HostAPI::dump(size_t indent) {
	SWDEBUGP2( 5, Verify::CHANNEL, "HostAPI::dump",
			" size_t " );
	SWDEBUG2( 5, Verify::TRACE, "HostAPI::dump",
			" size_t " );
	std::string ind;
        indent == 0 ? ind = std::string(indent, '\t') : ind = std::string("");
        std::string ind2(indent + 1, '\t');
        std::cerr << ind << "HostAPI contents:" << std::endl;
        std::cerr << ind2 << "name = " << hrep.get_name() << std::endl;
        std::cerr << ind2 << "channel = " << hrep.get_channel() << std::endl;
        std::cerr << ind2 << "translator = " << hrep.get_translator() << std::endl;
        std::cerr << ind2 << "protocol = " << hrep.get_protocol() << std::endl;
        std::cerr << ind2 << "key = " << hrep.get_key() << std::endl;
}
