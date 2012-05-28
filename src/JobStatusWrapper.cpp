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

#include <glite/ce/cream-client-api-c/JobStatusWrapper.h>

using namespace std;
using namespace glite::ce::cream_client_api::soap_proxy;

//______________________________________________________________________________
void JobStatusWrapper::set( const CREAMTYPES__Status* aStatus ) throw()
{
  
  if (aStatus->jobId)
    jobId = new JobIdWrapper( aStatus->jobId );
  else
    jobId = 0;
  
  name = aStatus->name;
  timestamp = aStatus->timestamp;
  
  if(aStatus->exitCode)
    exitCode = new std::string( *aStatus->exitCode );
  else
    exitCode = 0;
  
  if(aStatus->failureReason)
    failureReason = new std::string( *aStatus->failureReason );
  else
    failureReason = 0;
  
  if(aStatus->description)
    description   = new std::string( *aStatus->description );
  else
    description = 0;
}

//______________________________________________________________________________
JobStatusWrapper::JobStatusWrapper( const JobIdWrapper& aJob, 
					 const std::string& name,
					 const time_t timestamp, 
					 const std::string& exitCode,
					 const std::string& failureReason,
					 const std::string& description) throw()
{
  this->jobId = new JobIdWrapper( aJob );
  this->name = name;
  this->timestamp = timestamp;
  
  if( !exitCode.empty() )
    this->exitCode      = new std::string( exitCode );
  else
    this->exitCode = 0;
  
  if( !failureReason.empty() )
    this->failureReason = new std::string( failureReason );
  else
    this->failureReason = 0;
  
  if(!description.empty())
    this->description   = new std::string( description );
  else
    this->description = 0;
}
