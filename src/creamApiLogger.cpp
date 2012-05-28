/* LICENSE:
Copyright (c) Members of the EGEE Collaboration. 2010. 
See http://www.eu-egee.org/partners/ for details on the copyright
holders.  

Licensed under the Apache License, Version 2.0 (the "License"); 
you may not use this file except in compliance with the License. 
You may obtain a copy of the License at 

   http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software 
distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
implied. 
See the License for the specific language governing permissions and 
limitations under the License.

END LICENSE */

#include "glite/ce/cream-client-api-c/creamApiLogger.h"
#include "log4cpp/Category.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/RollingFileAppender.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Filter.hh"
#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <sstream>
#include "boost/algorithm/string.hpp"

extern "C" {
#include <sys/types.h>
#include <unistd.h>
}

using namespace std;
namespace util = glite::ce::cream_client_api::util;

util::creamApiLogger *util::creamApiLogger::s_instance = 0;
boost::recursive_mutex util::creamApiLogger::mutex;
const char* util::creamApiLogger::s_pattern = "%d %p - %m%n"; 


//////////////////////////////////////////////////////////////////////////////
//
// consoleFilter demfinition
//
//////////////////////////////////////////////////////////////////////////////
class util::creamApiLogger::consoleFilter : public log4cpp::Filter {
public:
    consoleFilter() : log4cpp::Filter() { };
protected:
    virtual log4cpp::Filter::Decision _decide( const log4cpp::LoggingEvent &ev ) {
        if ( util::creamApiLogger::instance()->isConsoleEnabled() )
            return log4cpp::Filter::ACCEPT;
        else
            return log4cpp::Filter::DENY;
    }
};


//////////////////////////////////////////////////////////////////////////////
//
// logfileFilter definition
//
//////////////////////////////////////////////////////////////////////////////
class util::creamApiLogger::logfileFilter : public log4cpp::Filter {
public:
    logfileFilter() : log4cpp::Filter() { };
protected:
    virtual log4cpp::Filter::Decision _decide( const log4cpp::LoggingEvent &ev ) {
        if ( util::creamApiLogger::instance()->isLogfileEnabled() )
            return log4cpp::Filter::ACCEPT;
        else
            return log4cpp::Filter::DENY;
    }
};


//////////////////////////////////////////////////////////////////////////////
//
// creamApiLogger definitions
//
//////////////////////////////////////////////////////////////////////////////
util::creamApiLogger* util::creamApiLogger::instance( void ) 
{
    if ( 0 == s_instance )
        s_instance = new creamApiLogger();
    return s_instance;
}


util::creamApiLogger::creamApiLogger( ) :
    m_logger( 0 ),
    m_console_appender( 0 ),
    m_logfile_appender( 0 ),
    m_consoleEnabled( true ),
    m_logfileEnabled( true ),
    m_max_logfile_size( 0 ), // 500 KBytes
    m_max_logfile_rotations( 1 )
{
    // Instantiates loggers
    m_logger = &log4cpp::Category::getInstance( "org.glite.ce.cream_client_api.util.creamApiLogger" );
    m_logger->setPriority( log4cpp::Priority::FATAL );
    m_logger->getRoot().removeAllAppenders();

    // Instantiates appenders
    m_console_appender = new log4cpp::OstreamAppender( "ConsoleAppender", &std::cout );
    m_console_appender->setFilter( new util::creamApiLogger::consoleFilter() );

    // _logfile_appender is not instantiated by default.
    // Use redirectOutput() to do this
    m_console_appender->setLayout( mkLayout( s_pattern ) );

    // Binds appenders to the logger
    m_logger->addAppender( m_console_appender );   
}


void util::creamApiLogger::setLogFile( const string& fname )
{
    if ( m_logfile_appender ) {
        // Delete old appender
        m_logger->removeAppender( m_logfile_appender );
        delete m_logfile_appender;
    }
    m_logfile_appender = new log4cpp::RollingFileAppender( 
							  "FileAppender", 
							  fname, 
							  m_max_logfile_size, 
							  m_max_logfile_rotations );

    m_logfile_appender->setLayout( mkLayout( s_pattern ) );
    m_logfile_appender->setFilter( new util::creamApiLogger::logfileFilter() );
    m_logger->addAppender( m_logfile_appender );
}


util::creamApiLogger::~creamApiLogger( )
{

}

string util::creamApiLogger::getLogFileName(const char* basedir, const char* basename)
{
    ostringstream result;
    
    time_t t = time(NULL);
    struct tm *T = localtime(&t);
    char timestamp[30];
    // memset((void*)timestamp, 0, 30);
    snprintf(timestamp, sizeof(timestamp), "_%.4d%.2d%.2d-%.2d%.2d%.2d.log",
             T->tm_year+1900, T->tm_mon+1, T->tm_mday, T->tm_hour,
             T->tm_min, T->tm_sec);
    
    string Basedir( basedir );
    //if(!util::string_manipulation::endsWith(Basedir,"/")) 
    if(!boost::ends_with(Basedir,"/")) 
      Basedir = Basedir + "/";
    
    result <<  Basedir << basename << "_CREAM_";
    
    if ( getenv("LOGNAME") )
        result << getenv("LOGNAME");
    else 
        result << getuid();
    
    result << timestamp << std::ends;

    return result.str();
}


void util::creamApiLogger::log( const log4cpp::Priority::PriorityLevel& pri, 
                                const string& msg,
                                bool outputDate, // actually ignored for now
                                bool writeToFile, 
                                bool writeToConsole )
{
    bool _tmpConsole = isConsoleEnabled();
    bool _tmpLogfile = isLogfileEnabled();
    setConsoleEnabled( writeToConsole );
    setLogfileEnabled( writeToFile );
    util::creamApiLogger::instance()->getLogger()->log( pri, msg );
    setConsoleEnabled( _tmpConsole );
    setLogfileEnabled( _tmpLogfile );
}


log4cpp::Layout* util::creamApiLogger::mkLayout( const char* pattern ) const
{
    log4cpp::PatternLayout *result = new log4cpp::PatternLayout( );
    result->setConversionPattern( pattern );
    return result;
}

