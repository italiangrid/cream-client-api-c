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

#include <glite/ce/cream-client-api-c/JobFilterWrapper.h>

using namespace glite::ce::cream_client_api::soap_proxy;
using namespace std;

//______________________________________________________________________________
void JobFilterWrapper::reset( void ) throw()
{
  delete fromDate;     fromDate=0;
  delete toDate;       toDate=0;
  delete delegationId; delegationId=0;
  delete leaseId;      leaseId=0;
  std::vector<CREAMTYPES__JobId * >::const_iterator it;
  for(it = jobId.begin(); it != jobId.end(); ++it){
    delete(*it);
  }
  jobId.clear();
}

//______________________________________________________________________________
void JobFilterWrapper::set( const CREAMTYPES__JobFilter& aFilter ) throw() 
{
  std::vector<CREAMTYPES__JobId*>::const_iterator it;
  for(it = aFilter.jobId.begin(); it != aFilter.jobId.end(); ++it) {
    JobIdWrapper *thisJobId = new JobIdWrapper( *it );
    jobId.push_back( thisJobId );
  }
  
  status = aFilter.status; //it is copyable because it's a vector<string>
  
  if( aFilter.fromDate && (*aFilter.fromDate > -1) )
    {
      fromDate = new time_t;
      (*fromDate) = *aFilter.fromDate;
    } else fromDate = NULL;
  
  if( aFilter.toDate && (*aFilter.toDate > -1) ) {
    toDate = new time_t;
    (*toDate) = *aFilter.toDate;
  } else toDate = NULL;
  
  if(aFilter.delegationId)
    delegationId = new std::string( *aFilter.delegationId );
  else
    delegationId = NULL;
  
  if(aFilter.leaseId)
    leaseId = new std::string( *aFilter.leaseId );
  else
    leaseId = NULL;
}

//______________________________________________________________________________
JobFilterWrapper::JobFilterWrapper(const std::vector< JobIdWrapper >& jobs,
				   const std::vector< std::string >& states,
				   const int from, const int to,
				   const std::string& delegId,
				   const std::string& lease_Id) throw() 
{
  std::vector< JobIdWrapper >::const_iterator it;
  for(it=jobs.begin(); it != jobs.end(); ++it)
    {
      jobId.push_back( (CREAMTYPES__JobId *)new JobIdWrapper( *it ) );
    }
  
  status = states;
  
  if(from>-1) {
    fromDate = new time_t;
    *fromDate = from;
  } else fromDate = NULL;
  
  if(to>-1) {
    toDate = new time_t;
    *toDate = to;
  } else toDate = NULL;
  
  if(!delegId.empty())
    delegationId = new std::string( delegId );
  else
    delegationId = NULL;
  
  if(!lease_Id.empty())
    leaseId = new std::string( lease_Id );
  else
    leaseId = NULL;
}
