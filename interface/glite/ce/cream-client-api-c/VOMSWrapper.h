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

#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_VOMSWRAPPER_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_VOMSWRAPPER_

#include "glite/ce/cream-client-api-c/creamApiLogger.h"
#include "glite/ce/cream-client-api-c/auth_ex.h"
#include "voms/voms_api.h"
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
//#include <cerrno>
#include <ctime>
#include "boost/thread/recursive_mutex.hpp"

//extern int errno;

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {


	/// Certificate/Proxy-related utility class
	/**
	   This class provides methods to get easy access to a proxy certificate, its time 
	   validity, data integrity, and stored information
	*/
	class VOMSWrapper {
	  
	  class helper_BIOnew {
	    BIO *in;
	  public:
	    helper_BIOnew(BIO* infile) : in(infile) {}
	    ~helper_BIOnew() {
	      if(in) {
		BIO_set_close(in, BIO_CLOSE);
		//BIO_close(in);
		BIO_free(in);
	      }
	    }
	  };
	  
	  class helper_X509new {
	    X509* x;
	  public:
	    helper_X509new(X509* xin) : x(xin) {}
	    ~helper_X509new() { if(x) X509_free(x); }
	  };
	  

	  VOMSWrapper( const VOMSWrapper& ) {}

	  static boost::recursive_mutex s_mutex;
	  
	  vomsdata m_V;
	  bool m_isValid;
	  std::string m_errorMessage;
	  int m_errorNum;

	  time_t m_proxyTimeEnd, m_ca_time_end, m_cert_time_end;

	  std::string m_pxfile;
	  
	  void getFQANs( std::vector<std::string>& fqans ) const throw()
	  {
	    if(m_isValid)
	      fqans = m_V.data.begin()->fqan;
	  }

	  X509* read_BIO( void ) throw( auth_ex& ); 

	  void timeEnd( void ) throw( auth_ex& );

	public:
	  
	  /**
	     Enumeration of the three possible non-validity reasons of the proxy
	  */
	  enum {
	    VALIDITY_ERROR,/**< The content of the proxy file is not valid (corrupted, or not recognized)  */
	    FILE_NOT_FOUND,/**< The proxy file is not present on disk or is not accessibile (permission denied) */
	    EXPIRED_PROXY/**< The proxy has expired, not valid anymore */
	  };

	  //____________________________________________________________________
	  /**
	     Creates an object of the class VOMSWrapper from a proxy file

	     \param pxfile The complete (and absolute) path of the proxy file
	     \param verify_ac_sign (Available from TAG R_1_11_1_0) If 'false' disable the verification of the VO voms
                             server certificate ( so this is needed when the VOMS server certificate is not installed). Default is 'true' (does the verification).
	  */
	  VOMSWrapper( const std::string& pxfile, const bool verify_ac_sign = true ) throw();

	  //____________________________________________________________________
	  /**
	     Class destructor
	  */
	  virtual      ~VOMSWrapper() throw() {}
	  
	  //____________________________________________________________________
	  /**
	     Returns yes if the proxy is valid, false otherwise. If the proxy is not valid
	     the user should check the return of the getErrorNum() and getErrorMessage() in order
	     to know the reason why the proxy is not valid.
	     
	     \return bool
	  */
	  bool         IsValid( void ) const { return m_isValid ; }

	  //____________________________________________________________________
	  /**
	     If the proxy is valid returns the name of the VO the owner of the proxy belongs to, an empty string otherwise

	     \return std::string
	  */
	  std::string  getVOName( void ) const;

	  //____________________________________________________________________
	  /**
	     If the proxy is valid returns the identity of who signed the proxy, an empty string otherwise
	     
	     \return std::string
	  */
	  std::string  getIssuer( void ) const;

	  //____________________________________________________________________
	  /**
	     DEPRECATED If the proxy is valid returns the identity of the owner of the proxy certificate, an empty string otherwise
	  */
	  std::string  getDN( void ) const {
	    return getIssuer();
	  }

	  //____________________________________________________________________
	  /**
	     If the proxy is valid returns the subject of the proxy certificate, an empty string otherwise

	     \return std::string
	  */
	  std::string  getSubject( void ) const {
	    return getIssuer();
	  }

	  //____________________________________________________________________
	  /**
	     If the proxy is valid returns the identity of the owner of the proxy certificate, an empty string otherwise

	     \return std::string
	  */
	  std::string  getDNFQAN( void ) const throw();
	  
	  /**
	     If the proxy is valid returns  the human readable reason of the invalid proxy, an empty string otherwise
	     
	     \return std::string
	  */
	  std::string  getErrorMessage( void ) const { return m_errorMessage; }

	  /**
	     If IsValid() returned true, this method returns the error code of the reason of invalid proxy (must be matched
	     against VOMSWrapper::VALIDITY_ERROR, VOMSWrapper::FILE_NOT_FOUND, VOMSWrapper::EXPIRED_PROXY
	     
	     \return int
	  */
	  int          getErrorNum( void ) const { return m_errorNum ; }

	  /**
	     If the proxy is valid returns the time (UTC, seconds since the 'epoch') of the proxy validity expiration, 0 otherwise
		
	     \return time_t
	  */
	  time_t       getProxyTimeEnd( void ) const throw() 
	    {return m_proxyTimeEnd;}

          time_t       getCATimeEnd( void ) const throw()
          { return m_ca_time_end; }

          time_t       getCertTimeEnd( void ) const throw()
          { return m_cert_time_end; }

	};
	
      }
    }
  }
}

#endif
