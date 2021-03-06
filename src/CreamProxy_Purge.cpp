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
#include "glite/ce/cream-client-api-c/JobInfoWrapper.h"
#include "glite/ce/cream-client-api-c/ResultWrapper.h"

using namespace glite::ce::cream_client_api::soap_proxy;
using namespace std;

//______________________________________________________________________________
CreamProxy_Purge::CreamProxy_Purge( const JobFilterWrapper* filter, ResultWrapper* target, const int timeout ) throw()
  : AbsCreamProxy( timeout ), m_jobFilter( filter ), m_result( target )
{
}

//______________________________________________________________________________
void CreamProxy_Purge::execute( const string& serviceAddress, const bool ignore_tag_mismatch ) 
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
  CREAMTYPES__CommandResult tmp;

#ifdef DOPROFILE
    apiUtil::scoped_timer T("CreamProxy_Purge::execute-soap_call___CREAM__JobPurge");
#endif  
    
    
    if(SOAP_OK != soap_call___CREAM__JobPurge(m_soap,
					      serviceAddress.c_str(),
					      NULL,    // soapAction
					      (CREAMTYPES__JobFilter*)m_jobFilter, 
					      &tmp))
      {
	ExceptionFactory::raiseException(m_soap, ignore_tag_mismatch);
      }

//   vector<CREAMTYPES__JobId*>::const_iterator it;
  
//   for( it = tmp.jobIdList.begin(); it != tmp.jobIdList.end(); ++it )
//     {
//       m_result->jobIdList.push_back( new JobIdWrapper( **it ) );
//     }
//   for( it = tmp.jobNotFoundIdList.begin(); it != tmp.jobNotFoundIdList.end(); ++it )
//     {
//       m_result->jobNotFoundIdList.push_back( new JobIdWrapper( **it ) );
//     }
//   for( it = tmp.jobStatusNotCompatibleIdList.begin(); it != tmp.jobStatusNotCompatibleIdList.end(); ++it )
//     {
//       m_result->jobStatusNotCompatibleIdList.push_back( new JobIdWrapper( **it ) );
//     }

  *(m_result) = tmp.result;

}
