/*
 *    Verify.cpp
 *
 *    Class to implement the member functions of the Verify base
 *    class of the Testability services.
 *
 *    Class to implement the member functions of the Verify base
 *    class of the Testability services.
 *    The class implements the Base element of the Testability services
 *    used to trace execution of the program's flow.
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

#include <ostream>
#include "debug/Verify.hpp"
#include "log/Logger.hpp"
#include <string>

/**********************************************************************
 *	Define the constant text strings used within this module.
 **********************************************************************
 */

static const char *		ALL_TYPE = "ALL";
static const char *		COMMON_TYPE = "COMMON";

static const char *		TRACE_ENTRY = "entering ";
static const char *		TRACE_EXIT = "exiting ";
static const char *		SRC_DELIM = ": ";
static const char *		PREFIX0 = "( ";
static const char *		SUFFIX0 = " )";

Verify::Verify( ) : trace(0) {
	if( getRefCnt() == 0 ) {
		debug_statics_init();
		/*
		 *	All Verify static members will be initialized
		 *	because the definitions of these statics are
		 *	contained in the file with the constructor called
		 *	by new above.
		 */
		// Verify::createAppInfo( );
	}
	incRefCnt();
	incCurrentLevel();
	level = getCurrentLevel();
}

Verify::~Verify( )
{
	decRefCnt( );
	if( getRefCnt( ) == 0 )
	{
		// Verify::deleteAppInfo( );
	}
	decCurrentLevel( );
}

/**********************************************************************
 *	initValue( )	Sets the initial value of a debugging type
 *			as specified by the input argument.
 *
 *	Preconditions:	The initialization argument (character pointer)
 *			is non-NULL.
 *
 *	Notes:		The form of init_thresh must be "type=number",
 *			where type is the name of a recognized debugging
 *			type, and number is a non-negative value to be
 *			assigned to the type.
 *
 *	Returns:	A -1 is returned if the form of the input
 *			argument is invalid.  Otherwise, the new
 *			value of the debugging type is returned.
 *********************************************************************
 */

int Verify::initValue( const std::string& init_thresh )
{
	int		eq_pos;
	int		ret_val = -1;
	std::string	type_name;
	int		type_value;

	if ( init_thresh.length( ) > 0 )
	{
	    type_name = init_thresh;
	    if ( ( eq_pos = type_name.find( "=" )) != std::string::npos )
	    {
		type_value = atoi( type_name.substr( eq_pos+1).c_str() );
		// check if conversion completed successfully
		if ( type_value >= 0 )
		{
		    type_name = type_name.substr( 0, eq_pos );
		    if ( type_name == ALL_TYPE )
		    {
			ret_val = setAllValues( type_value );
		    }
		    else if( type_name == COMMON_TYPE )
		    {
			setValue( type_value, Verify::BUILDER );
			setValue( type_value, Verify::BUS );
			setValue( type_value, Verify::CHANNEL );
			setValue( type_value, Verify::DSL );
			setValue( type_value, Verify::FACTORY );
			setValue( type_value, Verify::MODEL );
			setValue( type_value, Verify::PARSER );
			setValue( type_value, Verify::REPOSITORY );
			setValue( type_value, Verify::WRAPPER );
			ret_val = type_value;
		    }
		    else
		    {
			ret_val = setValue( type_value, type_name.c_str() );
		    }
		}
	    }
	}

	return ret_val;
}

#ifndef RW_MULTI_THREAD
/**********************************************************************
 *	setValue( )	Specifies the value of a debugging type	as specified
 *			by the input arguments.
 *
 *	Returns:	The previous threshold value associated
 *			with the debugging type.
 *********************************************************************
 */

int Verify::setValue( int ival, DebugTypes debug_type )
{
	int old_value;

	// adjust the current value for the debugging type
	old_value = type_info[debug_type].value;
	type_info[debug_type].value = ival;

	return old_value;
}

/**********************************************************************
 *	setValue( )	Specifies the value of a debugging type	as specified
 *			by the input arguments.
 *
 *	Returns:	The previous threshold value associated
 *			with the debugging type.
 *********************************************************************
 */

int Verify::setValue( int ival, const char* name )
{
	int old_value;
	int i;

	for( i = 0; i < NUM_2654_DEBUG_TYPES; i++ )
	    if( name == type_info[ i ].name )
	    {
	        old_value = type_info[i].value;
	        type_info[i].value = ival;
		break;
	    }

	return old_value;
}

/**********************************************************************
 *	setAllValues( )	Specifies the value of all debugging types
 *			to the input argument.
 *
 *	Returns:	The value passed.
 *********************************************************************
 */

int Verify::setAllValues( int ival )
{
	int i;

	for( i = 0; i < NUM_2654_DEBUG_TYPES; i++ )
	    type_info[ i ].value = ival;

	return ival;
}
#endif

/**********************************************************************
 *	setTrace( )	Specify whether function tracing is activated
 *			for this object.
 *
 *	Returns:	VOID.
 *********************************************************************
 */

void Verify::setTrace( int trace_value )
{
	trace = trace_value;

	return;
}

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

void Verify::traceEntry( const std::string& function, const std::string& mesg )
{
	std::string trace_message( getSource( ) );
	trace_message += SRC_DELIM;
	trace_message += TRACE_ENTRY;
	trace_message += function;
        if ( mesg.length( ) > 0 )
	        trace_message += PREFIX0 + mesg + SUFFIX0;

	Logger *l_p = Logger::get_logger();
	l_p->log(LOG_TYPE::NOTICE, trace_message.c_str());

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

void Verify::traceExit( const std::string& function )
{
	std::string trace_message( getSource( ) );
	trace_message += SRC_DELIM;
	trace_message += TRACE_EXIT;
	trace_message += function;

	Logger *l_p = Logger::get_logger();
	l_p->log(LOG_TYPE::NOTICE, trace_message.c_str());

	return;
}

/**********************************************************************
 *	getSource( )	Produces a message header with the name and
 *			process ID of the current program.
 *
 *	Returns:	String.
 *********************************************************************
 */

const char* Verify::getSource( ) const
{
	return "IEEE2654Tool";
}

/**********************************************************************
 *	dump( )		Dump values of current member elements to
 *			the user specified output stream.
 *
 *	Returns:	VOID
 *********************************************************************
 */
#ifdef DEBUG_DUMP
void Verify::dump( std::ostream& os ) const
{
	DebugTypes		i;

	os << "Verify(this=" << (void*)this << ")" << std::endl;
	os << "  level = " << level << std::endl;
	os << "  trace = " << trace << std::endl;

	os << "  TypeInfo:" << std::endl;
	for ( i = Verify::APP; i < NUM_2654_DEBUG_TYPES; i++ )
	    os << "    [" << (int)i << "] " << getName( i )
			<< " = " << getValue( i ) << std::endl;

	return;
}
#endif
