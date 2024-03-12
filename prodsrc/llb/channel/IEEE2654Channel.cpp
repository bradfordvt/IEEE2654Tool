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


IEEE2654Channel::IEEE2654Channel() {
	client_p = NULL;
	host_p = NULL;
}

IEEE2654Channel::~IEEE2654Channel() {

}

int IEEE2654Channel::send_request(uint32_t uid, size_t len, uint8_t* message) {
	return handle_request(uid, len, message);
}

int IEEE2654Channel::send_response(uint32_t uid, size_t len, uint8_t* message) {
	return handle_response(uid, len, message);
}

int IEEE2654Channel::handle_request(uint32_t uid, size_t len, uint8_t* message) {
	if(host_p != NULL) {
		return host_p->handle_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int IEEE2654Channel::handle_update_request(uint32_t uid, size_t len, uint8_t* message) {
	if(client_p != NULL) {
		return client_p->handle_update_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int IEEE2654Channel::handle_response(uint32_t uid, size_t len, uint8_t* message) {
	if(client_p != NULL) {
		return client_p->handle_response(uid, len, message);
	}
	else {
		return -1;
	}
}

int IEEE2654Channel::update_request(uint32_t uid, size_t len, uint8_t* message) {
	return handle_update_request(uid, len, message);
}

int IEEE2654Channel::send_update_response(uint32_t uid, size_t len, uint8_t* message) {
	return handle_update_response(uid, len, message);
}

int IEEE2654Channel::handle_update_response(uint32_t uid, size_t len, uint8_t* message) {
	if(host_p != NULL) {
		return host_p->handle_update_response(uid, len, message);
	}
	else {
		return -1;
	}
}

int IEEE2654Channel::set_client(ClientAPI& capi) {
	client_p = &capi;
	return 0;
}

int IEEE2654Channel::set_host(HostAPI& hapi) {
	host_p = &hapi;
	return 0;
}


