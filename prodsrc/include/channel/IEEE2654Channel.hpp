/*
 *    IEEE2654Channel.hpp
 *
 *    Class to implement the Channel architectural element.
 *
 *    Class to implement the Channel architectural element.
 *    The class implements the communications Channel of
 *    the message layer.  This is the mechanism that transports
 *    IEEE2654Message carrier wrapper messages from one Translator
 *    node to another.
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

#ifndef INCLUDE_CHANNEL_IEEE2654CHANNEL_HPP_
#define INCLUDE_CHANNEL_IEEE2654CHANNEL_HPP_

#include <stdint.h>
#include <stddef.h>
#include "channel/ClientAPI.hpp"
#include "channel/HostAPI.hpp"

class ClientAPI;
class HostAPI;

class IEEE2654Channel {
public:
	IEEE2654Channel();
	~IEEE2654Channel();

	int send_request(uint32_t uid, size_t len, uint8_t* message);
	int send_response(uint32_t uid, size_t len, uint8_t* message);
	int handle_request(uint32_t uid, size_t len, uint8_t* message);
	int handle_response(uint32_t uid, size_t len, uint8_t* message);
	int update_request(uint32_t uid, size_t len, uint8_t* message);
	int handle_update_request(uint32_t uid, size_t len, uint8_t* message);
	int send_update_response(uint32_t uid, size_t len, uint8_t* message);
	int handle_update_response(uint32_t uid, size_t len, uint8_t* message);

	int set_client(ClientAPI& capi);
	int set_host(HostAPI& hapi);

private:
	ClientAPI* client_p;
	HostAPI* host_p;
};


#endif /* INCLUDE_CHANNEL_IEEE2654CHANNEL_HPP_ */
