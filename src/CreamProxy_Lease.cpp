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

using namespace std;
using namespace glite::ce::cream_client_api::soap_proxy;

//______________________________________________________________________________
CreamProxy_Lease::CreamProxy_Lease( const pair<string, time_t>& Lease, pair<string, time_t>* target, const int timeout ) throw()
  : AbsCreamProxy( timeout ), m_leaseID( Lease.first ), m_leaseTime( Lease.second ), m_resp_lease( target )
{  
}

//______________________________________________________________________________
void CreamProxy_Lease::execute(const string& serviceURL, const bool ignore_tag_mismatch)
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

  CREAMTYPES__Lease leaseReq, leaseResp;
  leaseReq.leaseId = m_leaseID;
  leaseReq.leaseTime = m_leaseTime;

#ifdef DOPROFILE
  apiUtil::scoped_timer T("CreamProxy_Lease::execute()-soap_call___CREAM__setLease");
#endif
  
  if(SOAP_OK != soap_call___CREAM__setLease(m_soap,
					    serviceURL.c_str(),
					    NULL,// soapAction
					    &leaseReq,
					    &leaseResp))
    {
      
      ExceptionFactory::raiseException(m_soap, ignore_tag_mismatch);
      
    } else {
    
    m_resp_lease->first  = leaseResp.leaseId;
    m_resp_lease->second = leaseResp.leaseTime;
    
  }
  
}
