/*
 *    IEEE2654Channel.cpp
 *
 *    Class to implement the Channel architectural element.
 *
 *    Class to implement the Channel architectural element.
 *    The class implements the communications Channel of
 *    the message layer.  This is the mechanism that transports
 *    IEEE2654Message carrier wrapper messages from one Translator
 *    node to another.  This file implements the body of the class.
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

#include "channel/IEEE2654Channel.hpp"
#include "channel/HostAPI.hpp"
#include "channel/ClientAPI.hpp"
#include "repository/Repository.hpp"
#include "debug/Verify.hpp"


IEEE2654Channel::IEEE2654Channel() : crep() {
	SWDEBUGP1( 5, Verify::CHANNEL, "IEEE2654Channel::IEEE2654Channel");
	SWDEBUG1( 5, Verify::TRACE, "IEEE2654Channel::IEEE2654Channel");
}

IEEE2654Channel::IEEE2654Channel(const ChannelRep& cr) : crep(cr) {
	SWDEBUGP2( 5, Verify::CHANNEL, "IEEE2654Channel::IEEE2654Channel",
			" const ChannelRep& " );
	SWDEBUG2( 5, Verify::TRACE, "IEEE2654Channel::IEEE2654Channel",
			" const ChannelRep& " );
}

IEEE2654Channel::~IEEE2654Channel() {
	SWDEBUGP1( 5, Verify::CHANNEL, "IEEE2654Channel::~IEEE2654Channel");
	SWDEBUG1( 5, Verify::TRACE, "IEEE2654Channel::~IEEE2654Channel");
}

bool operator==(const IEEE2654Channel& lhs, const IEEE2654Channel& rhs) {
	SWDEBUGP1( 5, Verify::CHANNEL, "IEEE2654Channel::operator==");
	SWDEBUG1( 5, Verify::TRACE, "IEEE2654Channel::operator==");
	return lhs.crep == rhs.crep;
}

// DONE
int IEEE2654Channel::send_request(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "IEEE2654Channel::send_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "IEEE2654Channel::send_request",
			" uint32_t, size_t, uint8_t* " );
	// std::cerr << "uid = " << uid << std::endl;
	// std::cerr << "len = " << len << std::endl;
	// std::cerr << "message = " << (const char*)message << std::endl;
	// dump(0);
	return handle_request(uid, len, message);
}

// DONE
int IEEE2654Channel::send_response(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "IEEE2654Channel::send_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "IEEE2654Channel::send_response",
			" uint32_t, size_t, uint8_t* " );
	return handle_response(uid, len, message);
}

// DONE
int IEEE2654Channel::handle_request(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "IEEE2654Channel::handle_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "IEEE2654Channel::handle_request",
			" uint32_t, size_t, uint8_t* " );
	// std::cerr << "uid = " << uid << std::endl;
	// std::cerr << "len = " << len << std::endl;
	// std::cerr << "message = " << (const char*)message << std::endl;
	Repository* rep = Repository::get_repository();
	int h = crep.get_host_interface();
	// std::cerr << "h = " << h << std::endl;
	HostAPI* host_p = rep->get_HostAPI(h);
	// std::cerr << "host_p->translator = " << host_p->get_translator() << std::endl;
	// dump(0);
	if(host_p != NULL) {
		return host_p->handle_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int IEEE2654Channel::handle_update_request(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "IEEE2654Channel::handle_update_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "IEEE2654Channel::handle_update_request",
			" uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	int c = crep.get_client_interface();
	ClientAPI* client_p = rep->get_ClientAPI(c);
	if(client_p != NULL) {
		return client_p->handle_update_request(uid, len, message);
	}
	else {
		return -1;
	}
}

// DONE
int IEEE2654Channel::handle_response(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "IEEE2654Channel::handle_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "IEEE2654Channel::handle_response",
			" uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	int c = crep.get_client_interface();
	ClientAPI* client_p = rep->get_ClientAPI(c);
	if(client_p != NULL) {
		return client_p->handle_response(uid, len, message);
	}
	else {
		return -1;
	}
}

int IEEE2654Channel::update_request(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "IEEE2654Channel::update_request",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "IEEE2654Channel::update_request",
			" uint32_t, size_t, uint8_t* " );
	return handle_update_request(uid, len, message);
}

int IEEE2654Channel::send_update_response(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "IEEE2654Channel::send_update_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "IEEE2654Channel::send_update_response",
			" uint32_t, size_t, uint8_t* " );
	return handle_update_response(uid, len, message);
}

int IEEE2654Channel::handle_update_response(uint32_t uid, size_t len, uint8_t* message) {
	SWDEBUGP2( 5, Verify::CHANNEL, "IEEE2654Channel::handle_update_response",
			" uint32_t, size_t, uint8_t* " );
	SWDEBUG2( 5, Verify::TRACE, "IEEE2654Channel::handle_update_response",
			" uint32_t, size_t, uint8_t* " );
	Repository* rep = Repository::get_repository();
	int h = crep.get_host_interface();
	HostAPI* host_p = rep->get_HostAPI(h);
	if(host_p != NULL) {
		return host_p->handle_update_response(uid, len, message);
	}
	else {
		return -1;
	}
}

HostAPI* IEEE2654Channel::get_HostAPI() {
	SWDEBUGP1( 5, Verify::CHANNEL, "IEEE2654Channel::get_HostAPI");
	SWDEBUG1( 5, Verify::TRACE, "IEEE2654Channel::get_HostAPI");
	Repository* rep = Repository::get_repository();
	int h = crep.get_host_interface();
	return rep->get_HostAPI(h);
}

ClientAPI* IEEE2654Channel::get_ClientAPI() {
	SWDEBUGP1( 5, Verify::CHANNEL, "IEEE2654Channel::get_ClientAPI");
	SWDEBUG1( 5, Verify::TRACE, "IEEE2654Channel::get_ClientAPI");
	Repository* rep = Repository::get_repository();
	int c = crep.get_client_interface();
	return rep->get_ClientAPI(c);
}

void IEEE2654Channel::dump(size_t indent) {
	SWDEBUGP2( 5, Verify::CHANNEL, "IEEE2654Channel::dump",
			" size_t ");
	SWDEBUG2( 5, Verify::TRACE, "IEEE2654Channel::dump",
			" size_t ");
	std::string ind;
        indent == 0 ? ind = std::string(indent, '\t') : ind = std::string("");
        std::string ind2(indent + 1, '\t');
        std::cerr << ind << "IEEE2654Channel contents:" << std::endl;
        std::cerr << ind2 << "name = " << crep.get_name() << std::endl;
        std::cerr << ind2 << "method = " << crep.get_method() << std::endl;
        std::cerr << ind2 << "client_interface = " << crep.get_client_interface() << std::endl;
        std::cerr << ind2 << "host_interface = " << crep.get_host_interface() << std::endl;
        std::cerr << ind2 << "protocol = " << crep.get_protocol() << std::endl;
        std::cerr << ind2 << "key = " << crep.get_key() << std::endl;
}

