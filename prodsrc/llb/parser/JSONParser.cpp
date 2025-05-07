/*
 *    JSONParser.cpp
 *
 *    Class to implement the intermediate parser representation for the
 *    Translator architectural element.
 *
 *    Class to implement the intermediate parser representation for the
 *    Translator architectural element.
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
static const char __date__[] = "2024/06/13";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include "rapidjson/filereadstream.h"
#include "rapidjson/error/en.h"
#include <cstdio>
#include "parser/JSONParser.hpp"
#include <cassert>
#include "repository/Repository.hpp"
#include "log/Logger.hpp"
#include "debug/Verify.hpp"
// for cwd
#include <filesystem>

JSONParser::JSONParser() : filename() {
	SWDEBUGP1( 5, Verify::PARSER, "JSONParser::JSONParser");
	SWDEBUG1( 5, Verify::TRACE, "JSONParser::JSONParser");
}

JSONParser::JSONParser(const JSONParser& t) : filename(t.filename) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::JSONParser",
                        " const JSONParser& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::JSONParser",
                        " const JSONParser& " );
	// document = t.document;
	top_module_rep = t.top_module_rep;
}

JSONParser::~JSONParser() {
	SWDEBUGP1( 5, Verify::PARSER, "JSONParser::~JSONParser");
	SWDEBUG1( 5, Verify::TRACE, "JSONParser::~JSONParser");
}

JSONParser& JSONParser::operator=(const JSONParser& t) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::operator=",
                        " const JSONParser& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::operator=",
                        " const JSONParser& " );
	filename = t.filename;
	// document = t.document;
	top_module_rep = t.top_module_rep;
	return *this;
}

bool JSONParser::parse(const std::string& model_name) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::parse",
                        " const std::string& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::parse",
                        " const std::string& " );
	filename = model_name;
	FILE* fp = fopen(filename.c_str(), "rb");
	if(fp == NULL)
	{
		// TODO - log error
		std::string msg("JSONParser::parse(): filename(");
                msg += filename;
                msg += ") is not able to be opened!";
		// find the current path
		std::filesystem::path cwd = std::filesystem::current_path();
		msg += "\nCurrent working directory is: ";
		msg += cwd.string();
                Logger* logger = Logger::get_logger();
                logger->log(ERROR, msg.c_str());
		return false;
	}
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	
        // In-situ parsing, decode strings directly in the source string.
        // Source must be string.
	std::string buffer(readBuffer);
        char *writable = new char[buffer.size() + 1];
        std::copy(buffer.begin(), buffer.end(), writable);
        writable[buffer.size()] = '\0';
        // char buffer[strlen(json_message)];
        // memcpy(buffer, json_message, sizeof(json_message));
        // buffer[sizeof(json_message)] = '\0';
        // if(document.ParseStream(is).HasParseError())
        if(document.Parse<0>(writable).HasParseError())

        {
		// TODO - log error
		size_t offset = document.GetErrorOffset();
		// rapidjson::ParseErrorCode pecode = document.GetParseError();
		std::string msg("JSONParser::parse():\n");
		size_t i;
		for(i = 0; i < offset; i++) {
			msg += writable[i];
		}
		msg += "\n***********************************\n";
		msg += GetParseError_En(document.Parse<0>(writable).GetParseError());
		msg += "\n***********************************\n";
		for(; i < buffer.size(); i++) {
			msg += writable[i];
		}
		msg += "\n";
                Logger* logger = Logger::get_logger();
                logger->log(ERROR, msg.c_str());
		fclose(fp);
                return false;
        }
        // Parsing to document succeeded

        // 2. Access values in document.
        if(!document.IsObject())
	{

		// TODO - log error
		std::string msg("JSONParser::parse(): filename(");
                msg += filename;
                msg += ") document is not an object!";
                Logger* logger = Logger::get_logger();
                logger->log(ERROR, msg.c_str());
		fclose(fp);
                return false;
        }
	bool b = __parseTopModule();
	if(b)
	{
		fclose(fp);
		return true;
	}
	fclose(fp);
	return false;
}

bool JSONParser::__parseTopModule() {
	SWDEBUGP1( 5, Verify::PARSER, "JSONParser::__parseTopModule");
	SWDEBUG1( 5, Verify::TRACE, "JSONParser::__parseTopModule");
	Repository* rep = Repository::get_repository();
	int required = 0;
        // const rapidjson::Value& nt = document["num_translators"]; // Using a reference for consecutive access is handy and faster.
        if(document.HasMember("num_translators"))
        {
		rep->set_num_translators(document["num_translators"].GetInt());
		top_module_rep.set_num_translators(document["num_translators"].GetInt());
		required++;
        }
        if(document.HasMember("num_channels"))
        {
		rep->set_num_channels(document["num_channels"].GetInt());
		top_module_rep.set_num_channels(document["num_channels"].GetInt());
		required++;
        }
        if(document.HasMember("num_host_interfaces"))
        {
		rep->set_num_host_interfaces(document["num_host_interfaces"].GetInt());
		top_module_rep.set_num_host_interfaces(document["num_host_interfaces"].GetInt());
		required++;
        }
        if(document.HasMember("num_client_interfaces"))
        {
		rep->set_num_client_interfaces(document["num_client_interfaces"].GetInt());
		top_module_rep.set_num_client_interfaces(document["num_client_interfaces"].GetInt());
		required++;
        }
        if(document.HasMember("num_command_interfaces"))
        {
		rep->set_num_command_interfaces(document["num_command_interfaces"].GetInt());
		top_module_rep.set_num_command_interfaces(document["num_command_interfaces"].GetInt());
		required++;
        }
        if(document.HasMember("num_inject_interfaces"))
        {
		rep->set_num_inject_interfaces(document["num_inject_interfaces"].GetInt());
		top_module_rep.set_num_inject_interfaces(document["num_inject_interfaces"].GetInt());
		required++;
        }
        if(document.HasMember("translator"))
        {
		top_module_rep.set_translator(document["translator"].GetInt());
		required++;
        }
	if(required == 7)
	{
		// Using a reference for consecutive access is handy and faster.
	        const rapidjson::Value& translators = document["translators"];

		if(!translators.IsArray())
		{
			// TODO - log error
			std::string msg("JSONParser::parse(): translators key is not an array!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
#if 0
		// for(rapidjson::Value::ConstMemberIterator itr = translators.MemberBegin(); itr != translators.MemberEnd(); ++itr)
		for(rapidjson::Value::ConstValueIterator itr = translators.Begin(); itr != translators.End(); ++itr)
		{
			if(itr->GetType() != 3)
			{
				// TODO - log error
				std::string msg("JSONParser::parse(): translators value is not an object!");
				Logger* logger = Logger::get_logger();
				logger->log(ERROR, msg.c_str());
				return false;
			}
			else
			{
				if(itr->MemberBegin()->name.GetString() != "Translator")
				{
					// TODO - log error
					std::string msg("JSONParser::parse(): translators object is not a a Translator!");
					Logger* logger = Logger::get_logger();
					logger->log(ERROR, msg.c_str());
					return false;
				}
				rapidjson::Value::ConstMemberIterator it = itr->MemberBegin();
				TranslatorRep& tr = __parseTranslator(it);
		}
#endif
		bool tretval = __parseTranslators(translators);
		if(tretval == false) return false;
		// Using a reference for consecutive access is handy and faster.
	        const rapidjson::Value& channels = document["channels"];

		if(!channels.IsArray())
		{
			// TODO - log error
			std::string msg("JSONParser::parse(): channels key is not an object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
#if 0
		for(rapidjson::Value::ConstMemberIterator itr = channels.MemberBegin(); itr != channels.MemberEnd(); ++itr)
		{
			ChannelRep& cr = __parseChannel(itr);
			Repository* rep = Repository::get_repository();
			// Add channel to repository
			rep->insert_Channel(cr);
		}
#endif
		bool chretval = __parseChannels(channels);
		if(chretval == false) return false;
		// Using a reference for consecutive access is handy and faster.
	        const rapidjson::Value& host_interfaces = document["host_interfaces"];

		if(!host_interfaces.IsArray())
		{
			// TODO - log error
			std::string msg("JSONParser::parse(): host_interfaces key is not an object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
#if 0
		for(rapidjson::Value::ConstMemberIterator itr = host_interfaces.MemberBegin(); itr != host_interfaces.MemberEnd(); ++itr)
		{
			HostInterfaceRep& hir = __parseHostInterface(itr);
			Repository* rep = Repository::get_repository();
			// Add host_interface to repository
			rep->insert_HostAPI(hir);
		}
#endif
		bool hiretval = __parseHostInterfaces(host_interfaces);
		if(hiretval == false) return false;
		// Using a reference for consecutive access is handy and faster.
	        const rapidjson::Value& client_interfaces = document["client_interfaces"];

		if(!client_interfaces.IsArray())
		{
			// TODO - log error
			std::string msg("JSONParser::parse(): client_interfaces key is not an object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
#if 0
		for(rapidjson::Value::ConstMemberIterator itr = client_interfaces.MemberBegin(); itr != client_interfaces.MemberEnd(); ++itr)
		{
			ClientInterfaceRep& cir = __parseClientInterface(itr);
			Repository* rep = Repository::get_repository();
			// Add client_interface to repository
			rep->insert_ClientAPI(cir);
		}
#endif
		bool ciretval = __parseClientInterfaces(client_interfaces);
		if(ciretval == false) return false;
		// Using a reference for consecutive access is handy and faster.
	        const rapidjson::Value& command_interfaces = document["command_interfaces"];

		if(!command_interfaces.IsArray())
		{
			// TODO - log error
			std::string msg("JSONParser::parse(): command_interfaces key is not an object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
#if 0
		for(rapidjson::Value::ConstMemberIterator itr = command_interfaces.MemberBegin(); itr != command_interfaces.MemberEnd(); ++itr)
		{
			CommandInterfaceRep& cir = __parseCommandInterface(itr);
			Repository* rep = Repository::get_repository();
			// Add command_interface to repository
			rep->insert_CommandInterface(cir);
		}
#endif
		bool coiretval = __parseCommandInterfaces(command_interfaces);
		if(coiretval == false) return false;
		// Using a reference for consecutive access is handy and faster.
	        const rapidjson::Value& inject_interfaces = document["inject_interfaces"];

		if(!inject_interfaces.IsArray())
		{
			// TODO - log error
			std::string msg("JSONParser::parse(): inject_interfaces key is not an object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
#if 0
		for(rapidjson::Value::ConstMemberIterator itr = inject_interfaces.MemberBegin(); itr != inject_interfaces.MemberEnd(); ++itr)
		{
			InjectInterfaceRep& iir = __parseInjectInterface(itr);
			Repository* rep = Repository::get_repository();
			// Add inject_interface to repository
			rep->insert_InjectInterface(iir);
		}
#endif
		bool iiretval = __parseInjectInterfaces(inject_interfaces);
		if(iiretval == false) return false;
		return __add_TopModule(top_module_rep);
	}
	else
	{
		return false;
	}
}

bool JSONParser::__add_TopModule(TopModuleRep& tmr) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__add_TopModule",
                        " TopModuleRep& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__add_TopModule",
                        " TopModuleRep& " );
	Repository* rep = Repository::get_repository();
	int translator = tmr.get_translator();
	Translator* tp = rep->find_translator_by_uid(translator);
	tmr.set_module_name(tp->get_module_name());
	rep->dump(0);
	tmr.dump(0);
	// Add Top Module to repository
	Translator* t_p = rep->set_TopModule(tmr);
	if(t_p == NULL) return false;
	else return true;
}

bool JSONParser::__parseTranslators(const rapidjson::Value& v) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseTranslators",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseTranslators",
                        " const rapidjson::Value& " );
	for(rapidjson::Value::ConstValueIterator itr = v.Begin(); itr != v.End(); ++itr)
	{
		if(itr->GetType() != 3) // Not a {} object
		{
			// TODO - log error
			std::string msg("JSONParser::__parseTranslators(): \"v\" is not an object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
		// itr is a pointer to an object
		// Now verify it is a translator object
		std::string name(itr->MemberBegin()->name.GetString());
		int nlen = name.length();
		if(name.compare(0, nlen, "Translator")) // Not a Translator
		{
			// TODO - log error
			std::string msg("JSONParser::__parseTranslators(): \"itr\" is not a pointer to a translator object!");
			msg += "\nname = ";
			msg += name;
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
		// itr is a translator object
		// Now process the translator
		bool retval = __parseTranslator(itr->MemberBegin()->value);
		if(retval == false)
		{
			return false;
		}
	}
	return true;
}

bool JSONParser::__parseTranslator(const rapidjson::Value& v) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseTranslator",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseTranslator",
                        " const rapidjson::Value& " );
// TranslatorRep& JSONParser::__parseTranslator(rapidjson::Value::ConstMemberIterator& itr) {
// TranslatorRep& JSONParser::__parseTranslator(rapidjson::Value::ConstValueIterator& itr) {
	// const char* gptypes[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
	// std::cerr << "Translator name: " << itr->name.GetString() << std::endl;
	// std::cerr << "Translator type: " << gptypes[v.GetType()] << std::endl;
	// TranslatorRep tr;
	tmptr = TranslatorRep();
	// for(rapidjson::Value::ConstMemberIterator it = itr->MemberBegin(); it != itr->MemberEnd(); ++it)
	for(rapidjson::Value::ConstMemberIterator it = v.MemberBegin(); it != v.MemberEnd(); ++it)
	{
		// std::cerr << "Translator lhs name: " << it->name.GetString() << std::endl;
		// std::cerr << "Translator rhs type: " << gptypes[it->value.GetType()] << std::endl;
		std::string name = it->name.GetString();
		int nl = name.length();
		if(name.compare(0, nl, "module") == 0)
		{
			tmptr.set_module_name(it->value.GetString());
		}
		if(name.compare(0, nl, "key") == 0)
		{
			tmptr.set_key(it->value.GetInt());
		}
		if(name.compare(0, nl, "instance_name") == 0)
		{
			tmptr.set_instance_name(it->value.GetString());
		}
		if(name.compare(0, nl, "path") == 0)
		{
			tmptr.set_path(it->value.GetString());
		}
		if(name.compare(0, nl, "client") == 0)
		{
			tmptr.set_client(it->value.GetInt());
		}
		if(name.compare(0, nl, "hosts") == 0)
		{
			assert(it->value.IsArray());
			for (rapidjson::SizeType i = 0; i < it->value.Size(); i++)
			{
				tmptr.add_host(it->value[i].GetInt());
			}
		}
		if(name.compare(0, nl, "command_interface") == 0)
		{
			tmptr.set_command_interface(it->value.GetInt());
		}
		if(name.compare(0, nl, "inject_interface") == 0)
		{
			tmptr.set_inject_interface(it->value.GetInt());
		}
		if(name.compare(0, nl, "num_children") == 0)
		{
			tmptr.set_num_children(it->value.GetInt());
		}
		if(name.compare(0, nl, "translator_uid") == 0)
		{
			tmptr.set_translator_uid(it->value.GetInt());
		}
		if(name.compare(0, nl, "CommandLibrary") == 0)
		{
			CommandLibraryRep& clr = __parseCommandLibrary(it);
			tmptr.set_CommandLibraryRep(clr);
		}
		if(name.compare(0, nl, "InjectLibrary") == 0)
		{
			InjectLibraryRep& ilr = __parseInjectLibrary(it);
			tmptr.set_InjectLibraryRep(ilr);
		}
		if(name.compare(0, nl, "TransformLibrary") == 0)
		{
			TransformLibraryRep& tlr = __parseTransformLibrary(it);
			tmptr.set_TransformLibraryRep(tlr);
		}
		if(name.compare(0, nl, "DebugLibrary") == 0)
		{
			DebugLibraryRep& dlr = __parseDebugLibrary(it);
			tmptr.set_DebugLibraryRep(dlr);
		}
		if(name.compare(0, nl, "properties") == 0)
		{
			if(!(it->value.IsObject()))
			{

				// TODO - log error
				std::string msg("JSONParser::parse(): properties is not an object!");
				Logger* logger = Logger::get_logger();
				logger->log(ERROR, msg.c_str());
				assert(false);
			}
			for(rapidjson::Value::ConstMemberIterator pit = it->value.MemberBegin(); pit != it->value.MemberEnd(); ++pit)
			{
				const char* ptypes[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
				if(pit->value.GetType() == 5)
				{
					tmptr.add_property(pit->name.GetString(), pit->value.GetString(), std::string("string"));
				}
				else if(pit->value.GetType() == 6)
				{
					tmptr.add_property(pit->name.GetString(), std::to_string(pit->value.GetInt()), std::string("number"));
				}
				else if(pit->value.GetType() == 2)
				{
					tmptr.add_property(pit->name.GetString(), std::string("true"), std::string("bool"));
				}
				else if(pit->value.GetType() == 1)
				{
					tmptr.add_property(pit->name.GetString(), std::string("false"), std::string("bool"));
				}
				else
				{
					// TODO - report incorrect property type
					std::string msg("JSONParser::__parseTranslator(): incorrect property type for key <");
					msg += pit->name.GetString();
					msg += "> value of type [";
					msg += ptypes[pit->value.GetType()];
					msg += "]!";
					Logger* logger = Logger::get_logger();
					logger->log(ERROR, msg.c_str());
					assert(false);
				}
			}
		}
		if(name.compare(0, nl, "children") == 0)
		{
			assert(it->value.IsArray());
			for (rapidjson::SizeType i = 0; i < it->value.Size(); i++)
			{
				tmptr.add_child(it->value[i].GetInt());
			}
		}
	}
	return __add_translator(tmptr); 
}

bool JSONParser::__add_translator(TranslatorRep& tr) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__add_TopModule",
                        " TopModuleRep& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__add_TopModule",
                        " TopModuleRep& " );
	Repository* rep = Repository::get_repository();
	// Add translator to repository
	Translator* t_p = rep->insert_Translator(tr);
	if(t_p == NULL) return false;
	else return true;
}

bool JSONParser::__parseChannels(const rapidjson::Value& v) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseChannels",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseChannels",
                        " const rapidjson::Value& " );
	for(rapidjson::Value::ConstValueIterator itr = v.Begin(); itr != v.End(); ++itr)
	{
		if(itr->GetType() != 3) // Not a {} object
		{
			// TODO - log error
			std::string msg("JSONParser::__parseChannels(): \"a\" is not an object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
		// itr is a pointer to an object
		// Now verify it is a channel object
		std::string name(itr->MemberBegin()->name.GetString());
		int nlen = name.length();
		if(name.compare(0, nlen, "Channel")) // Not a channel
		{
			// TODO - log error
			std::string msg("JSONParser::__parseChannels(): \"itr\" is not a pointer to a channel object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
		// itr is a channel object
		// Now process the channel
		bool retval = __parseChannel(itr->MemberBegin()->value);
		if(retval == false)
		{
			return false;
		}
	}
	return true;
}

bool JSONParser::__parseChannel(const rapidjson::Value& v) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseChannel",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseChannel",
                        " const rapidjson::Value& " );
	// const char* gptypes[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
	// std::cerr << "Channel type: " << gptypes[v.GetType()] << std::endl;
	// ChannelRep cr;
	tmpchr = ChannelRep();
	int required = 0;
	// for(rapidjson::Value::ConstValueIterator it = v.Begin(); it != v.End(); ++it)
	for(rapidjson::Value::ConstMemberIterator it = v.MemberBegin(); it != v.MemberEnd(); ++it)
	{
		// std::cerr << "Channel lhs name: " << it->name.GetString() << std::endl;
		// std::cerr << "Channel rhs type: " << gptypes[it->value.GetType()] << std::endl;
		// std::string name = it->MemberBegin()->name.GetString();
		// int nl = name.length();
		std::string name = it->name.GetString();
		int nl = name.length();
#if 0
	if(!(itr->value.IsObject()))
	{

		// TODO - log error
		std::string msg("JSONParser::parse(): channel is not an object!");
		Logger* logger = Logger::get_logger();
		logger->log(ERROR, msg.c_str());
		assert(false);
	}
	for(rapidjson::Value::ConstMemberIterator it = itr->value.MemberBegin(); it != itr->value.MemberEnd(); ++it)
	{
		std::string name = it->name.GetString();
		int nl = name.length();
#endif
		if(name.compare(0, nl, "name") == 0)
		{
			tmpchr.set_name(it->value.GetString());
			required++;
		}
		if(name.compare(0, nl, "protocol") == 0)
		{
			tmpchr.set_protocol(it->value.GetString());
			required++;
		}
		if(name.compare(0, nl, "method") == 0)
		{
			tmpchr.set_method(it->value.GetString());
			required++;
		}
		if(name.compare(0, nl, "key") == 0)
		{
			tmpchr.set_key(it->value.GetInt());
			required++;
		}
		if(name.compare(0, nl, "host_interface") == 0)
		{
			tmpchr.set_host_interface(it->value.GetInt());
			required++;
		}
		if(name.compare(0, nl, "client_interface") == 0)
		{
			tmpchr.set_client_interface(it->value.GetInt());
			required++;
		}
	}
	return __add_channel(tmpchr); 
}

bool JSONParser::__add_channel(ChannelRep& cr) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__add_channel",
                        " TopModuleRep& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__add_channel",
                        " TopModuleRep& " );
	Repository* rep = Repository::get_repository();
	// Add channel to repository
	IEEE2654Channel* ch_p = rep->insert_Channel(cr);
	if(ch_p == NULL) return false;
	else return true;
}

bool JSONParser::__parseHostInterfaces(const rapidjson::Value& a) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseHostInterfaces",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseHostInterfaces",
                        " const rapidjson::Value& " );
	for(rapidjson::Value::ConstValueIterator itr = a.Begin(); itr != a.End(); ++itr)
	{
		if(itr->GetType() != 3) // Not a {} object
		{
			// TODO - log error
			std::string msg("JSONParser::__parseHostInterfaces(): \"a\" is not an object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
		// itr is a pointer to an object
		// Now verify it is a host_interface object
		std::string name(itr->MemberBegin()->name.GetString());
		int nlen = name.length();
		if(name.compare(0, nlen, "host_interface")) // Not a host_interface
		{
			// TODO - log error
			std::string msg("JSONParser::__parseHostInterfaces(): \"itr\" is not a pointer to a host_interface object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
		// itr is a host_interface object
		// Now process the host_interface
		bool retval = __parseHostInterface(itr->MemberBegin()->value);
		if(retval == false)
		{
			return false;
		}
	}
	return true;
}

bool JSONParser::__parseHostInterface(const rapidjson::Value& v) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseHostInterface",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseHostInterface",
                        " const rapidjson::Value& " );
	// HostInterfaceRep hir;
	tmphir = HostInterfaceRep();
	int required = 0;
	// for(rapidjson::Value::ConstValueIterator it = v.Begin(); it != v.End(); ++it)
	for(rapidjson::Value::ConstMemberIterator it = v.MemberBegin(); it != v.MemberEnd(); ++it)
	{
		// const char* gptypes[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
		// std::cerr << "HostInterface lhs name: " << it->name.GetString() << std::endl;
		// std::cerr << "HostInterface rhs type: " << gptypes[it->value.GetType()] << std::endl;
		// std::string name = it->MemberBegin()->name.GetString();
		// int nl = name.length();
		std::string name = it->name.GetString();
		int nl = name.length();
#if 0
	if(!(itr->value.IsObject()))
	{

		// TODO - log error
		std::string msg("JSONParser::parse(): host_interface is not an object!");
		Logger* logger = Logger::get_logger();
		logger->log(ERROR, msg.c_str());
		assert(false);
	}
	for(rapidjson::Value::ConstMemberIterator it = itr->value.MemberBegin(); it != itr->value.MemberEnd(); ++it)
	{
		std::string name = it->name.GetString();
		int nl = name.length();
#endif
		if(name.compare(0, nl, "name") == 0)
		{
			tmphir.set_name(it->value.GetString());
			required++;
		}
		if(name.compare(0, nl, "key") == 0)
		{
			tmphir.set_key(it->value.GetInt());
			required++;
		}
		if(name.compare(0, nl, "protocol") == 0)
		{
			tmphir.set_protocol(it->value.GetString());
			required++;
		}
		if(name.compare(0, nl, "channel") == 0)
		{
			tmphir.set_channel(it->value.GetInt());
			required++;
		}
		if(name.compare(0, nl, "translator") == 0)
		{
			tmphir.set_translator(it->value.GetInt());
			required++;
		}
	}
	return __add_host_interface(tmphir);
}

bool JSONParser::__add_host_interface(HostInterfaceRep& hir) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__add_host_interface",
                        " TopModuleRep& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__add_host_interface",
                        " TopModuleRep& " );
	Repository* rep = Repository::get_repository();
	// Add host_interface to repository
	HostAPI* hapi_p = rep->insert_HostAPI(hir);
	if(hapi_p == NULL) return false;
	else return true;
}

bool JSONParser::__parseClientInterfaces(const rapidjson::Value& v) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseClientInterfaces",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseClientInterfaces",
                        " const rapidjson::Value& " );
	for(rapidjson::Value::ConstValueIterator itr = v.Begin(); itr != v.End(); ++itr)
	{
		if(itr->GetType() != 3) // Not a {} object
		{
			// TODO - log error
			std::string msg("JSONParser::__parseClientInterface(): \"a\" is not an object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
		// itr is a pointer to an object
		// Now verify it is a client_interface object
		std::string name(itr->MemberBegin()->name.GetString());
		int nlen = name.length();
		if(name.compare(0, nlen, "client_interface")) // Not a client_interface
		{
			// TODO - log error
			std::string msg("JSONParser::__parseClientInterface(): \"itr\" is not a pointer to a client_interface object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
		// itr is a client_interface object
		// Now process the client_interface
		bool retval = __parseClientInterface(itr->MemberBegin()->value);
		if(retval == false)
		{
			return false;
		}
	}
	return true;
}

bool JSONParser::__parseClientInterface(const rapidjson::Value& v) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseClientInterface",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseClientInterface",
                        " const rapidjson::Value& " );
	// ClientInterfaceRep cir;
	tmpcir = ClientInterfaceRep();
	int required = 0;
	// for(rapidjson::Value::ConstValueIterator it = v.Begin(); it != v.End(); ++it)
	for(rapidjson::Value::ConstMemberIterator it = v.MemberBegin(); it != v.MemberEnd(); ++it)
	{
		// const char* gptypes[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
		// std::cerr << "client_interface lhs name: " << it->name.GetString() << std::endl;
		// std::cerr << "client_interface rhs type: " << gptypes[it->value.GetType()] << std::endl;
		// std::string name = it->MemberBegin()->name.GetString();
		// int nl = name.length();
		std::string name = it->name.GetString();
		int nl = name.length();
#if 0
	if(!(itr->value.IsObject()))
	{

		// TODO - log error
		std::string msg("JSONParser::parse(): client_interface is not an object!");
		Logger* logger = Logger::get_logger();
		logger->log(ERROR, msg.c_str());
		assert(false);
	}
	for(rapidjson::Value::ConstMemberIterator it = itr->value.MemberBegin(); it != itr->value.MemberEnd(); ++it)
	{
		std::string name = it->name.GetString();
		int nl = name.length();
#endif
		if(name.compare(0, nl, "name") == 0)
		{
			tmpcir.set_name(it->value.GetString());
			required++;
		}
		if(name.compare(0, nl, "key") == 0)
		{
			tmpcir.set_key(it->value.GetInt());
			required++;
		}
		if(name.compare(0, nl, "protocol") == 0)
		{
			tmpcir.set_protocol(it->value.GetString());
			required++;
		}
		if(name.compare(0, nl, "channel") == 0)
		{
			tmpcir.set_channel(it->value.GetInt());
			required++;
		}
		if(name.compare(0, nl, "translator") == 0)
		{
			tmpcir.set_translator(it->value.GetInt());
			required++;
		}
	}
	return __add_client_interface(tmpcir);
}

bool JSONParser::__add_client_interface(ClientInterfaceRep& cir) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__add_client_interface",
                        " TopModuleRep& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__add_client_interface",
                        " TopModuleRep& " );
	Repository* rep = Repository::get_repository();
	// Add client_interface to repository
	ClientAPI* ci_p = rep->insert_ClientAPI(cir);
	if(ci_p == NULL) return false;
	else return true;
}

bool JSONParser::__parseInjectInterfaces(const rapidjson::Value& v) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseInjectInterfaces",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseInjectInterfaces",
                        " const rapidjson::Value& " );
	for(rapidjson::Value::ConstValueIterator itr = v.Begin(); itr != v.End(); ++itr)
	{
		if(itr->GetType() != 3) // Not a {} object
		{
			// TODO - log error
			std::string msg("JSONParser::__parseInjectInterfaces(): \"a\" is not an object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
		// itr is a pointer to an object
		// Now verify it is a inject_interface object
		std::string name(itr->MemberBegin()->name.GetString());
		int nlen = name.length();
		if(name.compare(0, nlen, "inject_interface")) // Not a inject_interface
		{
			// TODO - log error
			std::string msg("JSONParser::__parseInjectInterfaces(): \"itr\" is not a pointer to a inject_interface object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
		// itr is a inject_interface object
		// Now process the inject_interface
		bool retval = __parseInjectInterface(itr->MemberBegin()->value);
		if(retval == false)
		{
			return false;
		}
	}
	return true;
}

bool JSONParser::__parseInjectInterface(const rapidjson::Value& v) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseInjectInterface",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseInjectInterface",
                        " const rapidjson::Value& " );
	// InjectInterfaceRep iir;
	tmpiir = InjectInterfaceRep();
	int required = 0;
	// for(rapidjson::Value::ConstValueIterator it = v.Begin(); it != v.End(); ++it)
	for(rapidjson::Value::ConstMemberIterator it = v.MemberBegin(); it != v.MemberEnd(); ++it)
	{
		// const char* gptypes[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
		// std::cerr << "inject_interface lhs name: " << it->name.GetString() << std::endl;
		// std::cerr << "inject_interface rhs type: " << gptypes[it->value.GetType()] << std::endl;
		// std::string name = it->MemberBegin()->name.GetString();
		// int nl = name.length();
		std::string name = it->name.GetString();
		int nl = name.length();
#if 0
	if(!(itr->value.IsObject()))
	{

		// TODO - log error
		std::string msg("JSONParser::parse(): inject_interface is not an object!");
		Logger* logger = Logger::get_logger();
		logger->log(ERROR, msg.c_str());
		assert(false);
	}
	for(rapidjson::Value::ConstMemberIterator it = itr->value.MemberBegin(); it != itr->value.MemberEnd(); ++it)
	{
		std::string name = it->name.GetString();
		int nl = name.length();
#endif
		if(name.compare(0, nl, "name") == 0)
		{
			tmpiir.set_name(it->value.GetString());
			required++;
		}
		if(name.compare(0, nl, "protocol") == 0)
		{
			tmpiir.set_protocol(it->value.GetString());
			required++;
		}
		if(name.compare(0, nl, "translator") == 0)
		{
			tmpiir.set_translator(it->value.GetInt());
			required++;
		}
		if(name.compare(0, nl, "key") == 0)
		{
			tmpiir.set_key(it->value.GetInt());
			required++;
		}
	}
	return __add_inject_interface(tmpiir);
}

bool JSONParser::__add_inject_interface(InjectInterfaceRep& iir) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__add_inject_interface",
                        " TopModuleRep& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__add_inject_interface",
                        " TopModuleRep& " );
	Repository* rep = Repository::get_repository();
	// Add inject_interface to repository
	InjectInterface* ii_p = rep->insert_InjectInterface(iir);
	if(ii_p == NULL) return false;
	else return true;
}

bool JSONParser::__parseCommandInterfaces(const rapidjson::Value& v) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseCommandInterfaces",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseCommandInterfaces",
                        " const rapidjson::Value& " );
	for(rapidjson::Value::ConstValueIterator itr = v.Begin(); itr != v.End(); ++itr)
	{
		if(itr->GetType() != 3) // Not a {} object
		{
			// TODO - log error
			std::string msg("JSONParser::__parseCommandInterfaces(): \"a\" is not an object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
		// itr is a pointer to an object
		// Now verify it is a command_interface object
		std::string name(itr->MemberBegin()->name.GetString());
		int nlen = name.length();
		if(name.compare(0, nlen, "command_interface")) // Not a command_interface
		{
			// TODO - log error
			std::string msg("JSONParser::__parseCommandInterfaces(): \"itr\" is not a pointer to a command_interface object!");
			Logger* logger = Logger::get_logger();
			logger->log(ERROR, msg.c_str());
			return false;
		}
		// itr is a command_interface object
		// Now process the command_interface
		bool retval = __parseCommandInterface(itr->MemberBegin()->value);
		if(retval == false)
		{
			return false;
		}
	}
	return true;
}

bool JSONParser::__parseCommandInterface(const rapidjson::Value& v) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseCommandInterface",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseCommandInterface",
                        " const rapidjson::Value& " );
	// CommandInterfaceRep cir;
	tmpcoir = CommandInterfaceRep();
	int required = 0;
	// for(rapidjson::Value::ConstValueIterator it = v.Begin(); it != v.End(); ++it)
	for(rapidjson::Value::ConstMemberIterator it = v.MemberBegin(); it != v.MemberEnd(); ++it)
	{
		// const char* gptypes[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
		// std::cerr << "command_interface lhs name: " << it->name.GetString() << std::endl;
		// std::cerr << "command_interface rhs type: " << gptypes[it->value.GetType()] << std::endl;
		// std::string name = it->MemberBegin()->name.GetString();
		// int nl = name.length();
		std::string name = it->name.GetString();
		int nl = name.length();
#if 0
	if(!(itr->value.IsObject()))
	{

		// TODO - log error
		std::string msg("JSONParser::parse(): command_interface is not an object!");
		Logger* logger = Logger::get_logger();
		logger->log(ERROR, msg.c_str());
		assert(false);
	}
	for(rapidjson::Value::ConstMemberIterator it = itr->value.MemberBegin(); it != itr->value.MemberEnd(); ++it)
	{
		std::string name = it->name.GetString();
		int nl = name.length();
#endif
		if(name.compare(0, nl, "name") == 0)
		{
			tmpcoir.set_name(it->value.GetString());
			required++;
		}
		if(name.compare(0, nl, "protocol") == 0)
		{
			tmpcoir.set_protocol(it->value.GetString());
			required++;
		}
		if(name.compare(0, nl, "key") == 0)
		{
			tmpcoir.set_key(it->value.GetInt());
			required++;
		}
		if(name.compare(0, nl, "translator") == 0)
		{
			tmpcoir.set_translator(it->value.GetInt());
			required++;
		}
		if(name.compare(0, nl, "uid") == 0)
		{
			tmpcoir.set_uid(it->value.GetInt());
			required++;
		}
	}
	return __add_command_interface(tmpcoir);
}

bool JSONParser::__add_command_interface(CommandInterfaceRep& cir) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__add_command_interface",
                        " TopModuleRep& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__add_command_interface",
                        " TopModuleRep& " );
	Repository* rep = Repository::get_repository();
	// Add command_interface to repository
	CommandInterface* ci_p = rep->insert_CommandInterface(cir);
	if(ci_p == NULL) return false;
	else return true;
}

TransformLibraryRep& JSONParser::__parseTransformLibrary(const rapidjson::Value::ConstMemberIterator& itr) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseTransformLibrary",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseTransformLibrary",
                        " const rapidjson::Value& " );
	// TransformLibraryRep tlr;
	tmptlr = TransformLibraryRep();
	int required = 0;
	if(!(itr->value.IsObject()))
	{

		// TODO - log error
		std::string msg("JSONParser::parse(): transform_library is not an object!");
		Logger* logger = Logger::get_logger();
		logger->log(ERROR, msg.c_str());
		assert(false);
	}
	for(rapidjson::Value::ConstMemberIterator it = itr->value.MemberBegin(); it != itr->value.MemberEnd(); ++it)
	{
		std::string name = it->name.GetString();
		int nl = name.length();
		if(name.compare(0, nl, "name") == 0)
		{
			tmptlr.set_library_name(it->value.GetString());
			required++;
		}
	}
	return tmptlr;
}

DebugLibraryRep& JSONParser::__parseDebugLibrary(const rapidjson::Value::ConstMemberIterator& itr) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseDebugLibrary",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseDebugLibrary",
                        " const rapidjson::Value& " );
	// DebugLibraryRep dlr;
	tmpdlr = DebugLibraryRep();
	int required = 0;
	if(!(itr->value.IsObject()))
	{

		// TODO - log error
		std::string msg("JSONParser::parse(): debug_library is not an object!");
		Logger* logger = Logger::get_logger();
		logger->log(ERROR, msg.c_str());
		assert(false);
	}
	for(rapidjson::Value::ConstMemberIterator it = itr->value.MemberBegin(); it != itr->value.MemberEnd(); ++it)
	{
		std::string name = it->name.GetString();
		int nl = name.length();
		if(name.compare(0, nl, "name") == 0)
		{
			tmpdlr.set_library_name(it->value.GetString());
			required++;
		}
	}
	return tmpdlr;
}

CommandLibraryRep& JSONParser::__parseCommandLibrary(const rapidjson::Value::ConstMemberIterator& itr) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseCommandLibrary",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseCommandLibrary",
                        " const rapidjson::Value& " );
	// CommandLibraryRep clr;
	tmpclr = CommandLibraryRep();
	int required = 0;
	if(!(itr->value.IsObject()))
	{

		// TODO - log error
		std::string msg("JSONParser::parse(): command_library is not an object!");
		Logger* logger = Logger::get_logger();
		logger->log(ERROR, msg.c_str());
		assert(false);
	}
	for(rapidjson::Value::ConstMemberIterator it = itr->value.MemberBegin(); it != itr->value.MemberEnd(); ++it)
	{
		std::string name = it->name.GetString();
		int nl = name.length();
		if(name.compare(0, nl, "name") == 0)
		{
			tmpclr.set_library_name(it->value.GetString());
			required++;
		}
	}
	return tmpclr;
}

InjectLibraryRep& JSONParser::__parseInjectLibrary(const rapidjson::Value::ConstMemberIterator& itr) {
	SWDEBUGP2( 5, Verify::PARSER, "JSONParser::__parseInjectLibrary",
                        " const rapidjson::Value& " );
	SWDEBUG2( 5, Verify::TRACE, "JSONParser::__parseInjectLibrary",
                        " const rapidjson::Value& " );
	// InjectLibraryRep ilr;
	tmpilr = InjectLibraryRep();
	int required = 0;
	if(!(itr->value.IsObject()))
	{

		// TODO - log error
		std::string msg("JSONParser::parse(): inject_library is not an object!");
		Logger* logger = Logger::get_logger();
		logger->log(ERROR, msg.c_str());
		assert(false);
	}
	for(rapidjson::Value::ConstMemberIterator it = itr->value.MemberBegin(); it != itr->value.MemberEnd(); ++it)
	{
		std::string name = it->name.GetString();
		int nl = name.length();
		if(name.compare(0, nl, "name") == 0)
		{
			tmpilr.set_library_name(it->value.GetString());
			required++;
		}
	}
	return tmpilr;
}

