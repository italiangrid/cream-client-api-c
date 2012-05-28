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
#include "glite/ce/cream-client-api-c/JobStatusWrapper.h"
#include "glite/ce/cream-client-api-c/JobFilterWrapper.h"

#include <boost/tuple/tuple.hpp>

using namespace glite::ce::cream_client_api::soap_proxy;
using namespace std;

//__________________________________________________________________________________
void processorStatusResult::operator()( const CREAMTYPES__JobStatusResult* jr ) 
{
  
  if(!jr) 
    {
      throw InternalException("processorStatusResult::operator() - Pointer CREAMTYPES__JobStatusResult is NULL! Probable de-serialization error");
    }
  
  
  if(!jr->jobDescriptionId)
    {
      throw InternalException("processorStatusResult::operator() - Pointer CREAMTYPES__JobStatusResult->jobDescriptionId is NULL! Probable de-serialization error");
    }
  
  string errMex;
  
  switch( jr->__union_JobStatusResult) {
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobStatusResult_CREAMTYPES__JobUnknownFault:
    if( jr->union_JobStatusResult.CREAMTYPES__JobUnknownFault )
      errMex = ExceptionFactory::makeStringFromFault( jr->union_JobStatusResult.CREAMTYPES__JobUnknownFault );
    else
      errMex = "Error Message Not Available";
    
    (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobStatusWrapper::JOBUNKNOWN, JobStatusWrapper( ), errMex );
    
    break;
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobStatusResult_CREAMTYPES__JobStatusInvalidFault:
    if( jr->union_JobStatusResult.CREAMTYPES__JobStatusInvalidFault )
      errMex = ExceptionFactory::makeStringFromFault( jr->union_JobStatusResult.CREAMTYPES__JobStatusInvalidFault);
    else
      errMex = "Error Message Not Available";
    
    (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobStatusWrapper::JOBSTATUSINVALID, JobStatusWrapper( ), errMex );
    
    break; 
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobStatusResult_CREAMTYPES__DelegationIdMismatchFault:
    if( jr->union_JobStatusResult.CREAMTYPES__DelegationIdMismatchFault )
      errMex = ExceptionFactory::makeStringFromFault( jr->union_JobStatusResult.CREAMTYPES__DelegationIdMismatchFault);
    else
      errMex = "Error Message Not Available";
    
    (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobStatusWrapper::DELEGATIONIDMISMATCH, JobStatusWrapper( ), errMex );
    
    break; 
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobStatusResult_CREAMTYPES__DateMismatchFault:
    if( jr->union_JobStatusResult.CREAMTYPES__DateMismatchFault )
      errMex = ExceptionFactory::makeStringFromFault( jr->union_JobStatusResult.CREAMTYPES__DateMismatchFault);
    else
      errMex = "Error Message Not Available";
    
    (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobStatusWrapper::DATEMISMATCH, JobStatusWrapper( ), errMex );
    
    break; 
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobStatusResult_CREAMTYPES__GenericFault:
    if( jr->union_JobStatusResult.CREAMTYPES__GenericFault)
      errMex = ExceptionFactory::makeStringFromFault( jr->union_JobStatusResult.CREAMTYPES__GenericFault);
    else
      errMex = "Error Message Not Available";
    
    (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobStatusWrapper::GENERIC, JobStatusWrapper( ), errMex );
    
    break;
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobStatusResult_CREAMTYPES__LeaseIdMismatchFault:
    if( jr->union_JobStatusResult.CREAMTYPES__LeaseIdMismatchFault )
      errMex = ExceptionFactory::makeStringFromFault( jr->union_JobStatusResult.CREAMTYPES__LeaseIdMismatchFault);
    else
      errMex = "Error Message Not Available";
    
    (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobStatusWrapper::LEASEIDMISMATCH, JobStatusWrapper( ), errMex );
    
    break;
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobStatusResult_jobStatus:
    if( jr->union_JobStatusResult.jobStatus )
      (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobStatusWrapper::OK, JobStatusWrapper( jr->union_JobStatusResult.jobStatus ), "" );
    
    break;
    
  } // switch
  
} // void operator()
  
//______________________________________________________________________________
CreamProxy_Status::CreamProxy_Status(  const JobFilterWrapper* filter, 
				       StatusArrayResult* target,
				       const int timeout ) throw()
  : AbsCreamProxy( timeout ), m_jobFilter( filter ), m_target( target )
{
}

//______________________________________________________________________________
void CreamProxy_Status::execute( const string& serviceAddress, const bool ignore_tag_mismatch ) throw(BaseException&,
								      InvalidArgumentException&,
								      GridProxyDelegationException&,
								      JobSubmissionDisabledException&,
								      GenericException&,
								      // AuthenticationException&,
								      AuthorizationException&,
								      DelegationException&,
								      InternalException&,
								      ConnectionTimeoutException&,
								      auth_ex&,
								      soap_ex&,
								      soap_runtime_ex&)
{
  initSoap init(this);
  
#ifdef DOPROFILE
  apiUtil::scoped_timer T("CreamProxy_Status::execute-soap_call___CREAM__JobStatus");
#endif  
  
  _CREAMTYPES__JobStatusResponse resp;
  
  //cout << "CreamProxy_Status::execute() - Calling soap_call___CREAM__JobStatus to ["<<serviceAddress<<"]"<<endl;
  
  
  if(SOAP_OK != soap_call___CREAM__JobStatus(m_soap,
					     serviceAddress.c_str(),
					     NULL,    // soapAction
					     (CREAMTYPES__JobFilter*)m_jobFilter, 
					     &resp))
    {
      ExceptionFactory::raiseException(m_soap, ignore_tag_mismatch);
      
    } else {
    
    m_target->clear();
    processorStatusResult _processorResult(m_target);
    
    for_each( resp.result.begin(), resp.result.end(), _processorResult);
    
  }
}
