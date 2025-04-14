/*
 *    SwDebugLib.hpp
 *
 *    Class to implement the member functions of the SwDebugLib
 *    class of the Testability services.
 *
 *    Class to implement the member functions of the SwDebugLib
 *    class of the Testability services.
 * 
 * Copyright (C) 2025 Bradford G. Van Treuren
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

#ifndef INCLUDE_DEBUG_SWDEBUGLIB_HPP_
#define INCLUDE_DEBUG_SWDEBUGLIB_HPP_

#include <fstream>

/************************************************************************
 *	The SwDebugLib class provides a simple mechanism to permit the
 *	programmer to log debugging information in a plug-in library,
 *	and optionally to trace
 *	the entry and exit of a particular function.  It is derived from
 *	the Verify base class.
 *
 *	The class uses two data elements, trace, which is used by the
 *	constructor and destructor to enable the tracing of function
 *	entry and exit, and value, which represents the threshold
 *	value for a particular instance of this class.
 ************************************************************************
 */

template <typename T>
class SwDebugLib
{
public:
    // constructors and destructors
    SwDebugLib( T* inst_ );
    SwDebugLib( T* inst_,
			const std::string& func_name,
			const std::string& mesg =std::string( ) );
    SwDebugLib( T* inst_,
			const char* func_name,
			const char* mesg ="" );
    ~SwDebugLib( );

    void		traceEntry( const std::string& functions,
					const std::string& mesg = std::string( ) );
    void		traceExit( const std::string& function );

    // logging functions
    void		log( const char* filename, const std::string& mesg );

# ifdef DEBUG_DUMP
    void		dump( std::ostream& os ) const;
# endif

private:
    T* inst;
    std::string		funcname;
};

// #ifdef	USE_SWDEBUG
#define	SWDEBUG0( T, INST )	SwDebugLib<T> swtrace( INST )
#define	SWDEBUG1(T, INST, FUNC)	SwDebugLib<T>	swtrace( INST, FUNC )
#define	SWDEBUG2(T, INST, FUNC, MESG)	\
				SwDebugLib<T> swtrace( INST, FUNC, MESG )
#define	SWDEBUG_LOG(FILENAME, MESG)     swtrace.log( FILENAME, MESG )
/*
#else
#define	SWDEBUG0( T, INST )
#define	SWDEBUG1(T, INST, FUNC)
#define	SWDEBUG2(T, INST, FUNC, MESG)
#define SWDEBUG_LOG(T, MESG)
#endif
*/

/*
 *    SwDebugLib.cpp
 *
 *    Class to implement the member functions of the SwDebugLib
 *    class of the Testability services.
 *
 *    Class to implement the member functions of the SwDebugLib
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

/*
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
*/

#include <iostream>
#include "api/translator_api.h"
#include "debug/SwDebugLib.hpp"

static const char *		TRACE_ENTRY = "entering ";
static const char *		TRACE_EXIT = "exiting ";
static const char *		SRC_DELIM = ": ";
static const char *		PREFIX0 = "( ";
static const char *		SUFFIX0 = " )";

/**********************************************************************
 *	SwDebugLib( )	Constructor for a SwDebugLib object
 *
 *	Returns:	Nothing.
 **********************************************************************
 */

template <typename T>
SwDebugLib<T>::SwDebugLib( T* inst_ ) { inst = inst_; }

/**********************************************************************
 *	SwDebugLib( )	Constructor for a SwDebugLib object
 *
 *	Notes:		The use of this constructor implements the
 *			function entry and exit tracing feature.
 *
 *	Returns:	Nothing.
 **********************************************************************
 */

template <typename T>
SwDebugLib<T>::SwDebugLib( T* inst_,
			const std::string& func_name, const std::string& mesg )
{
	inst = inst_;
	funcname = func_name;

	traceEntry( func_name, mesg );
}

/**********************************************************************
 *	SwDebugLib( )	Constructor for a SwDebugLib object
 *
 *	Notes:		The use of this constructor implements the
 *			function entry and exit tracing feature.
 *
 *	Returns:	Nothing.
 **********************************************************************
 */

template <typename T>
SwDebugLib<T>::SwDebugLib( T* inst_,
			const char* func_name, const char* mesg )
{
	inst = inst_;
	funcname = std::string(func_name);

	std::string msg( mesg );
	traceEntry( funcname, msg );
}

/**********************************************************************
 *	~SwDebugLib( )	Destructor for a SwDebugLib object.
 *
 *	Notes:		The destructor determine if tracing is enabled,
 *			and pops the function name from the stack if
 *			appropriate.
 *
 *	Returns:	Nothing.
 **********************************************************************
 */

template <typename T>
SwDebugLib<T>::~SwDebugLib( )
{
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

template <typename T>
void SwDebugLib<T>::log( const char* filename, const std::string& mesg )
{
	std::string log_message( filename );
	log_message += ":  ";
	log_message += mesg;
	if(inst == NULL)
	{
		std::cerr << "NOTICE: " << log_message << std::endl;
	}
	else if(inst->translator_api == NULL)
	{
		std::cerr << "NOTICE: " << log_message << std::endl;
	}
	else
	{
		inst->translator_api->logger(inst, LOG_TYPE::NOTICE, log_message.c_str());
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
template <typename T>
void SwDebugLib<T>::dump( std::ostream& os ) const
{
	os << "SwDebug.";
	os << "  function name = " << funcname << endl;

	return;
}
# endif

/**********************************************************************
 *	traceEntry( )	Print message specifying function entry to
 *			output port.
 *
 *	Preconditions:	That the input argument "function" is not an
 *			empty string.
 *
 *	Returns:	VOID.
 *********************************************************************
 */

template <typename T>
void SwDebugLib<T>::traceEntry( const std::string& function, const std::string& mesg )
{
	std::string trace_message;
	trace_message += SRC_DELIM;
	trace_message += TRACE_ENTRY;
	trace_message += function;
        if ( mesg.length( ) > 0 )
	        trace_message += PREFIX0 + mesg + SUFFIX0;

	if(inst == NULL)
	{
		std::cerr << "NOTICE: " << trace_message << std::endl;
	}
	else if(inst->translator_api == NULL)
	{
		std::cerr << "NOTICE: " << trace_message << std::endl;
	}
	else
	{
		inst->translator_api->logger(inst, LOG_TYPE::NOTICE, trace_message.c_str());
	}

	return;
}

/**********************************************************************
 *	traceExit( )	Print message specifying function exit to
 *			output port.
 *
 *	Preconditions:	That the input argument "function" is not an
 *			empty string.
 *
 *	Returns:	VOID.
 *********************************************************************
 */

template <typename T>
void SwDebugLib<T>::traceExit( const std::string& function )
{
	std::string trace_message;
	trace_message += SRC_DELIM;
	trace_message += TRACE_EXIT;
	trace_message += function;

	if(inst == NULL)
	{
		std::cerr << "NOTICE: " << trace_message << std::endl;
	}
	else if(inst->translator_api == NULL)
	{
		std::cerr << "NOTICE: " << trace_message << std::endl;
	}
	else
	{
		inst->translator_api->logger(inst, LOG_TYPE::NOTICE, trace_message.c_str());
	}

	return;
}

#endif /* INCLUDE_DEBUG_SWDEBUGLIB_HPP_ */
