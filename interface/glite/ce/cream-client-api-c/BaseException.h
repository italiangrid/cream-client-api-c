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

#ifndef _GLITE_CE_CREAM_CLIENT_API_CREAMEX_BASEEX_H__
#define _GLITE_CE_CREAM_CLIENT_API_CREAMEX_BASEEX_H__

#include<exception>
#include<string>
#include<ctime>
#include <cstring> // for memset
#include <boost/lexical_cast.hpp>

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace cream_exceptions {

	/** An object of this class is raised as an exception when the remote 
	  CREAM Web Service sends back to the client a BaseFault, 
	  or when the fault type is not recognized
	 */
	class BaseException : public std::exception {
	  
	  std::string  m_methodname;
	  std::string  m_errorcode;
	  std::string  m_description;
	  std::string  m_faultcause;
	  std::string  m_whatinfo;
	  time_t       m_timestamp;
	  
	public:

	  /**
	    BaseException constructor. This is usually invoked by other cream-client's classes
	  */
	  BaseException(const std::string& mn,
			const std::string& ec,
			const std::string& des,
			const std::string& fc,
			const time_t& t) 
	    : m_methodname(mn), m_errorcode(ec), m_description(des), m_faultcause(fc), m_timestamp(t) {}

	  virtual ~BaseException() throw() {}

	  /**
	    \return The human readable reason of the fault returned by the CREAM service. Actually this is the 
	    concatenation of the pieces of information returned by the method getDescription(), getMethodName(), getErrorCode(), getFaultCause(),
	    getTimeStamp()
	   */
	  virtual const char* what()  throw() { 
	    char timestamp[40]; 
	    struct tm TSTAMP;
	    memset((void*)timestamp, 0, 40); 
	    localtime_r(&m_timestamp, &TSTAMP);
	    strftime(timestamp, sizeof(timestamp), "%a %d %b %Y %T", &TSTAMP);

	  
	      m_whatinfo = "MethodName=[";
	      m_whatinfo += m_methodname;
	      m_whatinfo += "] ErrorCode=[";
	      m_whatinfo += m_errorcode;
	      m_whatinfo += "] Description=[";
	      m_whatinfo += m_description;
	      m_whatinfo += "] FaultCause=[";
	      m_whatinfo += m_faultcause;
	      m_whatinfo += "] Timestamp=[";
	      try {
	        m_whatinfo += boost::lexical_cast<std::string>( timestamp );
	      } catch(exception& ex) {
	        m_whatinfo += "Not available due to a cast error: ";
		m_whatinfo += ex.what();
	      }
	      m_whatinfo += "]";
	      
	  
	    
	    return m_whatinfo.c_str();
	  }

	  /**
	    \return The CREAM's method that raised the service's fault
	  */
	  virtual const char* getMethodName() const { return m_methodname.c_str(); }
	  /**
	    \return A CREAM internal error code
	  */
	  virtual const char* getErrorCode() const { return m_errorcode.c_str(); }
	  /**
	    \return The description of the fault returned by the service
	  */
	  virtual const char* getDescription() const { return m_description.c_str(); }
	  /**
	    \return The cause of the fault returned by the service
	  */
	  virtual const char* getFaultCause() const { return m_faultcause.c_str(); }
	  /**
	    \return The timestamp of the fault returned by the service
	  */	  
	  virtual time_t      getTimeStamp() const { return m_timestamp; }
	};
      }
    }
  }
}

#endif
