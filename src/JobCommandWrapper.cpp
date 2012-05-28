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

#include <glite/ce/cream-client-api-c/JobCommandWrapper.h>

using namespace glite::ce::cream_client_api::soap_proxy;

//______________________________________________________________________________
void JobCommandWrapper::reset( void ) throw() 
{
  //std::cout << "JobCommandWrapper::reset() - freeing memory..." << std::endl;
  
  delete id;                     id=0;
  delete failureReason;          failureReason=0;
  delete creationTime;           creationTime = 0;
  delete startSchedulingTime;    startSchedulingTime=0;
  delete startProcessingTime;    startProcessingTime=0;
  delete executionCompletedTime; executionCompletedTime=0;
}

//______________________________________________________________________________
void JobCommandWrapper::set( const CREAMTYPES__Command* aCommand ) throw()
{
  if(aCommand->id)
    this->id = new std::string( *aCommand->id );
  else
    this->id = NULL;
  
  this->name = aCommand->name;
  this->category = aCommand->category;
  this->status = aCommand->status;
  
  if(aCommand->failureReason)
    this->failureReason = new std::string(*aCommand->failureReason);
  else
    this->failureReason = NULL;
  
  if(aCommand->creationTime) {
    this->creationTime = new time_t();
    *this->creationTime = *aCommand->creationTime;
  } else this->creationTime = NULL;
  
  if(aCommand->startSchedulingTime) {
    this->startSchedulingTime = new time_t();
    *this->startSchedulingTime = *aCommand->startSchedulingTime;
  } else this->startSchedulingTime = NULL;
  
  if(aCommand->startProcessingTime) {
    this->startProcessingTime = new time_t();
    *this->startProcessingTime = *aCommand->startProcessingTime;
  } else this->startProcessingTime = NULL;
  
  if(aCommand->executionCompletedTime) {
    this->executionCompletedTime = new time_t();
    *this->executionCompletedTime = *aCommand->executionCompletedTime;
  } else this->executionCompletedTime = NULL;
  
}

//______________________________________________________________________________
// JobCommandWrapper::JobCommandWrapper(const std::string& id, 
// 				     const std::string& name,
// 				     const std::string& category,
// 				     const std::string& status,
// 				     const std::string& failureReason,
// 				     const time_t creationTime,
// 				     const time_t startSchedulingTime,
// 				     const time_t startProcessingTime,
// 				     const time_t executionCompletedTime) throw() 
// {
//   if(!id.empty())
//     this->id = new std::string( id );
//   else
//     this->id = NULL;
  
//   this->name = name;
//   this->category = category;
//   this->status = status;
  
//   if(!failureReason.empty())
//     this->failureReason = new std::string(failureReason);
//   else
//     this->failureReason = NULL;
  
//   if(creationTime) {
//     this->creationTime = new time_t();
//     *this->creationTime = creationTime;
//   } else this->creationTime = NULL;
  
//   if(startSchedulingTime) {
//     this->startSchedulingTime = new time_t();
//     *this->startSchedulingTime = startSchedulingTime;
//   } else this->startSchedulingTime = NULL;
  
//   if(startProcessingTime) {
//     this->startProcessingTime = new time_t();
//     *this->startProcessingTime = startProcessingTime;
//   } else this->startProcessingTime = NULL;
  
//   if(executionCompletedTime) {
//     this->executionCompletedTime = new time_t();
//     *this->executionCompletedTime = executionCompletedTime;
//   } else this->executionCompletedTime = NULL;
// }
