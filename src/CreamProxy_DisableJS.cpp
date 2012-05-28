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
#include "glite/ce/cream-client-api-c/creamApiLogger.h"

using namespace glite::ce::cream_client_api::soap_proxy;
using namespace std;

//______________________________________________________________________________
void CreamProxy_DisableJS::execute( const std::string& serviceURL ) 
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
  initSoap init(this);
  
  __CREAM__DisableAcceptJobSubmissionsResponse resp;
#ifdef DOPROFILE
  apiUtil::scoped_timer T("CreamProxy_DisableJS::execute-soap_call___CREAM__DisableAcceptJobSubmissions");
#endif  
  if(SOAP_OK != soap_call___CREAM__DisableAcceptJobSubmissions(m_soap,
							     serviceURL.c_str(),
							     NULL,    // soapAction
							     resp))
    ExceptionFactory::raiseException(m_soap, ignore_tag_mismatch);
}
