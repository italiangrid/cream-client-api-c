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
#ifndef __JOBINFOOBJECT_H__
#define __JOBINFOOBJECT_H__

//#include "glite/ce/cream-client-api-c/soap_definitions.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"
class JobInfoObject : public creamtypes__JobInfo { // ns3__JobInfo
 public:

  //____________________________________________________________________________
  JobInfoObject(const creamtypes__JobInfo& J) : creamtypes__JobInfo(J) {
/*			  LRMSubmissionTime = new time_t();
			  LRMStartRunningTime = new time_t();
			  LRMSCompletedTime = new time_t();
			  if(J.LRMSubmissionTime)
			    *LRMSubmissionTime = *(J.LRMSubmissionTime);
			  else
			    *LRMSubmissionTime = 0;
			  if(J.LRMStartRunningTime)
			    *LRMStartRunningTime = *(J.LRMStartRunningTime);
			  else
			    *LRMStartRunningTime = 0;
			  if(J.LRMSCompletedTime)
			    *LRMSCompletedTime = *(J.LRMSCompletedTime);
			  else
			    *LRMSCompletedTime = 0;*/
			}

  //____________________________________________________________________________
  JobInfoObject(const JobInfoObject& J) : creamtypes__JobInfo(J) {
/*			  LRMSubmissionTime = new time_t();
			  LRMStartRunningTime = new time_t();
			  LRMSCompletedTime = new time_t();
			  if(J.LRMSubmissionTime)
			    *LRMSubmissionTime = *(J.LRMSubmissionTime);
 			  else
 			    *LRMSubmissionTime = 0;
			  if(J.LRMStartRunningTime)
			    *LRMStartRunningTime = *(J.LRMStartRunningTime);
 			  else
 			    *LRMStartRunningTime = 0;
			  if(J.LRMSCompletedTime)
			    *LRMSCompletedTime = *(J.LRMSCompletedTime);
 			  else
 			    *LRMSCompletedTime = 0;*/
			}

  //____________________________________________________________________________
  virtual ~JobInfoObject() { 
/*    if(LRMSubmissionTime) delete(LRMSubmissionTime);
    if(LRMStartRunningTime) delete(LRMStartRunningTime);
    if(LRMSCompletedTime) delete(LRMSCompletedTime);*/
  }

};

#endif
