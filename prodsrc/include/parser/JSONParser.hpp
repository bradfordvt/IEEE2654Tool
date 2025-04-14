/*
 *    JSONParser.hpp
 *
 *    Class to implement the parser to read the persistent representation
 *    of the IEEE2654Tree Model.
 *
 *    Class to implement the parser to read the persistent representation
 *    of the IEEE2654Tree Model.
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

#ifndef INCLUDE_PARSER_JSONPARSER_HPP_
#define INCLUDE_PARSER_JSONPARSER_HPP_

#include <string>

#include "rapidjson/document.h"  // rapidjason's DOM-style API

#include "parser/TopModuleRep.hpp"
#include "parser/TranslatorRep.hpp"
#include "parser/ChannelRep.hpp"
#include "parser/HostInterfaceRep.hpp"
#include "parser/ClientInterfaceRep.hpp"
#include "parser/InjectInterfaceRep.hpp"
#include "parser/CommandInterfaceRep.hpp"
#include "parser/TransformLibraryRep.hpp"
#include "parser/DebugLibraryRep.hpp"
#include "parser/CommandLibraryRep.hpp"
#include "parser/InjectLibraryRep.hpp"

class JSONParser {
#ifdef TEST
	friend class JSONParser_TestCases;
#endif
public:
	JSONParser();
	JSONParser(const JSONParser& t);
	~JSONParser();

	JSONParser& operator=(const JSONParser& t);

	bool parse(const std::string& model_name);

private:
	bool __parseTopModule();
	bool __add_TopModule(TopModuleRep& tmr);
	bool __parseTranslators(const rapidjson::Value& v);
	bool __parseTranslator(const rapidjson::Value& v);
	bool __add_translator(TranslatorRep& tr);
	bool __parseChannels(const rapidjson::Value& v);
	bool __parseChannel(const rapidjson::Value& v);
	bool __add_channel(ChannelRep& cr);
	bool __parseHostInterfaces(const rapidjson::Value& v);
	bool __parseHostInterface(const rapidjson::Value& v);
	bool __add_host_interface(HostInterfaceRep& hir);
	bool __parseClientInterfaces(const rapidjson::Value& v);
	bool __parseClientInterface(const rapidjson::Value& v);
	bool __add_client_interface(ClientInterfaceRep& cir);
	bool __parseInjectInterfaces(const rapidjson::Value& v);
	bool __parseInjectInterface(const rapidjson::Value& v);
	bool __add_inject_interface(InjectInterfaceRep& iir);
	bool __parseCommandInterfaces(const rapidjson::Value& v);
	bool __parseCommandInterface(const rapidjson::Value& v);
	bool __add_command_interface(CommandInterfaceRep& cir);
	TransformLibraryRep& __parseTransformLibrary(const rapidjson::Value::ConstMemberIterator& itr);
	DebugLibraryRep& __parseDebugLibrary(const rapidjson::Value::ConstMemberIterator& itr);
	CommandLibraryRep& __parseCommandLibrary(const rapidjson::Value::ConstMemberIterator& itr);
	InjectLibraryRep& __parseInjectLibrary(const rapidjson::Value::ConstMemberIterator& itr);

	std::string filename;
	rapidjson::Document document;  // Default template parameter uses UTF8
				       // and MemoryPoolAllocator.
	TopModuleRep top_module_rep;

	// Temporary storage objects
	TopModuleRep tmptmr;
	TranslatorRep tmptr;
	ChannelRep tmpchr;
	HostInterfaceRep tmphir;
	ClientInterfaceRep tmpcir;
	CommandInterfaceRep tmpcoir;
	InjectInterfaceRep tmpiir;
	CommandLibraryRep tmpclr;
	InjectLibraryRep tmpilr;
	DebugLibraryRep tmpdlr;
	TransformLibraryRep tmptlr;
};

#endif /* INCLUDE_PARSER_JSONPARSER_HPP_ */
