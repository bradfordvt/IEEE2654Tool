/*
 *    ClientAPI.cpp
 *
 *    Class to implement the Client API interface element.
 *
 *    Class to implement the Client API interface element.
 *    The class implements the interface used between the Channel
 *    element and the Translator node.  This file implements the
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

#include "channel/ClientAPI.hpp"
#include "repository/Repository.hpp"
#include "debug/Verify.hpp"

ClientAPI::ClientAPI() : crep() {
	SWDEBUGP1( 5, Verify::CHANNEL, "ClientAPI::ClientAPI");
	SWDEBUG1( 5, Verify::TRACE, "ClientAPI::ClientAPI");
}

ClientAPI::ClientAPI(const ClientInterfaceRep& cr) : crep(cr) {
	SWDEBUGP2( 5, Verify::CHANNEL, "ClientAPI::ClientAPI",
			" const ClientInterfaceRep& ");
	SWDEBUG2( 5, Verify::TRACE, "ClientAPI::ClientAPI",
			" const ClientInterfaceRep& ");
}

ClientAPI::~ClientAPI() {
	SWDEBUGP1( 5, Verify::CHANNEL, "ClientAPI::~ClientAPI");
	SWDEBUG1( 5, Verify::TRACE, "ClientAPI::~ClientAPI");
}

bool operator==(const ClientAPI& lhs, const ClientAPI& rhs) {
	SWDEBUGP2( 5, Verify::CHANNEL, "ClientAPI::ClientAPI",
			" const ClientAPI&, const ClientAPI& ");
	SWDEBUG2( 5, Verify::TRACE, "ClientAPI::ClientAPI",
			" const ClientAPI&, const ClientAPI& ");
	return lhs.crep == rhs.crep;
}

int ClientAPI::send_request(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "ClientAPI::send_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "ClientAPI::send_request",
			" uint32_t, size_t, uint8_t* " );
	// std::cerr << "uid = " << uid << std::endl;
	// std::cerr << "len = " << len << std::endl;
	// std::cerr << "message = " << (const char*)message << std::endl;
	IEEE2654Channel* channel = get_Channel();
	// std::cerr << "channel->translator = " << channel->get_translator() << std::endl;
	// dump(0);
	if(channel != NULL) {
		return channel->send_request(uid, len, message);
	}
	else {
		return -1;
	}
}

// DONE
int ClientAPI::handle_response(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "ClientAPI::handle_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "ClientAPI::handle_response",
			" uint32_t, size_t, uint8_t* " );
	Translator* translator = get_Translator();
	if(translator != NULL) {
		return translator->handle_response(uid, len, message);
	}
	else {
		return -1;
	}
}

int ClientAPI::handle_update_request(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "ClientAPI::handle_update_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "ClientAPI::handle_update_request",
			" uint32_t, size_t, uint8_t* " );
	Translator* translator = get_Translator();
	if(translator != NULL) {
		return translator->handle_update_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int ClientAPI::send_update_response(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "ClientAPI::send_update_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "ClientAPI::send_update_response",
			" uint32_t, size_t, uint8_t* " );
	IEEE2654Channel* channel = get_Channel();
	if(channel != NULL) {
		return channel->send_update_response(uid, len, message);
	}
	else {
		return -1;
	}
}

IEEE2654Channel* ClientAPI::get_Channel() {
	SWDEBUGP1( 5, Verify::CHANNEL, "ClientAPI::get_Channel");
	SWDEBUG1( 5, Verify::TRACE, "ClientAPI::get_Channel");
	Repository* rep = Repository::get_repository();
	int ch = crep.get_channel();
	IEEE2654Channel* channel = rep->get_Channel(ch);
	return channel;
}

Translator* ClientAPI::get_Translator() {
	SWDEBUGP1( 5, Verify::CHANNEL, "ClientAPI::get_Translator");
	SWDEBUG1( 5, Verify::TRACE, "ClientAPI::get_Translator");
	Repository* rep = Repository::get_repository();
	int t = crep.get_translator();
	Translator* translator = rep->lookup_translator(t);
	return translator;
}

void ClientAPI::dump(size_t indent) {
	SWDEBUGP2( 5, Verify::CHANNEL, "ClientAPI::dump",
			" size_t " );
	SWDEBUG2( 5, Verify::TRACE, "ClientAPI::dump",
			" size_t " );
	std::string ind;
        indent == 0 ? ind = std::string(indent, '\t') : ind = std::string("");
        std::string ind2(indent + 1, '\t');
        std::cerr << ind << "ClientAPI contents:" << std::endl;
        std::cerr << ind2 << "name = " << crep.get_name() << std::endl;
        std::cerr << ind2 << "channel = " << crep.get_channel() << std::endl;
        std::cerr << ind2 << "translator = " << crep.get_translator() << std::endl;
        std::cerr << ind2 << "protocol = " << crep.get_protocol() << std::endl;
        std::cerr << ind2 << "key = " << crep.get_key() << std::endl;
}
