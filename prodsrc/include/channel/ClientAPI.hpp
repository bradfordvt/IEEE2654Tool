/*
 *    ClientAPI.hpp
 *
 *    Class to implement the Client API interface element.
 *
 *    Class to implement the Client API interface element.
 *    The class implements the interface used between the Channel
 *    element and the Translator node.
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

#ifndef INCLUDE_CHANNEL_CLIENTAPI_HPP_
#define INCLUDE_CHANNEL_CLIENTAPI_HPP_

#include <stdint.h>
#include <stddef.h>
#include "channel/IEEE2654Channel.hpp"
#include "model/Translator.hpp"
#include "parser/ClientInterfaceRep.hpp"

class IEEE2654Channel;
class Translator;

class ClientAPI {
public:
	ClientAPI();
	ClientAPI(const ClientInterfaceRep& cr);
	~ClientAPI();

	friend bool operator==(const ClientAPI& lhs, const ClientAPI& rhs);

	int send_request(uint32_t uid, size_t len, uint8_t* message);
	int handle_response(uint32_t uid, size_t len, uint8_t* message);
	int handle_update_request(uint32_t uid, size_t len, uint8_t* message);
	int send_update_response(uint32_t uid, size_t len, uint8_t* message);

        // uint32_t uid;
	IEEE2654Channel* get_Channel();
	Translator* get_Translator();

	void dump(size_t indent);

private:
	ClientInterfaceRep crep;
};


#endif /* INCLUDE_CHANNEL_CLIENTAPI_HPP_ */
