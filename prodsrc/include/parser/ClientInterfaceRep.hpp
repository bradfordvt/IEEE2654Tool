/*
 *    ClientInterfaceRep.hpp
 *
 *    Class to implement the intermediate parser representation for the
 *    ClientInterface architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    ClientInterface architectural element.
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

#ifndef INCLUDE_PARSER_CLIENTINTERFACEREP_HPP_
#define INCLUDE_PARSER_CLIENTINTERFACEREP_HPP_

#include <string>

class ClientInterfaceRep {
#ifdef TEST
	friend class ClientInterfaceRep_TestCases;
#endif
public:
	ClientInterfaceRep();
	ClientInterfaceRep(const std::string& _name);
	ClientInterfaceRep(const ClientInterfaceRep& l);
	~ClientInterfaceRep();

	ClientInterfaceRep& operator=(const ClientInterfaceRep& l);
	friend bool operator==(const ClientInterfaceRep& lhs, const ClientInterfaceRep& rhs);

	bool set_name(const std::string& _name);
	const std::string& get_name();
	bool set_channel(int ch);
	int get_channel();
	bool set_translator(int t);
	int get_translator();
	bool set_protocol(const std::string& _protocol);
	const std::string& get_protocol();
	bool set_key(int k);
	int get_key();

private:
	std::string name; // Name of the channel
	std::string protocol; // The Google Protocol Description File defining
			      // messages used over the interface
	int key; // Index into table of ClientAPI instances in repository
	int channel; // Unique identifier index representing Channel object
		     // in the application's repository
	int translator; // Unique identifier index representing Translator
			// object in the application's repository
};

#endif /* INCLUDE_PARSER_CLIENTINTERFACEREP_HPP_ */
