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

#include "CREAM_CLIENTH.h"
#include "CREAM_CLIENTStub.h"

#include "glite/ce/cream-client-api-c/CreamProxy_Impl.h"
#include "glite/ce/cream-client-api-c/VOMSWrapper.h"
#include "glite/ce/cream-client-api-c/certUtil.h"
#include "glite/ce/cream-client-api-c/creamApiLogger.h"

#include <ctime>

using namespace std;
using namespace glite::ce::cream_client_api::soap_proxy;

//______________________________________________________________________________
CreamProxy_ProxyRenew::CreamProxy_ProxyRenew( const string& delegID, /*string* S_certtxt,*/ const int timeout ) throw() 
 : AbsCreamProxy( timeout ), m_delegation_ID( delegID )//, m_certtxt( S_certtxt )
{
  //m_delegation_ID = "";
  //m_certtxt = NULL;
}

//______________________________________________________________________________
void CreamProxy_ProxyRenew::execute(const string& serviceURL, const bool ignore_tag_mismatch) 
  throw(BaseException&,
	InvalidArgumentException&,
	GridProxyDelegationException&,
	JobSubmissionDisabledException&,
	GenericException&,
	//	AuthenticationException&,
	AuthorizationException&,
	DelegationException&,
	InternalException&,
	ConnectionTimeoutException&,
	auth_ex&,
	soap_ex&,
	soap_runtime_ex&)
{
   char *certtxt;
/*   
   CREAM_SAFE_LOG(*m_log_dev << log4cpp::Priority::INFO
                  << "CreamProxy_DelegateRenew::execute() - Calling "
		  << "renewProxyReq to remote service ["
                  << serviceURL << "]" ); */

    {
      initSoap init(this);

      delegation2__renewProxyReqResponse proxyReqResp;
      {
#ifdef DOPROFILE
        apiUtil::scoped_timer T("CreamProxy_DelegateRenew::execute()-soap_call_delegation2__renewProxyReq");
#endif
        if(SOAP_OK != soap_call_delegation2__renewProxyReq(m_soap,
							   serviceURL.c_str(),
							   NULL,    // soapAction
							   m_delegation_ID,
							   proxyReqResp))
          ExceptionFactory::raiseException(m_soap, ignore_tag_mismatch); 
      }
    
      CREAM_SAFE_LOG(*m_log_dev << log4cpp::Priority::INFO
                     << "CreamProxy_DelegateRenew::execute() - "
	             << "Signing returned proxy with our proxy certificate ["
                     << m_certfile<< "]..." );

       VOMSWrapper V( m_certfile, false );
       if( !V.IsValid( ) ) {
//	 if(V.getErrorNum() == VOMSWrapper::FILE_NOT_FOUND) {
	   string errmex = "CreamProxy_DelegateRenew::execute() - Coundl't open proxyfile [";
	   errmex += m_certfile+ "]: " + V.getErrorMessage();
	   throw auth_ex( errmex );
       }
       time_t timeleft = V.getProxyTimeEnd() - time(NULL);

      if (certUtil::GRSTx509MakeProxyCert_local(&certtxt,
						stderr,
						(char*)proxyReqResp._renewProxyReqReturn.c_str(),
						(char*)m_certfile.c_str(),
						(char*)m_certfile.c_str(),
						timeleft/60))
        throw DelegationException("Delegation proxy make failed: GRSTx509MakeProxyCert returned error") ;
    } // calls the initSoap's dtor that clears the SOAP runtime
    
//    *m_certtxt = string(certtxt);
    
    string certtxt_str( certtxt );
    free(certtxt);
    
    CREAM_SAFE_LOG(*m_log_dev<< log4cpp::Priority::INFO  
    		   << "CreamProxy_Delegate::execute() - "
		   << "Sending signed proxy to ["
             	   << serviceURL << "] with id ["<<m_delegation_ID<<"]"
		   );
    {
      initSoap init(this);
      delegation2__putProxyResponse response;

#ifdef DOPROFILE
      apiUtil::scoped_timer T("CreamProxy_DelegateRenew::execute()-soap_call_delegation2__putProxy");
#endif    
  
      if(SOAP_OK != soap_call_delegation2__putProxy(m_soap,
                                     		    serviceURL.c_str(),
                                     		    NULL,    // soapAction
                                     		    m_delegation_ID,
						    certtxt_str,
						    response))
        ExceptionFactory::raiseException(m_soap, ignore_tag_mismatch);
    }
}
