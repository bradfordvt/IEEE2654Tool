/*
 *    ChannelRep.hpp
 *
 *    Class to implement the intermediate parser representation for the
 *    Channel architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    Channel architectural element.
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

#ifndef INCLUDE_PARSER_CHANNELREP_HPP_
#define INCLUDE_PARSER_CHANNELREP_HPP_

#include <string>

class ChannelRep {
#ifdef TEST
	friend class ChannelRep_TestCases;
#endif
public:
	ChannelRep();
	ChannelRep(const std::string& _name);
	ChannelRep(const ChannelRep& l);
	~ChannelRep();

	ChannelRep& operator=(const ChannelRep& l);
	friend bool operator==(const ChannelRep& lhs, const ChannelRep& rhs);

	bool set_name(const std::string& _name);
	const std::string& get_name();
	bool set_key(int n);
	int get_key();
	bool set_protocol(const std::string& _protocol);
	const std::string& get_protocol();
	bool set_method(const std::string& _method);
	const std::string& get_method();
	bool set_client_interface(int n);
	int get_client_interface();
	bool set_host_interface(int n);
	int get_host_interface();

private:
	std::string name; // Name of the channel
	std::string protocol; // The Google Protocol Description File defining messages used over channel
	std::string method; // The method of transmission of message used
			    // reference: function call pass by reference
			    // gRPC: Google Remote Procedure Call
			    // socket: Posix sockets
			    // USB: Raw text commands over USB
			    // Telnet: Commands with handshake over Telnet port
			    // SSH: Commands with handshake over SSH port
			    // HTTP: API over HTTP port
	int key; // Unique identifier index representing Channel object
	int client_interface; // Unique identifier index representing
			      // ClientAPI object
	int host_interface; // Unique identifier index representing
			      // HostAPI object
};

#endif /* INCLUDE_PARSER_CHANNELREP_HPP_ */
