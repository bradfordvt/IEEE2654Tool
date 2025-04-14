/*
 *    svcstat.cpp
 *
 *    Class static members of the Verify base class of the Testability services.
 *
 *    Class static members of the Verify base class of the Testability services.
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
static const char __date__[] = "2024/12/07";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

#include 	"debug/Verify.hpp"

/**********************************************************************
 *	Define static elements of the Verify class.
 *
 *	The output port for the Testability service classes is
 *	initialized to STDERR.
 *
 *	The array of debugging and tracing values for the instances
 *	of the testability services are initially set to zero.
 **********************************************************************
 */

Verify::type_values		Verify::type_info[NUM_2654_DEBUG_TYPES] =
{
	"APP", 0,		// application tracing
	"CHANNEL", 0,		// for communications channel checking
	"FACTORY", 0,		// for Factory classes checking
	"PARSER", 0,		// for Parser checking
	"REPOSITORY", 0,	// for Repository class checking
	"WRAPPER", 0,		// for Wrapper class checking
	"MODEL", 0,		// IEEE2654Tree data model checking
	"BUS", 0,		// for communications bus checking
	"DSL", 0,		// for Domain Specific Language checking
	"BUILDER", 0,		// for builder class checking
	"TRACE", 0,		// for use in tracing control flow
	"LOG", 0,		// for Log checking
	"DEBUG", 0,		// for debug utilities checking
};

unsigned		Verify::debug_level = 0;
// List<Verify::type_mods> *	Verify::mod_stack = 0;

// AppInfo *		Verify::app_info_p = 0;
// OutMesgPort *		Verify::out_port_p = 0;

int			Verify::init_count = 0;

/**********************************************************************
 *	debug_statics_init( )	Dummy function to ensure that
 *				this module is linked.
 *
 *	Returns:		Nothing.
 **********************************************************************
 */

void debug_statics_init( void )
{
	return;
}

