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

#include <glite/ce/cream-client-api-c/ResultWrapper.h>

using namespace glite::ce::cream_client_api::soap_proxy;

#ifdef SL6

  #define UNION_JOBSTATUSRESULT_JOBUNKNOWN	 	  SOAP_UNION__CREAMTYPES__union_Result_JobUnknownFault
  #define UNION_JOBSTATUSRESULT_JOBSTATUSINVALID 	  SOAP_UNION__CREAMTYPES__union_Result_JobStatusInvalidFault
  #define UNION_JOBSTATUSRESULT_DELEGATIONIDMISMATCH	  SOAP_UNION__CREAMTYPES__union_Result_DelegationIdMismatchFault
  #define UNION_JOBSTATUSRESULT_DATEMISMATCH		  SOAP_UNION__CREAMTYPES__union_Result_DateMismatchFault
  #define UNION_JOBSTATUSRESULT_LEASEIDMISMATCH		  SOAP_UNION__CREAMTYPES__union_Result_LeaseIdMismatchFault
  #define UNION_JOBSTATUSRESULT_GENERIC			  SOAP_UNION__CREAMTYPES__union_Result_GenericFault
  #define JOBUNKNOWN_FAULT 				  JobUnknownFault
  #define JOBSTATUSINVALID_FAULT 			  JobStatusInvalidFault
  #define DELEGATIONIDMISMATCH_FAULT 			  DelegationIdMismatchFault
  #define DATEMISMATCH_FAULT				  DateMismatchFault
  #define LEASEIDMISMATCH_FAULT				  LeaseIdMismatchFault
  #define GENERIC_FAULT					  GenericFault

#else

  #define UNION_JOBSTATUSRESULT_JOBUNKNOWN	 	SOAP_UNION__CREAMTYPES__union_JobStatusResult_CREAMTYPES__JobUnknownFault
  #define UNION_JOBSTATUSRESULT_JOBSTATUSINVALID 	SOAP_UNION__CREAMTYPES__union_JobStatusResult_CREAMTYPES__JobStatusInvalidFault
  #define UNION_JOBSTATUSRESULT_DELEGATIONIDMISMATCH	SOAP_UNION__CREAMTYPES__union_JobStatusResult_CREAMTYPES__DelegationIdMismatchFault
  #define UNION_JOBSTATUSRESULT_DATEMISMATCH            SOAP_UNION__CREAMTYPES__unãon_JobStatusResult_CREAMTYPES__DateMismatchFault
  #define UNION_JOBSTATUSRESULT_LEASEIDMISMATCH    	SOAP_UNION__CREAMTYPES__unãon_JobStatusResult_CREAMTYPES__DateMismatchFault
  #define UNION_JOBSTATUSRESULT_GENERIC                 SOAP_UNION__CREAMTYPES__unãon_JobStatusResult_CREAMTYPES__DateMismatchFault
   
  #define JOBUNKNOWN_FAULT 				CREAMTYPES__JobUnknownFault
  #define JOBSTATUSINVALID_FAULT 			CREAMTYPES__JobStatusInvalidFault
  #define DELEGATIONIDMISMATCH_FAULT 			CREAMTYPES__DelegationIdMismatchFault
  #define DATEMISMATCH_FAULT                            CREAMTYPES__DateMismatchFault
  #define LEASEIDMISMATCH_FAULT                         CREAMTYPES__LeaseIdMismatchFault
  #define GENERIC_FAULT					CREAMTYPES__GenericFault 

#endif

//______________________________________________________________________________
void ResultWrapper::set(const std::vector<CREAMTYPES__Result * >& results) throw() 
{
  std::vector<CREAMTYPES__Result * >::const_iterator it;
  for(it=results.begin(); it!=results.end(); ++it) {
    CREAMTYPES__JobId* job           = (*it)->jobId;
    std::string errMex;
    
    switch((*it)->__union_Result) {
      
      //------------------------------------------------------------
    //case SOAP_UNION__CREAMTYPES__union_JobStatusResult_JobUnknownFault:
    case UNION_JOBSTATUSRESULT_JOBUNKNOWN:
    //  if( (*it)->union_Result.CREAMTYPES__JobUnknownFault )
    if( (*it)->union_Result.JOBUNKNOWN_FAULT )
       errMex = ExceptionFactory::makeStringFromFault( (*it)->union_Result.JOBUNKNOWN_FAULT );
      else
	errMex = "Error Message Not Available";
      if(job)
	notExistingJobs.push_back( std::make_pair(JobIdWrapper(job), errMex));
      else
	notExistingJobs.push_back( std::make_pair(JobIdWrapper(), errMex));
      break;
      
      //------------------------------------------------------------
    case UNION_JOBSTATUSRESULT_JOBSTATUSINVALID:
      if( (*it)->union_Result.JOBSTATUSINVALID_FAULT )
       errMex = ExceptionFactory::makeStringFromFault( (*it)->union_Result.JOBSTATUSINVALID_FAULT );
      else
	errMex = "Error Message Not Available";
      if(job)
	notMatchingStatusJobs.push_back( std::make_pair(JobIdWrapper(job), errMex));
      else
	notMatchingStatusJobs.push_back( std::make_pair(JobIdWrapper(), errMex));
      break; 
      
      //------------------------------------------------------------
    case UNION_JOBSTATUSRESULT_DELEGATIONIDMISMATCH:
      if( (*it)->union_Result.DELEGATIONIDMISMATCH_FAULT)
       errMex = ExceptionFactory::makeStringFromFault( (*it)->union_Result.DELEGATIONIDMISMATCH_FAULT);
      else
	errMex = "Error Message Not Available";
      if(job)
	notMatchingProxyDidJobs.push_back( std::make_pair(JobIdWrapper(job), errMex));
      else
	notMatchingProxyDidJobs.push_back( std::make_pair(JobIdWrapper(), errMex));
      break; 
      
      //------------------------------------------------------------
    case UNION_JOBSTATUSRESULT_DATEMISMATCH:
      if( (*it)->union_Result.DATEMISMATCH_FAULT )
       errMex = ExceptionFactory::makeStringFromFault( (*it)->union_Result.DATEMISMATCH_FAULT);
      else
	errMex = "Error Message Not Available";
      if(job)
	notMatchingDateJobs.push_back( std::make_pair(JobIdWrapper(job), errMex));
      else
	notMatchingDateJobs.push_back( std::make_pair(JobIdWrapper(), errMex));
      break; 
      
      //------------------------------------------------------------
    case UNION_JOBSTATUSRESULT_GENERIC:
      if( (*it)->union_Result.GENERIC_FAULT)
       errMex = ExceptionFactory::makeStringFromFault( (*it)->union_Result.GENERIC_FAULT);
      else
	errMex = "Error Message Not Available";
      if(job)
	notExistingJobs.push_back( std::make_pair(JobIdWrapper(job), errMex));
      else
	notExistingJobs.push_back( std::make_pair(JobIdWrapper(), errMex));
      break;
      
      //------------------------------------------------------------
    case UNION_JOBSTATUSRESULT_LEASEIDMISMATCH:
      if( (*it)->union_Result.LEASEIDMISMATCH_FAULT )
       errMex = ExceptionFactory::makeStringFromFault( (*it)->union_Result.LEASEIDMISMATCH_FAULT );
      else
	errMex = "Error Message Not Available";
      if(job)
	notMatchingLeaseJobs.push_back( std::make_pair(JobIdWrapper(job), errMex));
      else
	notMatchingLeaseJobs.push_back( std::make_pair(JobIdWrapper(), errMex));
      break;
    }
    
  } // end loop over Results
}

//______________________________________________________________________________
void ResultWrapper::fill(std::list<std::pair<JobIdWrapper, std::string> >& target, 
			 const std::list<std::pair<JobIdWrapper, std::string> >& source) 
  const throw()
{
  std::list<std::pair<JobIdWrapper, std::string> >::const_iterator it;
  for( it=source.begin() ; it != source.end(); ++it ) {
    target.push_back( std::make_pair( JobIdWrapper( it->first), it->second ));
  }
}

//______________________________________________________________________________
ResultWrapper& 
ResultWrapper::operator=( const std::vector<CREAMTYPES__Result * >& results ) throw()
{
  //okJobs.clear();
    notExistingJobs.clear();
    notMatchingStatusJobs.clear();
    notMatchingDateJobs.clear();
    notMatchingProxyDidJobs.clear();
    notMatchingLeaseJobs.clear();
    
    this->set(results);
  return *this;
}
