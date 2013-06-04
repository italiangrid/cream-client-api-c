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
#include "glite/ce/cream-client-api-c/JobDescriptionWrapper.h"
#include "glite/ce/cream-client-api-c/JobIdWrapper.h"

#include <map>
#include <utility>
#include <ctime>
#include <iostream>

using namespace std;
using namespace glite::ce::cream_client_api::soap_proxy;

#ifdef SL6
  #define UNION_JOBREGISTERRESULT_DELEGATIONPROXY 	SOAP_UNION__CREAMTYPES__union_JobRegisterResult_DelegationProxyFault
  #define UNION_JOBREGISTERRESULT_DELEGATIONIDMISMATCH  SOAP_UNION__CREAMTYPES__union_JobRegisterResult_DelegationIdMismatchFault
  #define UNION_JOBREGISTERRESULT_LEASEIDMISMATCH	SOAP_UNION__CREAMTYPES__union_JobRegisterResult_LeaseIdMismatchFault
  #define UNION_JOBREGISTERRESULT_GENERIC		SOAP_UNION__CREAMTYPES__union_JobRegisterResult_GenericFault

  #define DELEGATIONIDMISMATCH_FAULT			DelegationProxyFault
  #define LEASEIDMISMATCH_FAULT				LeaseIdMismatchFault
  #define DELEGATIONPROXY_FAULT				DelegationProxyFault
  #define GENERIC_FAULT					GenericFault
#else
  #define UNION_JOBREGISTERRESULT_DELEGATIONPROXY       SOAP_UNION__CREAMTYPES__union_JobRegisterResult_CREAMTYPES__DelegationProxyFault
  #define UNION_JOBREGISTERRESULT_DELEGATIONIDMISMATCH  SOAP_UNION__CREAMTYPES__union_JobRegisterResult_CREAMTYPES__DelegationIdMismatchFault
  #define UNION_JOBREGISTERRESULT_LEASEIDMISMATCH       SOAP_UNION__CREAMTYPES__union_JobRegisterResult_CREAMTYPES__LeaseIdMismatchFault
  #define UNION_JOBREGISTERRESULT_GENERIC               SOAP_UNION__CREAMTYPES__union_JobRegisterResult_CREAMTYPES__GenericFault

  #define DELEGATIONIDMISMATCH_FAULT			CREAMTYPES__DelegationProxyFault
  #define LEASEIDMISMATCH_FAULT				CREAMTYPES__LeaseIdMismatchFault
  #define DELEGATIONPROXY_FAULT				CREAMTYPES__DelegationProxyFault
  #define GENERIC_FAULT					CREAMTYPES__GenericFault
#endif

//__________________________________________________________________________________
void processorRegisterResult::operator()( const CREAMTYPES__JobRegisterResult* jr ) 
{
  if(!jr) 
    {
      throw InternalException("processorRegisterResult::operator() - Pointer CREAMTYPES__JobRegisterResult is NULL! Probable de-serialization error");
    }
  
  if(!jr->jobDescriptionId) 
    {
      throw InternalException("processorRegisterResult::operator() - Pointer CREAMTYPES__JobRegisterResult->jobDescriptionId is NULL! Probable de-serialization error");
    }
  
  switch(jr->__union_JobRegisterResult) {
    
  case SOAP_UNION__CREAMTYPES__union_JobRegisterResult_jobId:
    (*m_target)[*jr->jobDescriptionId] = boost::make_tuple(JobIdWrapper::OK, JobIdWrapper(jr->union_JobRegisterResult.jobId ), "");
    break;      
    
  case UNION_JOBREGISTERRESULT_DELEGATIONPROXY:
    if(jr->union_JobRegisterResult.DELEGATIONPROXY_FAULT) {
      string errMex = ExceptionFactory::makeStringFromFault( jr->union_JobRegisterResult.DELEGATIONPROXY_FAULT);
      (*m_target)[*jr->jobDescriptionId] = boost::make_tuple( JobIdWrapper::DELEGATIONPROXYERROR, JobIdWrapper( "", "", vector<JobPropertyWrapper>()), errMex );
    }
    break;
    
  case UNION_JOBREGISTERRESULT_DELEGATIONIDMISMATCH:
    if(jr->union_JobRegisterResult.DELEGATIONIDMISMATCH_FAULT) {
      string errMex = ExceptionFactory::makeStringFromFault( jr->union_JobRegisterResult.DELEGATIONIDMISMATCH_FAULT );
      (*m_target)[*jr->jobDescriptionId] = boost::make_tuple( JobIdWrapper::DELEGATIONIDMISMATCH, JobIdWrapper( "", "", vector<JobPropertyWrapper>()), errMex );
    }
    break;
    
    
  case UNION_JOBREGISTERRESULT_LEASEIDMISMATCH:
    if(jr->union_JobRegisterResult.LEASEIDMISMATCH_FAULT) {
      string errMex = ExceptionFactory::makeStringFromFault( jr->union_JobRegisterResult.LEASEIDMISMATCH_FAULT );
      (*m_target)[*jr->jobDescriptionId] = boost::make_tuple( JobIdWrapper::LEASEIDMISMATCH, JobIdWrapper( "", "", vector<JobPropertyWrapper>()), errMex );
    }
    break;  
    
  case UNION_JOBREGISTERRESULT_GENERIC:
    if( jr->union_JobRegisterResult.GENERIC_FAULT ) {
      string errMex = ExceptionFactory::makeStringFromFault( jr->union_JobRegisterResult.GENERIC_FAULT);
      (*m_target)[*jr->jobDescriptionId] = boost::make_tuple( JobIdWrapper::GENERIC, JobIdWrapper( "", "", vector<JobPropertyWrapper>()), errMex );
    }
    break;  
    
  } 
  
}
  

//______________________________________________________________________________
CreamProxy_Register::CreamProxy_Register( const RegisterArrayRequest* jdlist,
					  RegisterArrayResult* target,
					  const int timeout ) throw() 
  : AbsCreamProxy( timeout ), m_jd_list( jdlist ), m_target( target )
{

	//cout << "\n*** CreamProxy_Register::CTOR" << endl;

}

//______________________________________________________________________________
void CreamProxy_Register::execute(const string& serviceURL, const bool ignore_tag_mismatch) 
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

  if(m_jd_list->empty()) return;

  initSoap init(this);
  
  _CREAMTYPES__JobRegisterRequest REQ; // vector of pointer to CREAMTYPES__JobDescription
  
  list<JobDescriptionWrapper*>::const_iterator it;
  
  for( it = m_jd_list->begin(); it != m_jd_list->end(); ++it)
    {
      // *it is a pointer to a JobDescriptionWrapper
      REQ.jobDescriptionList.push_back( *it );
    }
  
  _CREAMTYPES__JobRegisterResponse RESP;
#ifdef DOPROFILE
  apiUtil::scoped_timer T("CreamProxy_Register::execute-soap_call___CREAM__JobRegister");
#endif  

  //cout << "CreamProxy_Register: Invoking remote call" << endl;

  if(SOAP_OK != soap_call___CREAM__JobRegister(m_soap,
					       serviceURL.c_str(),
					       NULL,
					       &REQ,
					       &RESP))
    {
      
      ExceptionFactory::raiseException(m_soap, ignore_tag_mismatch);
      
    } else {
    
    //m_target->clear();
    processorRegisterResult _processorResult(m_target);
    
    for_each( RESP.result.begin(), RESP.result.end(), _processorResult);
    
  }
}
