/*
 *    Verify.hpp
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

#ifndef INCLUDE_DEBUG_VERIFY_HPP_
#define INCLUDE_DEBUG_VERIFY_HPP_

#include <fstream>
#ifdef MULTI_THREAD
#include <thread>
#include <mutex>
#include <map>
#endif

// Define a dummy basic service library static initialization function
// to ensure the static variable definitions are linked into the application.
extern void debug_statics_init( void );

/************************************************************************
 *	Define the number of valid debugging types supported by this
 *	version of the of the Program Verification services.
 ************************************************************************
 */

const unsigned		NUM_2654_DEBUG_TYPES = 13;

/************************************************************************
 *	The Verify class is used as a base class by the other Program
 *	Verification service classes.
 *
 *	To ensure it's use (only) as a base class, the constructor and
 *	destructor have been defined as protected member functions.
 ************************************************************************
 */

class Verify
{
    // friend class Verify_init;

public:
    /*********************************************************************
     *	Define the valid debugging types supported by this version of the
     *	of the Program Verification services.
     *********************************************************************
     */
    enum DebugTypes
    {
	APP,		// for use in application program
	CHANNEL,	// for communications channel checking
	FACTORY,	// for Factory classes checking
	PARSER,		// for Parser checking
	REPOSITORY,	// for Repository class checking
	WRAPPER,	// for Wrapper class checking
	MODEL,		// IEEE2654Tree data model checking
	BUS,		// for communications bus checking
	DSL,		// for Domain Specific Language checking
	BUILDER,	// for builder class checking
	TRACE,		// for use in tracing control flow
	LOG,		// for Log checking
	DEBUG,		// for debug utilities checking
    };

    // selectors
    unsigned		getLevel( ) const;
    int			getValue( DebugTypes debug_type ) const;

    // modifiers
    int			initValue( const std::string& init_value );
    int			initLog( const std::string& log_file );
    int			setValue( int ival, DebugTypes debug_type );
    int			setValue( int ival, const char* name );
    int			setAllValues( int ival );

// # ifdef DEBUG_DUMP
    void		dump( std::ostream& os ) const;
// # endif

protected:
    // constructor and destructors
    Verify( );
    ~Verify( );

    // selectors
    // const AppInfo&	getAppInfo( ) const;
    const char*		getSource( ) const;
    unsigned		getTraceValue( ) const;

    // modifiers
    void		setTrace( int trace_value );
    void		traceEntry( const std::string& functions,
					const std::string& mesg = std::string( ) );
    void		traceExit( const std::string& function );

private:
    const char*		getName( DebugTypes debug_type ) const;
    // The next two functions abstract the construction and destruction
    // of the app_info_p object in both thread and non-thread modes.
    // static void		createAppInfo( );
    // static void		deleteAppInfo( );
    // Abstractions used to support MULTI_THREAD
    unsigned		getCurrentLevel( ) const;
    void		incCurrentLevel( );
    void		decCurrentLevel( );
    //	The current value for each debugging type is stored in a structure
    //	with the text string which identifies the debugging type.  These
    //	structures are collected into a static array for use within all
    //	of the instance of the Testability classes.

    struct type_values
    {
	const char *	name;
	unsigned	value;
    };

    static type_values		type_info[NUM_2654_DEBUG_TYPES];

#ifndef MULTI_THREAD
    //	Each instance of the Testability classes shares access to the
    //	global repository of information about the application.

    // static AppInfo *	app_info_p;

    //	Each instance of the Testability classes stores it's own debugging
    //	level (the order in which the instances were constructed), and a
    //	flag which specifies whether the destructor of the subclass must
    //	log a message on exit from scope.

    // member data
    static int init_count;
    static unsigned	debug_level;		// The current debug level
#else
    struct thread_data {
	    unsigned debug_level;
    };
    // member data
    static int init_count;
    static std::map<pthread_t, struct thread_data*> thread_data_map;
#endif
#ifdef MULTI_THREAD
	int	getRefCnt( ) const;
	void	incRefCnt( );
	void	decRefCnt( );
#else
	int	getRefCnt( ) const { return init_count; }
	void	incRefCnt( ) { init_count++; }
	void	decRefCnt( ) { --init_count; }
#endif
    unsigned		level;			// debugging level
    int			trace;			// trace flag
};

#if 0
inline const AppInfo& Verify::getAppInfo( ) const
{
	return *app_info_p;
}

inline void Verify::createAppInfo( )
{
	app_info_p = new AppInfo;
}

inline void Verify::deleteAppInfo( )
{
	delete app_info_p;
}

inline unsigned Verify::getCurrentLevel( ) const
{
	return debug_level;
}

inline void Verify::incCurrentLevel( )
{
	debug_level++;
}

inline void Verify::decCurrentLevel( )
{
	--debug_level;
}
#endif

inline int Verify::getValue( DebugTypes debug_type ) const
{
	return type_info[debug_type].value;
}

inline const char* Verify::getName( DebugTypes debug_type ) const
{
	return type_info[debug_type].name;
}

inline unsigned Verify::getLevel( ) const
{
	return level;
}

inline unsigned Verify::getTraceValue( ) const
{
	return trace;
}

/************************************************************************
 *	The SwDebug class provides a simple mechanism to permit the
 *	programmer to log debugging information, and optionally to trace
 *	the entry and exit of a particular function.  It is derived from
 *	thie Verify base class.
 *
 *	The class uses two data elements, trace, which is used by the
 *	constructor and destructor to enable the tracing of function
 *	entry and exit, and value, which represents the threshold
 *	value for a particular instance of this class.
 ************************************************************************
 */

class SwDebug : public Verify
{
public:
    // constructors and destructors
    SwDebug( );
    SwDebug( unsigned threshold, DebugTypes type,
			const std::string& func_name,
			const std::string& mesg =std::string( ) );
    SwDebug( unsigned threshold, DebugTypes type,
			const char* func_name,
			const char* mesg ="" );
    ~SwDebug( );

    // logging functions
    void		log( unsigned threshold,
				DebugTypes type,
				const std::string& mesg );

// # ifdef DEBUG_DUMP
    void		dump( std::ostream& os ) const;
// # endif

private:
    std::string		funcname;
};

#ifdef	USE_SWDEBUG
#define	SWDEBUG0( )	SwDebug swtrace
#define	SWDEBUG1(THRESH, TYPE, FUNC)	SwDebug	swtrace( THRESH, TYPE, FUNC )
#define	SWDEBUG2(THRESH, TYPE, FUNC, MESG)	\
				SwDebug swtrace( THRESH, TYPE, FUNC, MESG )
#define	SWDEBUG_LOG(THRESH, TYPE, MESG)     swtrace.log( THRESH, TYPE, MESG )
#define	SWDEBUGP0( )	SwDebug swtracep
#define	SWDEBUGP1(THRESH, TYPE, FUNC)	SwDebug	swtracep( THRESH, TYPE, FUNC )
#define	SWDEBUGP2(THRESH, TYPE, FUNC, MESG)	\
				SwDebug swtracep( THRESH, TYPE, FUNC, MESG )
#define	SWDEBUGP_LOG(THRESH, TYPE, MESG)     swtracep.log( THRESH, TYPE, MESG )
#else
#define	SWDEBUG0( )
#define	SWDEBUG1(THRESH, TYPE, FUNC)
#define	SWDEBUG2(THRESH, TYPE, FUNC, MESG)
#define SWDEBUG_LOG(THRESH, TYPE, MESG)
#define	SWDEBUGP0( )
#define	SWDEBUGP1(THRESH, TYPE, FUNC)
#define	SWDEBUGP2(THRESH, TYPE, FUNC, MESG)
#define SWDEBUGP_LOG(THRESH, TYPE, MESG)
#endif
#endif /* INCLUDE_DEBUG_VERIFY_HPP_ */
