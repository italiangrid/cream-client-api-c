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

using namespace glite::ce::cream_client_api::soap_proxy;
using namespace std;

//____________________________________________________________________________
void processorInfoResult::operator()( const CREAMTYPES__JobInfoResult* jr ) 
{
  if(!jr){
    throw InternalException("processorInfoResult::operator() - Pointer CREAMTYPES__JobInfoResult is NULL! Probable de-serialization error");
  }
  
  if(!jr->jobDescriptionId){
    throw InternalException("processorInfoResult::operator() - Pointer CREAMTYPES__JobInfoResult->jobDescriptionId is NULL! Probable de-serialization error");
  }
  
  string errMex;
  
  switch( jr->__union_JobInfoResult) {
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobInfoResult_CREAMTYPES__JobUnknownFault:
    if( jr->union_JobInfoResult.CREAMTYPES__JobUnknownFault )
      errMex = ExceptionFactory::makeStringFromFault( jr->union_JobInfoResult.CREAMTYPES__JobUnknownFault );
    else
      errMex = "Error Message Not Available";
    
    (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobInfoWrapper::JOBUNKNOWN, JobInfoWrapper( ), errMex );
    
    break;
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobInfoResult_CREAMTYPES__JobStatusInvalidFault:
    if( jr->union_JobInfoResult.CREAMTYPES__JobStatusInvalidFault )
      errMex = ExceptionFactory::makeStringFromFault( jr->union_JobInfoResult.CREAMTYPES__JobStatusInvalidFault);
    else
      errMex = "Error Message Not Available";
    
    (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobInfoWrapper::JOBSTATUSINVALID, JobInfoWrapper( ), errMex );
    
    break; 
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobInfoResult_CREAMTYPES__DelegationIdMismatchFault:
    if( jr->union_JobInfoResult.CREAMTYPES__DelegationIdMismatchFault )
      errMex = ExceptionFactory::makeStringFromFault( jr->union_JobInfoResult.CREAMTYPES__DelegationIdMismatchFault);
    else
      errMex = "Error Message Not Available";
    
    (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobInfoWrapper::DELEGATIONIDMISMATCH, JobInfoWrapper( ), errMex );
    
    break; 
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobInfoResult_CREAMTYPES__DateMismatchFault:
    if( jr->union_JobInfoResult.CREAMTYPES__DateMismatchFault )
      errMex = ExceptionFactory::makeStringFromFault( jr->union_JobInfoResult.CREAMTYPES__DateMismatchFault);
    else
      errMex = "Error Message Not Available";
    
    (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobInfoWrapper::DATEMISMATCH, JobInfoWrapper( ), errMex );
    
    break; 
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobInfoResult_CREAMTYPES__GenericFault:
    if( jr->union_JobInfoResult.CREAMTYPES__GenericFault)
      errMex = ExceptionFactory::makeStringFromFault( jr->union_JobInfoResult.CREAMTYPES__GenericFault);
    else
      errMex = "Error Message Not Available";
    
    (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobInfoWrapper::GENERIC, JobInfoWrapper( ), errMex );
    
    break;
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobInfoResult_CREAMTYPES__LeaseIdMismatchFault:
    if( jr->union_JobInfoResult.CREAMTYPES__LeaseIdMismatchFault )
      errMex = ExceptionFactory::makeStringFromFault( jr->union_JobInfoResult.CREAMTYPES__LeaseIdMismatchFault);
    else
      errMex = "Error Message Not Available";
    
    (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobInfoWrapper::LEASEIDMISMATCH, JobInfoWrapper( ), errMex );
    
    break;
    
    //------------------------------------------------------------
  case SOAP_UNION__CREAMTYPES__union_JobInfoResult_jobInfo:
    if( jr->union_JobInfoResult.jobInfo ) {
      JobInfoWrapper jinfo( jr->union_JobInfoResult.jobInfo );
      (*m_target)[ *jr->jobDescriptionId ] = boost::make_tuple( JobInfoWrapper::OK, jinfo, "" );
    }
    
    break;
    
  } // switch
} //  operator()

//______________________________________________________________________________
CreamProxy_Info::CreamProxy_Info( const JobFilterWrapper* filter, InfoArrayResult* target, const int timeout ) throw()
  : AbsCreamProxy( timeout ), m_jobFilter( filter ), m_target( target )
{
}

//_____________________________________________________________________________
void CreamProxy_Info::execute( const string& serviceAddress, const bool ignore_tag_mismatch ) 
    throw(BaseException&,
          InvalidArgumentException&,
          GridProxyDelegationException&,
          JobSubmissionDisabledException&,
          GenericException&,
	  //          AuthenticationException&,
          AuthorizationException&,
          DelegationException&,
          InternalException&,
          ConnectionTimeoutException&,
          auth_ex&,
	  soap_ex&,
	  soap_runtime_ex&)
{
    static const char* method_name = "CreamProxy_Info::execute() - ";
    initSoap init(this);
  
#ifdef DOPROFILE
    apiUtil::scoped_timer T("CreamProxy_Info::execute-soap_call___CREAM__JobInfo");
#endif  
  
    _CREAMTYPES__JobInfoResponse resp;
    /*    CREAM_SAFE_LOG(m_log_dev->debugStream() 
		   << "CreamProxy_Info::execute() - "
		   << "Sending JobInfo request with certificate ["
		   << m_certfile << "]"
		   );
    */
    if(SOAP_OK != soap_call___CREAM__JobInfo(m_soap,
                                             serviceAddress.c_str(),
                                             NULL,    // soapAction
                                             (CREAMTYPES__JobFilter*)m_jobFilter, 
                                             &resp) ) {
        ExceptionFactory::raiseException(m_soap, ignore_tag_mismatch);
        
    } else {        
        //m_target->clear();
        processorInfoResult proc(m_target);    
        for ( std::vector< CREAMTYPES__JobInfoResult* >::const_iterator it = resp.result.begin(); it != resp.result.end(); ++it ) {
            try {               
                proc(*it); //can raise any type of exception
            } catch( const std::exception& ex ) {
                CREAM_SAFE_LOG(m_log_dev->errorStream() << method_name
                               << "Got std::exception \""
                               << ex.what()
                               << "\". Rethrowing..."
			        );
                throw ex;
            } catch( ... ) {
                CREAM_SAFE_LOG(m_log_dev->errorStream() << method_name
                               << "Got unknown exception. Rethrowing..."
			        );
                throw; // rethrow
            }
        }
    }
}
