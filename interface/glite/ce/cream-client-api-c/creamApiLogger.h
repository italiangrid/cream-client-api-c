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

#ifndef GLITE_CE_CREAM_CLIENT_API_UTIL_CREAMAPILOGGER_H
#define GLITE_CE_CREAM_CLIENT_API_UTIL_CREAMAPILOGGER_H

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "boost/thread/recursive_mutex.hpp"

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace util {
	
	class creamApiLogger {
	public:
	  
	  static boost::recursive_mutex mutex;

	  /**
	   * Builds and returns the singleton instance of this
	   * class.
	   * 
	   * @return a pointer to the singleton instance
	   */    
	  static creamApiLogger* instance( void );
	  
	  /**
	   * Destructor. This actually does nothing.
	   */
	  virtual ~creamApiLogger();
	  
	  // Accessors
	  
	  /**
	   * Returns a pointer to the root logger.
	   *
	   * @result the pointer to the root logger
	   */
	  log4cpp::Category* getLogger( void ) {
	    return m_logger;
	  };
	  
	  /**
	   * Returns a pointer to the console logger.
	   *
	   * @result the pointer to the console logger
	   */              
	  log4cpp::Appender* getConsoleAppender( void ) {
	    return m_console_appender;
	  };
	  
	  /**
	   * Returns a pointer to the logfile logger.
	   *
	   * @result the pointer to the logfile logger; may be 0
	   * if no logfile appender has been set by calling
	   * setLogFile().
	   * @see setLogFile();
	   */
	  log4cpp::Appender* getLogfileAppender( void ) {
	    return m_logfile_appender;
	  };
	  
	  /**
	   * Returns true if logging on the console is enabled
	   *
	   * @result true if logging on the console is enabled
	   */
	  bool isConsoleEnabled( void ) const {
	    return m_consoleEnabled; 
	  };
	  
	  /**
	   * Returns true if logging on the logfile is enabled
	   *
	   * @result true if logging on the logfile is enabled
	   */
	  bool isLogfileEnabled( void ) const {
	    return m_logfileEnabled; 
	  };
	  
	  // Modifiers
	  
	  /**
	   * Enables or disables logging on the console.
	   *
	   * @param b if true, then logging on the console will be
	   * enabled. If false, no message will be displayed on
	   * the console.
	   * @see setLogFile();
	   */
	  void setConsoleEnabled( bool b ) {
	    m_consoleEnabled = b;
	  };
	  
	  /**
	   * Enables or disables logging on the logfile.
	   *
	   * @param b if true, then logging on the logfile will be
	   * enabled. If false, no message will be sent to the
	   * logfile.
	   * @see setLogFile();
	   */
	  void setLogfileEnabled( bool b ) {
	    m_logfileEnabled = b;
	  };
	  
	  /**
	   * Returns the name of a log file, build according with
	   * some default rules.  @todo{Should this be put outside
	   * this class? Should this function be made stand-alone,
	   * as it does not depend on any data member of this
	   * class?}
	   *
	   * @param basedir the pathname of the logfile
	   * @param basename the base name of the logfile
	   * @result the fully qualified logfile name
	   */   
	  std::string getLogFileName( const char* basedir, const char* basename );
	  
	  /**
	   * Instantiates an appender for writing to a logfile. If
	   * a logfile appender was already defined, then the old
	   * one is discarded and a new one created instead.
	   *
	   * @param fname the name of the logfile. If a fila with
	   * that name already exists, then new data will be
	   * appended to it.
	   */
	  void setLogFile( const std::string& fname );

          /**
           * Sets the maximum log file size (in bytes) before the log
           * is rotated. The default maximum log file size is
           * 500Kbytes. This function can only be called _before_
           * setLogFile is called, otherwise it will have no effect.
           *
           * @param s the maximum log file size, in bytes. 
           */	  
	  void setMaxLogFileSize( size_t s ) { m_max_logfile_size = s; };

          /**
           * Sets the maximum number of rotate log files to keep
           * (default: 10). After the logfile is rotated more than
           * this number of times, it is discarded. This function can
           * only be called _before_ setLogFile is called, otherwise
           * it will have no effect.
           * 
           * @param n The maximum number of times a logfile can be rotated
           */
          void setMaxLogFileRotations( unsigned int n ) { m_max_logfile_rotations = n; };

	  /**
	   * @deprecated{This method is provided for compatibility
	   * _only_, and should be considered as deprecated. This
	   * method prints a message with a given priority level
	   * on the console or logfile (or both).}
	   *
	   * @param pri the priority level of this message
	   * @param msg the message to be printed
	   * @param outputDate currently ignored
	   * @param writeToFile if true, the message is written to the log file
	   * @param writeToConsole if true, the message is written to the console
	   */
	  void log( const log4cpp::Priority::PriorityLevel& pri, const std::string& msg,
		    bool outputDate, bool writeToFile, bool writeToConsole );
	protected:
	  
	  /**
	   * This Filter is used to check wether logging on the
	   * console is enabled or not.
	   */
	  class consoleFilter;
	  
	  /**
	   * This Filter is used to check wether logging on the
	   * logfile is enabled or not.
	   */
	  class logfileFilter;
	  
	  /**
	   * Default constructor. This method is called by the
	   * instance() method to initialize the singleton
	   * instance of the creamApiLogger class.  This method
	   * creates the _logger log4cpp::Category object.
	   * _logger is bound to a log4cpp::OstreamAppender which
	   * sends messages to stderr. The user may initialize and
	   * attach a logfile appender by invoking the
	   * setLogFile() method. In this case, messages will be
	   * sent to the console _and_ to the logfile.
	   * 
	   * @par By default the logging severity is set to
	   * log4cpp::Priority::FATAL. This means that, by
	   * default, only fatal messages will appear on the
	   * console (and/or logfile). The user may lower the
	   * global priority level (i.e., the severity level of
	   * all loggers) with the following command:
	   *
	   * @code
	   * creamApiLogger::instance()->getLogger()->setPriority( log4cpp::Priority::DEBUG );
	   * @endcode
	   */
	  creamApiLogger( void );
	  
	  /**
	   * Utility function used to create a new
	   * log4cpp::PatternLayout object with the given pattern
	   * layout
	   * 
	   * @param pattern the pattern to use for the layout
	   * @result the new log4cpp::PatternLayout object. The
	   * user owns the result, and thus is responsible for
	   * (eventually) deallocating it.
	   */
	  
	  log4cpp::Layout* mkLayout( const char* pattern ) const;
	  
	  static creamApiLogger *s_instance;
	  log4cpp::Category *m_logger;
	  log4cpp::Appender *m_console_appender;
	  log4cpp::Appender *m_logfile_appender;
	  bool m_consoleEnabled;
	  bool m_logfileEnabled;
          size_t m_max_logfile_size;
          unsigned int m_max_logfile_rotations;
	  
	  static const char* s_pattern; //< This patter is used to instantiate the default log4cpp::Layout objects. It displays the current date, the severity level and the message
	};

        // The following macro can be used in a multithreaded environment
        // to ensure that logging calls do not happen concurrently.
        // The macro can be invoked as follows:
        //
        // CREAM_SAFE_LOG( m_log_dev->debugStream() << foo << bar << baz << log4cpp::CategoryStream::ENDLINE );
        //

#ifndef CREAM_SAFE_LOG
#define CREAM_SAFE_LOG( cmds ) { boost::recursive_mutex::scoped_lock cream_safe_log_mutex( glite::ce::cream_client_api::util::creamApiLogger::mutex ); cmds; }
#endif	

      } // namespace util
    } // namespace cream_client_api
  } // namespace ce
} // namespace glite

#endif
