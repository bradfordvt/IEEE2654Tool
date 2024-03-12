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

int ClientAPI::send_request(uint32_t uid, size_t len, uint8_t* message) {
	if(channel != NULL) {
		return channel->send_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int ClientAPI::handle_response(uint32_t uid, size_t len, uint8_t* message) {
	if(translator != NULL) {
		return translator->handle_response(uid, len, message);
	}
	else {
		return -1;
	}
}

int ClientAPI::handle_update_request(uint32_t uid, size_t len, uint8_t* message) {
	if(translator != NULL) {
		return translator->handle_update_request(uid, len, message);
	}
	else {
		return -1;
	}
}

int ClientAPI::send_update_response(uint32_t uid, size_t len, uint8_t* message) {
	if(channel != NULL) {
		return channel->send_update_response(uid, len, message);
	}
	else {
		return -1;
	}
}

int ClientAPI::set_channel(IEEE2654Channel& ch) {
	channel = &ch;
	return 0;
}

int ClientAPI::set_translator(Translator& t) {
	translator = &t;
	return 0;
}

