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

#include "glite/ce/cream-client-api-c/VOMSWrapper.h"
#include "glite/ce/cream-client-api-c/certUtil.h"
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <openssl/pem.h>
#include <cerrno>
#include "glite/ce/cream-client-api-c/creamApiLogger.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <boost/shared_ptr.hpp>

#include <ctime>

extern int daylight;
extern long timezone;

using namespace glite::ce::cream_client_api::soap_proxy;
using namespace std;

boost::recursive_mutex VOMSWrapper::s_mutex;

//______________________________________________________________________________
VOMSWrapper::VOMSWrapper( const std::string& pxfile, const bool verify_ac_sign ) 
  throw() : m_pxfile ( pxfile )
{
  boost::recursive_mutex::scoped_lock M( s_mutex );

  m_isValid = false;

  struct stat sbuf;

  int res_stat = stat( pxfile.c_str(), &sbuf);

  if(res_stat) {
    m_errorMessage = "Unable to open the file [";
    m_errorMessage += pxfile + "] for stat: " + strerror( errno );
    m_errorNum = FILE_NOT_FOUND;
    return;
  }
 
  if(sbuf.st_uid != ::getuid( ) ) {
     m_errorMessage = "The owner of the file [";
     m_errorMessage += pxfile + "] is not you!";
     m_errorNum = FILE_NOT_FOUND;
     return;
  }	
 
  FILE* certIN;

  int saveerr;
  int retry = 0;
  while( true ) {

    certIN = fopen( pxfile.c_str(), "r" );
    
    if( !certIN ) {

      if( retry<3) {

	sleep(1);
	retry++;
	continue;

      } else {
	
	saveerr = errno;
	m_errorMessage = "Unable to open the file [";
	m_errorMessage += pxfile + "]: " + strerror( saveerr );
	m_errorNum = FILE_NOT_FOUND;
	return;
      }

    } else { // certIN is not NULL; so exit from while(true)

      break;

    }
  }
  
  boost::shared_ptr<std::FILE> tmpIn(certIN, std::fclose);
  


  // do not set yet m_isValid to true because
  // we must before check the validity
  // of internal attribute certificate

  
  // VOMS API do not accept an expired proxy
  
  int res = m_V.Retrieve( certIN, RECURSE_CHAIN );

  bool second_check = false;

  if(res) {
    m_isValid = true;
  } else {

    if( m_V.error == VERR_PARAM || 
        m_V.error == VERR_IDCHECK ||
        m_V.error == VERR_FORMAT )
      {
	m_isValid = false;
	m_errorMessage = "Proxy file contains and invalid certificate: ";
	m_errorMessage += m_V.ErrorMessage();
	m_errorNum = VALIDITY_ERROR;
	return;
      } else {
      second_check = true;
    }
    
    m_V.SetVerificationType( (verify_type)(VERIFY_NONE) );
    rewind( certIN );
    res = m_V.Retrieve( certIN, RECURSE_CHAIN );
    
    /**
       let's ignore the missing voms cert installed on the system (if requested by the caller)
    */

    if(!res) {
      
      m_errorMessage = "Error in certificate: [";
      m_errorMessage += m_V.ErrorMessage() + "]";
      
      return;
      
    }

    if( verify_ac_sign ) { // NOT IGNORE missing AC signs
        m_errorMessage = "WARNING: The VOMS attribute could not be verified. Possibly, the VOMS server certificate is not installed.";      
      //return;
        m_isValid = false;
    } else m_isValid = true;
    
  }

  try {
    this->timeEnd();
  }catch(exception& ex) {
    m_errorMessage = ex.what();
    m_errorNum = VALIDITY_ERROR;
    m_isValid = false;
    return;
  }
  
  if( this->getProxyTimeEnd() <= time(NULL) ) {
    m_errorNum = EXPIRED_PROXY;
    m_errorMessage = "The proxy has EXPIRED!";
    m_isValid = false;
    return;
  }

}

//______________________________________________________________________________
string VOMSWrapper::getVOName( void ) const 
{ 
  if( m_V.data.begin() != m_V.data.end() )
    return m_V.data.begin()->voname; 
  else return "";
}

//______________________________________________________________________________
string VOMSWrapper::getIssuer( void ) const
{
  if( m_V.data.begin() != m_V.data.end() )
    return m_V.data.begin()->user; 
  else return "";
}

//______________________________________________________________________________
std::string VOMSWrapper::getDNFQAN( void ) const throw () {
  
  std::vector<std::string> fqans;
  std::string fqan = "";
  
  this->getFQANs( fqans );
  
  if( fqans.begin() != fqans.end( ) )
    fqan += *( fqans.begin() );
  
//   for(std::vector<std::string>::const_iterator it=fqans.begin(); it!=fqans.end(); ++it)
//     {
//       fqan += *it;    
//     }
  
  return this->getSubject( ) 
    + "-" 
    + fqan; // both methods can raise an auth_ex exception
  
}

//______________________________________________________________________________
void VOMSWrapper::timeEnd( void ) throw(auth_ex&) 
{
  
  X509 *x;
  x = VOMSWrapper::read_BIO( ); // can raise an auth_ex
  VOMSWrapper::helper_X509new X(x);
  
  voms v = *m_V.data.begin();

  ASN1_TIME *after  = certUtil::convtime(v.date2);
  
  //m_cert_time_end = certUtil::ASN1_UTCTIME_get( X509_get_notAfter(x) ) ;
  m_cert_time_end = certUtil::ASN1_UTCTIME_get( X509_get_notAfter(x) ) ;
  m_ca_time_end   = certUtil::stillvalid(after);
 
  ASN1_TIME_free( after )
 
  m_proxyTimeEnd = (m_cert_time_end > m_ca_time_end ? m_ca_time_end : m_cert_time_end);

}

//______________________________________________________________________________
X509* VOMSWrapper::read_BIO( void ) 
  throw(auth_ex&)
{
  BIO *in = NULL;
  in = BIO_new(BIO_s_file());
  VOMSWrapper::helper_BIOnew h( in ); // smart container to 
                                      // free 'in' when leaving this scope
  if (in) {
    if (BIO_read_filename( in, m_pxfile.c_str() ) > 0) {
        
      X509* x = PEM_read_bio_X509(in, NULL, 0, NULL);
      if(!x) {
        throw  auth_ex(std::string("PEM_read_bio_X509 failed while reading X509 proxy file: ")+ m_pxfile)
;
      }
      
      return x;

    } else {
      throw  auth_ex(std::string("VOMSWrapper::read_BIO() - BIO_read_filename failed while reading X509 proxy file: ")+ m_pxfile);
    }
  } else {
    throw  auth_ex(std::string("VOMSWrapper::read_BIO() - unable to allocate memory when creatin a BIO object with BIO_new() call, for the proxy file: ")+ m_pxfile);
  }
}
