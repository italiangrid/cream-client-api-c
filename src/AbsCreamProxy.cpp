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

/*
purify g++ -c -g -O0 -I../build/src/autogen -I../interface -I../../repository/externals/gsoap/2.7.6b/slc4_ia32_gcc346/include -I../../repository/externals/log4cpp/0.3.4b/slc4_ia32_gcc346/include -I../../repository/org.glite/org.glite.security.gsoap-plugin/1.5.2/slc4_ia32_gcc346/include -I../../repository/vdt/globus/4.0.3-VDT-1.6.0/slc4_ia32_gcc346/include/gcc32dbgpthr -I../../repository/org.glite/org.glite.security.voms/1.8.3/slc4_ia32_gcc346/include -I../../repository/org.glite/org.gridsite.core/1.1.18/slc4_ia32_gcc346/include -I ../../repository/externals/classads/0.9.8/slc4_ia32_gcc346/include -DWANT_NAMESPACES -UHAVE_CONFIG_H AbsCreamProxy.cpp CreamProxy_Register.cpp certUtil.cpp CEUrl.cpp ConfigurationManager.cpp creamApiLogger.cpp CreamProxy_Delegate.cpp CreamProxy_Info.cpp CreamProxy_Start.cpp ExceptionFactory.cpp JobCommandWrapper.cpp JobDescriptionWrapper.cpp JobFilterWrapper.cpp JobIdWrapper.cpp  JobInfoWrapper.cpp job_statuses.cpp JobStatusWrapper.cpp ResultWrapper.cpp scoped_timer.cpp VOMSWrapper.cpp CEUrl.cpp certUtil.cpp
*/

//#include "glite/ce/cream-client-api-c/certUtil.h"
#include "glite/ce/cream-client-api-c/AbsCreamProxy.h"
#include "glite/ce/cream-client-api-c/creamApiLogger.h"
#include "glite/ce/cream-client-api-c/scoped_timer.h"
#include "glite/ce/cream-client-api-c/JobDescriptionWrapper.h"
#include "glite/ce/cream-client-api-c/JobPropertyWrapper.h"
#include "glite/ce/cream-client-api-c/CREAM_CLIENT.nsmap"
#include "glite/ce/cream-client-api-c/VOMSWrapper.h"
#include "CREAM_CLIENTH.h"
#include "CREAM_CLIENTStub.h"

#include "log4cpp/Category.hh"

#include <boost/filesystem/operations.hpp>

#include <list>

using namespace std;
using namespace glite::ce::cream_client_api::soap_proxy;
namespace apiUtil = glite::ce::cream_client_api::util;

//______________________________________________________________________________
initSoap::~initSoap() throw()
{
  m_theProxy->clearSoap();
}

//______________________________________________________________________________
initSoap::initSoap( AbsCreamProxy* p )
  throw(auth_ex&, soap_ex&, soap_runtime_ex&)
{
  m_theProxy = p;
  m_theProxy->makeSoap();
}

//______________________________________________________________________________
AbsCreamProxy::AbsCreamProxy( const int nbio ) throw()
 : m_nbio( nbio ), 
   m_ctx(NULL), 
   m_use_soap_header(0),
   m_soap_header( "" ), 
   m_soap(NULL),
   m_log_dev(apiUtil::creamApiLogger::instance()->getLogger())
{ 
}


//______________________________________________________________________________
void AbsCreamProxy::setConnectionTimeout( const int timeout ) throw() 
{
  m_nbio = timeout;
}

//______________________________________________________________________________
AbsCreamProxy::~AbsCreamProxy( ) throw()
{
}

//______________________________________________________________________________
void AbsCreamProxy::setCredential( const string& certfile,
				   const string& keyfile) throw( auth_ex& )
{
#ifdef DOPROFILE
  apiUtil::scoped_timer T("CreamProxy::Authenticate");
#endif
  
  /**
   *
   * check for proxy validity
   *
   */
  if( certfile.empty() ) {

    CREAM_SAFE_LOG(m_log_dev->fatalStream()
		   << "CreamProxy::Authenticate() - trying to authenticate "
		   << "with an unknown certificate file."
		   << " Argument 'certfile' is an empty string."
		   );

    throw auth_ex("'certfile' argument is an empty string. Cannot set credentials");
  } 
  
  m_certfile = certfile;
  if(keyfile.empty()) m_keyfile = certfile;
  else m_keyfile = keyfile;
  
}

//______________________________________________________________________________
void AbsCreamProxy::makeSoap( void ) throw(soap_ex&, soap_runtime_ex&, auth_ex&)
{
#ifdef DOPROFILE
  apiUtil::scoped_timer TT("AbsCreamProxy::makeSoap");
#endif
 
  //cout << "\n*** AbsCreamProxy::makeSoap" << endl;
  try {
    m_soap = soap_new();
    
    if(!m_soap)
      throw soap_runtime_ex("SOAP run time initialization failed");

    m_soap->header = NULL;
    
    m_soap->socket_flags = MSG_NOSIGNAL; // this setting will NOT generate a sigpipe
    // but read/write operations return SOAP_EOF instead.
    
    soap_set_namespaces(m_soap, CREAM_CLIENT_namespaces);
    
    if( m_certfile.empty() ) {
      CREAM_SAFE_LOG(m_log_dev->fatalStream()
		     << "CreamProxy::Authenticate() - trying to authenticate "
		     << "with an unknown certificate file."
		     << " Argument 'certfile' is an empty string, Probably "
		     << "setCreadential() call hasn't been called"
		     );
      //     cerr <<"FATAL ERROR: trying to authenticate with an unknown "
      // 	 << "certificate file. Argument 'certfile' is an empty string. Stop"
      // 	 <<endl;
      
      string errMex = "CreamProxy::Authenticate() - trying to authenticate ";
      errMex += "with an unknown certificate file.";
      errMex += " Argument 'certfile' is an empty string, Probably ";
      errMex += "setCreadential() call hasn't been called";
      
      throw auth_ex( errMex );
      
    }
    
    if(!::getenv("CREAM_CLIENT_NO_AUTHN")) {
      if( m_ctx ) {
	glite_gsplugin_free_context( m_ctx );
	m_ctx = NULL;
      }
      
      if ( glite_gsplugin_init_context( &m_ctx ) ) {
	m_ctx = NULL;
	
	/**
	 *
	 * The m_soap will be freed by the clearSoap
	 * that is called by the CTOR of initSoap whose CTOR
	 * called this makeSaop API.
	 *
	 */
	throw auth_ex("gsplugin initialization failed");
      }
      
      
      if(!boost::filesystem::exists( boost::filesystem::path(m_certfile, boost::filesystem::native ) ) ) {
	glite_gsplugin_free_context( m_ctx );
	m_ctx = NULL;
	throw auth_ex("Missing certificate file [" + m_certfile + "]");
      }
	  
      if(!boost::filesystem::exists( boost::filesystem::path(m_keyfile, boost::filesystem::native ) ) ) {
	glite_gsplugin_free_context( m_ctx );
	m_ctx = NULL;
	throw auth_ex("Missing key file [" + m_keyfile + "]");
      }
      

      ::unsetenv("X509_USER_CERT");
      ::unsetenv("X509_USER_KEY");
      ::setenv("X509_USER_CERT", m_certfile.c_str(), 0);
      ::setenv("X509_USER_KEY", m_keyfile.c_str(), 0);
      if (glite_gsplugin_set_credential( m_ctx, m_certfile.c_str(), m_keyfile.c_str())) {
	//cerr << "Err desc: " << glite_gsplugin_errdesc( m_soap ) << endl;
	glite_gsplugin_free_context( m_ctx );
	m_ctx = NULL;
	throw auth_ex("Cannot set credentials in the gsoap-plugin context");
      }
      
      struct timeval T;
      T.tv_sec = (time_t)m_nbio;
      T.tv_usec = 0;
      
      glite_gsplugin_set_timeout( m_ctx, &T );
      
      if ( soap_register_plugin_arg( m_soap, glite_gsplugin, m_ctx ) ) {
	glite_gsplugin_free_context( m_ctx );
	m_ctx = NULL;
	/**
	 *
	 * The m_soap will be freed by the clearSoap
	 * that is called by the CTOR of initSoap whose CTOR
	 * called this makeSaop API.
	 *
	 */
	throw auth_ex("soap_register_plugin_arg FAILED");
      }
    }
    

    
    if( m_use_soap_header ) {
      /**
       * POSSIBLE MEM LEAK? When a response is received
       * it seems that the field SOAP->header is set to NULL by
       * the gSOAP runtime
       */
      m_soap->header = new SOAP_ENV__Header(); // FIXME how to free this (see comment above) ?
      m_soap->header->CREAMTYPES__iceId = new string( m_soap_header );
    }
  } catch(exception& ex) {

    this->clearSoap();// if an exception is thrown the initSoap object is not created
                      // This means that the DTOR (that cleans up the gSOAP runtime)
                      // wont be called. then we must call it explicitly

    throw;// ex;
  }
}

//______________________________________________________________________________
void AbsCreamProxy::clearSoap( void )
{
#ifdef DOPROFILE
  apiUtil::scoped_timer T("AbsCreamProxy::clearSoap");
#endif

  //cout << "\n*** AbsCreamProxy::clearSoap" << endl;


  if(m_soap) {
    soap_destroy(m_soap); // deletes deserialized class instances (for C++ only)
    soap_end(m_soap); // removes deserialized data and clean up
    soap_done(m_soap); // detach soap runtime
    
    
    if(!::getenv("CREAM_CLIENT_NO_AUTHN")) {
      if( m_ctx ) {
	glite_gsplugin_free_context( m_ctx );
	m_ctx = NULL;
      }
    }

    if(m_use_soap_header) { 
      if(m_soap->header) {
        if(m_soap->header->CREAMTYPES__iceId)
	  delete m_soap->header->CREAMTYPES__iceId;
	delete m_soap->header; 
	m_soap->header = NULL; 
      }
    }
    
    free(m_soap);
    m_soap = NULL;
  }
  
}
