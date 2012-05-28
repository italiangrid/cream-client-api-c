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

#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"
#include "glite/ce/cream-client-api-c/Status.h"
#include "glite/ce/cream-client-api-c/job_statuses.h"

using namespace std;

namespace soapProxy = glite::ce::cream_client_api::soap_proxy;
namespace job_states = glite::ce::cream_client_api::job_statuses;

//______________________________________________________________________________
soapProxy::Status::~Status()
{
}

//______________________________________________________________________________
soapProxy::Status::Status(creamtypes__Status* status) {
  if(!status) return;
  m_name = status->name;
  m_timestamp = status->timestamp;
  if( status->exitCode )
    m_exitCode = *(status->exitCode);
  else
    m_exitCode = "";
  if( status->failureReason )
    m_failureReason = *(status->failureReason);
  else
    m_failureReason = "";
  if( status->jobId )
    m_jobId = *(status->jobId);
  else
    m_jobId = "";
}

//______________________________________________________________________________
void soapProxy::Status::print( const int level ) const
{
    printf("\n****** JobID=[%s]\n", m_jobId.c_str() );
    printf("\tStatus        = [%s]\n", m_name.c_str());
    if(job_states::isFinished( job_states::getStatusNum(m_name) )) {
      printf("\tExitCode      = [%s]\n", m_exitCode.c_str());
      if(job_states::isFailed( job_states::getStatusNum(m_name) ))
        printf("\tFailureReason = [%s]\n", m_failureReason.c_str());
    }
}
