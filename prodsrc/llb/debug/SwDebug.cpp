/*
 *    SwDebug.cpp
 *
 *    Class to implement the member functions of the SwDebug
 *    class of the Testability services.
 *
 *    Class to implement the member functions of the SwDebug
 *    class of the Testability services.
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

#include "debug/Verify.hpp"
#include "log/Logger.hpp"

/**********************************************************************
 *	SwDebug( )	Constructor for a SwDebug object
 *
 *	Returns:	Nothing.
 **********************************************************************
 */

SwDebug::SwDebug( ) { }

/**********************************************************************
 *	SwDebug( )	Constructor for a SwDebug object
 *
 *	Notes:		The use of this constructor implements the
 *			function entry and exit tracing feature.
 *
 *	Returns:	Nothing.
 **********************************************************************
 */

SwDebug::SwDebug( unsigned threshold, Verify::DebugTypes type,
			const std::string& func_name, const std::string& mesg )
{
	funcname = func_name;

	if ( threshold <= getValue( type ) )
	{
	    traceEntry( func_name, mesg );
	    setTrace( threshold );
	}
}

/**********************************************************************
 *	SwDebug( )	Constructor for a SwDebug object
 *
 *	Notes:		The use of this constructor implements the
 *			function entry and exit tracing feature.
 *
 *	Returns:	Nothing.
 **********************************************************************
 */

SwDebug::SwDebug( unsigned threshold, Verify::DebugTypes type,
			const char* func_name, const char* mesg )
{
	funcname = std::string(func_name);

	if ( threshold <= getValue( type ) )
	{
	    std::string msg( mesg );
	    traceEntry( funcname, msg );
	    setTrace( threshold );
	}
}

/**********************************************************************
 *	~SwDebug( )	Destructor for a SwDebug object.
 *
 *	Notes:		The destructor determine if tracing is enabled,
 *			and pops the function name from the stack if
 *			appropriate.
 *
 *	Returns:	Nothing.
 **********************************************************************
 */

SwDebug::~SwDebug( )
{
	if ( getTraceValue( ) )
	    traceExit( funcname );
}
/**********************************************************************
 *	log( )		Pass information to the debugging output log.
 *			Uses threshold value to control whether
 *			message is logged or ignored.
 *
 *	Returns:	VOID.
 *********************************************************************
 */

void SwDebug::log( unsigned threshold,
		Verify::DebugTypes type, const std::string& mesg )
{
	if ( threshold < getValue( type ) )
	{
	    std::string log_message( getSource( ) );
	    log_message += ":  ";
	    log_message += mesg;
	    Logger *l_p = Logger::get_logger();
	    l_p->log(LOG_TYPE::NOTICE, log_message.c_str());
	}

	return;
}

/**********************************************************************
 *	dump( )		Dump values of current member elements to
 *			the user specified output stream.
 *
 *	Returns:	VOID
 *********************************************************************
 */
# ifdef DEBUG_DUMP
void SwDebug::dump( std::ostream& os ) const
{
	os << "SwDebug.";
	Verify::dump( os );
	os << "  function name = " << funcname << endl;

	return;
}
# endif
