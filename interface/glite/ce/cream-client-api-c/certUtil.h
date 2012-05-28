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

#ifndef _GLITE_CE_CREAM_CLIENT_API_UTIL_CERTUTIL_H_
#define _GLITE_CE_CREAM_CLIENT_API_UTIL_CERTUTIL_H_
 
#include "glite/ce/cream-client-api-c/auth_ex.h"
#include <string>
#include "voms/voms_api.h"
#include <openssl/pem.h>

namespace glite {
namespace ce {
namespace cream_client_api {

   class helper_BIOnew { 
     BIO *in; 
   public: 
     helper_BIOnew(BIO* infile) : in(infile) {} 
     ~helper_BIOnew() {  
       if(in) { 
 	BIO_set_close(in, BIO_CLOSE);     
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
  
   class helper_skX509new { 
     STACK_OF(X509) *sk; 
   public: 
     helper_skX509new(STACK_OF(X509)* x) : sk(x) {} 
     ~helper_skX509new() { 
       if( sk ) { 
 	sk_X509_pop_free( sk, X509_free ); 
       } 
     } 
   }; 

  namespace certUtil {

    ASN1_TIME *convtime(const std::string& data);
    time_t stillvalid(ASN1_TIME *ctm);
    
    X509* read_BIO( const std::string& pxfile )  
      throw( glite::ce::cream_client_api::soap_proxy::auth_ex& ); 

      std::string getDN(const std::string& proxyfile) 
       throw(glite::ce::cream_client_api::soap_proxy::auth_ex&);

/*     std::string getDNFQAN(const std::string& proxyfile) */
/*       throw(glite::ce::cream_client_api::soap_proxy::auth_ex&); */
    

/*     std::string getCertIssuer(const std::string& proxyfile) */
/*       throw(glite::ce::cream_client_api::soap_proxy::auth_ex&); */
        

     std::string getCertSubj(const std::string& proxyfile) 
       throw(glite::ce::cream_client_api::soap_proxy::auth_ex&); 
            

/*     std::string getVOName( const std::string& proxyfile) */
/*       throw(glite::ce::cream_client_api::soap_proxy::auth_ex&); */
    

     const long int getProxyTimeLeft( const std::string& proxyfile )
       throw (glite::ce::cream_client_api::soap_proxy::auth_ex&);
    
 
/*     X509* getX509Fromfile(const std::string& proxyfile) */
/*       throw(glite::ce::cream_client_api::soap_proxy::auth_ex&); */
    

/*     STACK_OF(X509) *load_chain(char *certfile) throw(); */
    
/*     void getFQANs( const std::string&, std::vector<std::string>& ) */
/*       throw(glite::ce::cream_client_api::soap_proxy::auth_ex&); */

    void generateUniqueID(std::string& target) throw();
    
    void bintostring( unsigned char* buf, size_t len, std::string& );
    
    int GRSTx509MakeProxyCert_local(char **proxychain, FILE *debugfp, 
                                    char *reqtxt, char *cert, char *key, int minutes);

    time_t ASN1_UTCTIME_get(const ASN1_UTCTIME*);

  };
  
 }
 }
}

#endif
