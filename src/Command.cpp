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
#include "glite/ce/cream-client-api-c/Command.h"

namespace soapProxy = glite::ce::cream_client_api::soap_proxy;

soapProxy::Command::Command(creamtypes__Command* C)
{
  if(!C) return;
  m_name = C->name;
  m_status = C->status;
  if( C->failureReason )
    m_failureReason = *(C->failureReason);
  else
    m_failureReason = "";
  if( C->creationTime )
    m_creationTime = *(C->creationTime);
  else
    m_creationTime = 0;
  if( C->startSchedulingTime )
    m_startSchedulingTime = *(C->startSchedulingTime);
  else
    m_startSchedulingTime = 0;
  if( C->startProcessingTime )
    m_startProcessingTime = *(C->startProcessingTime);
  else
    m_startProcessingTime = 0;
  if( C->executionCompletedTime )
    m_executionCompletedTime = *(C->executionCompletedTime);
  else
    m_executionCompletedTime = 0;
}
