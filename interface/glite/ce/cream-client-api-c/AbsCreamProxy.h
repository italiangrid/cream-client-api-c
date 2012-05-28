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

#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_ABSCREAMPROXY_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_ABSCREAMPROXY_

#include <string>
#include <map>
#include <list>
#include <utility>

#include "boost/tuple/tuple.hpp"

#include "glite/ce/cream-client-api-c/cream_client_soapH.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"

#include "glite/ce/cream-client-api-c/ExceptionFactory.h"
#include "glite/ce/cream-client-api-c/JobIdWrapper.h"
#include "glite/ce/cream-client-api-c/JobStatusWrapper.h"
#include "glite/ce/cream-client-api-c/JobInfoWrapper.h"
#include "glite/ce/cream-client-api-c/auth_ex.h"
#include "glite/ce/cream-client-api-c/soap_ex.h"
#include "glite/ce/cream-client-api-c/soap_runtime_ex.h"

#include "glite/ce/cream-client-api-c/BaseException.h"
#include "glite/ce/cream-client-api-c/GenericException.h"
#include "glite/ce/cream-client-api-c/InvalidArgumentException.h"
#include "glite/ce/cream-client-api-c/GridProxyDelegationException.h"
#include "glite/ce/cream-client-api-c/JobSubmissionDisabledException.h"
#include "glite/ce/cream-client-api-c/JobStatusInvalidException.h"
#include "glite/ce/cream-client-api-c/JobUnknownException.h"
#include "glite/ce/cream-client-api-c/AuthorizationException.h"
#include "glite/ce/cream-client-api-c/DelegationException.h"
#include "glite/ce/cream-client-api-c/InternalException.h"
#include "glite/ce/cream-client-api-c/ConnectionTimeoutException.h"

extern "C" {
#undef IOV_MAX
#include "glite/security/glite_gsplugin.h"
};

#define SOAP_CONNECT_TIMEOUT 60
#define SOAP_RECV_TIMEOUT 60
#define SOAP_SEND_TIMEOUT 60

using namespace glite::ce::cream_client_api::cream_exceptions;

namespace log4cpp {
    class Category;
};

class CREAMTYPES__JobFilter;

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {
      
	class JobDescriptionWrapper;
	class JobFilterWrapper;
	class ResultWrapper;
	
	/// A Class implementing the CREAM communication protocol.
	/**
        	AbsCreamProxy is the CREAM C++ client hiding user from the tedious and complex details
		of the SOAP communication and authentication.\n
		An object of the class AbsCreamProxy CANNOT be instantiated because the class is
		abstract (the execute() method is pure virtual). 
		In order to interact with the CREAM CE Web Service the user must 
		invoke the proper static method of the class CreamProxyFactory to create
		an instance of a subclass of AbsCreamProxy. Each
		subclass is not abstract (because it implements the execute() method).\n
		
		The user is not supposed to know anything about the subclasses because the object to use
		is correctly built and (a pointer to it) returned by the CreamProxyFactory factory; this pointer
		is polimorphic and the user must assign it to a variable of type AbsCreamProxy.
		The subclasses are not instantiable by the user because their costructors are protected, only the factory can do it.\n

		CreamProxyFactory has different methods 
		to create different AbsCreamProxy subclass instances for different remote operations: 
		JobRegister, JobStart, JobCancel, JobList, etc.\n
		When an instance of (a subclass of) AbsCreamProxy has been returned
		by the factory, the two methods setCredential() and execute() can be invoked (in this order) to perform
		a CREAM operation.
		
		\see CreamProxyFactory

	*/
	class AbsCreamProxy {
	 
	  int m_ctimeout;
	  int m_iotimeout;
	  int m_nbio;
          int m_use_soap_header;
	  glite_gsplugin_Context m_ctx;
 
	  std::string m_soap_header;
 
	public:
 
	  /**
	     Data type for output argument of the JobRegister operation
	  */
	  typedef std::map< std::string, boost::tuple<JobIdWrapper::RESULT, JobIdWrapper, std::string> >      RegisterArrayResult;
	  /**
	     Data type for output argument of the JobStatus operation
	  */
	  typedef std::map< std::string, boost::tuple<JobStatusWrapper::RESULT, JobStatusWrapper, std::string> >  StatusArrayResult;
	  /**
	     Data type for output argument of the JobInfo operation
	  */
	  typedef std::map< std::string, boost::tuple<JobInfoWrapper::RESULT, JobInfoWrapper, std::string> >    InfoArrayResult;
	  /**
	     Data type for input argument of the JobRegister operation
	  */
	  typedef std::list<JobDescriptionWrapper*>                                           RegisterArrayRequest;

	  /**
	     An object of the class AbsCreamProxy cannot be created by the user, 
	     but the CreamProxyFactory allocates an instance of it on the heap, so the user
	     MUST free this instance after usage... then, of course, the class destructor must be public vritual. 
	  */
	  virtual ~AbsCreamProxy( ) throw();

	  /**
	     This is a polimorphic method. 
	     Its behaviour depends on which subclass of the AbsCreamProxy class
	     it is invoked on. \n
	     Each AbsCreamProxy's subclass implements in a different way the execute() method
	     in order to perform different 
	     CREAM operations (JobRegister, JobStart, JobCancel, JobStatus, etc.).\n
	     
	     \param serviceURL The service's URL to contact to perform a CREAM operation
	     \throw glite::ce::cream_client_api::cream_exceptions::BaseException
	     \throw glite::ce::cream_client_api::cream_exceptions::InvalidArgumentException
	     \throw glite::ce::cream_client_api::cream_exceptions::GridProxyDelegationException
	     \throw glite::ce::cream_client_api::cream_exceptions::JobSubmissionDisabledException
	     \throw glite::ce::cream_client_api::cream_exceptions::JobStatusInvalidException
	     \throw glite::ce::cream_client_api::cream_exceptions::JobUnknownException
	     \throw glite::ce::cream_client_api::cream_exceptions::GenericException
	     \throw glite::ce::cream_client_api::cream_exceptions::AuthorizationException
	     \throw glite::ce::cream_client_api::cream_exceptions::DelegationException
	     \throw glite::ce::cream_client_api::cream_exceptions::InternalException
	     \throw glite::ce::cream_client_api::cream_exceptions::ConnectionTimeoutException
	     \throw glite::ce::cream_client_api::soap_proxy::auth_ex
	     \throw glite::ce::cream_client_api::soap_proxy::soap_ex
	     \throw glite::ce::cream_client_api::soap_proxy::soap_runtime_ex
	  */
	  virtual void execute(const std::string& serviceURL, const bool ignore_tag_mismatch = false) 
	    throw(BaseException&,
		  InvalidArgumentException&,
		  GridProxyDelegationException&,
		  JobSubmissionDisabledException&,
		  JobStatusInvalidException&,
		  JobUnknownException&,
		  GenericException&,
		  AuthorizationException&,
		  DelegationException&,
		  InternalException&,
		  ConnectionTimeoutException&,
		  auth_ex&,
		  soap_ex&,
		  soap_runtime_ex&) = 0;

	  /**
	     Before to invoke the execute() method, the user MUST set the proxy file containing
	     the user's credentials. If the proxy file is invalid, unreadable, corrupted, expired
	     an exception auth_ex is raised. auth_ex inherits from std::exception so the what() method
	     returns a string containing the failure reason in a human readable form.
	     \see execute
	     \param certificate_file containing the user's certificate const std::string&
	     \param key_file containing the user's key std::string&
	     \throw glite::ce::cream_client_api::soap_proxy::auth_ex
	  */
	  void setCredential( const std::string& certificate_file, const std::string& key_file = "" ) throw( auth_ex& );

	  /**
	     Before to invoke the execute() method, the user CAN set the connection timeout in order to avoid
	     connections that stuck waiting for too long an answer from the service. 
	     A value for this timeout is already set by the CreamProxyFactory's factory methods when a AbsCreamProxy's subclass is created;
	     after factory's method invocation, this method can be used to refine the timeout if needed.

	     \param connection_timeout int That specifies the amount of timeout in seconds
	  */
	  void setConnectionTimeout( const int connection_timeout) throw();

	  /**
	     This method must be ignored, it is conceived only for the ICE component
	   */
	  void setSoapHeader( const std::string& sh ) throw() { m_use_soap_header=1; m_soap_header=sh; }

	protected:

	  friend class initSoap;

	  void          makeSoap( void ) throw(soap_ex&, auth_ex&, soap_runtime_ex&);
	  void          clearSoap( void );			     

	  struct soap* m_soap;
	  log4cpp::Category *m_log_dev;
	  std::string m_certfile;
	  std::string m_keyfile;
	  
	  AbsCreamProxy( const int nbio ) throw();// : m_nbio( nbio ) { };
	  
	};
  
	class initSoap {
	  
	  AbsCreamProxy* m_theProxy;
	  
	public:
	  initSoap(AbsCreamProxy* p) throw(auth_ex&, soap_ex&, soap_runtime_ex&);
	  ~initSoap() throw();
	};

      }
    }
  }
}

#endif
