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

#include "glite/ce/cream-client-api-c/JobStatusList.h"
#include "glite/ce/cream-client-api-c/JobStatusObject.h"
#include "glite/ce/cream-client-api-c/job_statuses.h"

using namespace std;
namespace soapProxy = glite::ce::cream_client_api::soap_proxy;

void soapProxy::JobStatusList::print(const int& level) {
  if(!jobStatus.size()) return;
  for(vector<creamtypes__Status * >::const_iterator sit = jobStatus.begin();
      sit != jobStatus.end();
      sit++) { //unsigned int j=0; j<jobStatus.size(); j++) {

    char Timestamp[256];

    memset(Timestamp, 0, 256);

    struct tm a;
    localtime_r(&((*sit)->timestamp), &a);

    if((*sit)->timestamp>0)
      strftime(Timestamp, sizeof(Timestamp), "%a %d %b %Y %T", &a);

    if((*sit)->jobId)
      printf("\n****** JobID=[%s]\n", (*sit)->jobId->c_str());
    else
      printf("\n****** JobID=[N/A]\n");

    string _status = (*sit)->name;

    if(_status != string("N/A")) {
      printf("\tStatus=[%s]\n", _status.c_str());
    }

//    if(jobStatus.at(j)->timestamp>0)
//      printf("\tTimestamp=[%d] [%s]\n", (int)jobStatus.at(j)->timestamp,
//      					Timestamp);

    if((*sit)->exitCode)
      printf("\tExitCode=[%s]\n", (*sit)->exitCode->c_str());

    if((*sit)->failureReason)
      printf("\tFailureReason=[%s]\n", (*sit)->failureReason->c_str());

//     if(level >=1) {
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->GridJobId != "N/A")
//         printf("\tGridJobID=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->GridJobId.c_str());
// 
//       printf("\tCreationTime=[%d] (%s)\n",(int)SOAP_JOBINFO_LIST_MEMBER.at(j)->creationTime,creat_time);
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->LRMSubmissionTime)
//         printf("\tLRMSSubmissionTime=[%d] (%s)\n",(int)*SOAP_JOBINFO_LIST_MEMBER.at(j)->LRMSubmissionTime, sub_time);
//       else
// 	printf("\tLRMSSubmissionTime=[N/A] (N/A)\n");
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->LRMStartRunningTime)
//         printf("\tLRMSStartRunningTime=[%d] (%s)\n",(int)*SOAP_JOBINFO_LIST_MEMBER.at(j)->LRMStartRunningTime, start_time);
//       else
// 	printf("\tLRMSStartRunningTime=[N/A] (N/A)\n");
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->LRMSCompletedTime)
//         printf("\tLRMSCompletedTime=[%d] (%s)\n",(int)*SOAP_JOBINFO_LIST_MEMBER.at(j)->LRMSCompletedTime, compl_time);
//       else
// 	printf("\tLRMSCompletedTime=[N/A] (N/A)\n");
// 
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->reason != "N/A")
//         printf("\tReason=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->reason.c_str());
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->workerNode != "N/A")
//         printf("\tWorkerNode=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->workerNode.c_str());
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->exitCode != "N/A")
//         printf("\tExitCode=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->exitCode.c_str());
//       for(unsigned i=0; i<SOAP_JOBINFO_LIST_MEMBER.at(j)->lastCommand.size();i++)
//       {
// 	if(SOAP_JOBINFO_LIST_MEMBER.at(j)->lastCommand.at(i))
// 	  printf("\tLastCommand=[%s]\n",
//                  SOAP_JOBINFO_LIST_MEMBER.at(j)->lastCommand.at(i)->name.c_str());
// 	  printf("\t\tLastCommand.status=[%s]\n",
//                  SOAP_JOBINFO_LIST_MEMBER.at(j)->lastCommand.at(i)->status.c_str());
// 	  if(SOAP_JOBINFO_LIST_MEMBER.at(j)->lastCommand.at(i)->failureReason->c_str())
//           printf("\t\tLastCommand.fail-reason=[%s]\n",
// 	  SOAP_JOBINFO_LIST_MEMBER.at(j)->lastCommand.at(i)->failureReason->c_str());
//       }
// //       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->lastCommand)
// // 	{
// // 	  printf("\tLastCommand=[%s]\n", SOAP_JOBINFO_LIST_MEMBER.at(j)->lastCommand->name.c_str());
// // 	  printf("\t\tLastCommand.status=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->lastCommand->status.c_str());
// // 	  printf("\t\tLastCommand.fail-reason=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->lastCommand->failureReason.c_str());
// // 	      char cmd_creat_time[256];
// // 	      char cmd_sts_time[256];
// // 	      char cmd_ste_time[256];
// // 	      char cmd_exc_time[256];
// 
// // 	      memset(cmd_creat_time, 0, 256);
// // 	      memset(cmd_sts_time, 0, 256);
// // 	      memset(cmd_ste_time, 0, 256);
// // 	      memset(cmd_exc_time, 0, 256);
// // 	      struct tm ca, cb, cc, cd;
// // 	      localtime_r(&(SOAP_JOBINFO_LIST_MEMBER.at(j)->creationTime), &ca);
// // 	      if(SOAP_JOBINFO_LIST_MEMBER.at(j)->lastCommand->creationTime) localtime_r((SOAP_JOBINFO_LIST_MEMBER.at(j)->LRMSubmissionTime), &cb);
// // 	      if(SOAP_JOBINFO_LIST_MEMBER.at(j)->lastCommand->startSchedulingTime) localtime_r((SOAP_JOBINFO_LIST_MEMBER.at(j)->LRMStartRunningTime), &cc);
// // 	      if(SOAP_JOBINFO_LIST_MEMBER.at(j)->lastCommand->startProcessingTime) localtime_r((SOAP_JOBINFO_LIST_MEMBER.at(j)->LRMSCompletedTime), &cd);
// 
// // 	}
//     }
// 
//     if(level >=2 ) {
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->localUser != "N/A")
// 	printf("\tlocalUser=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->localUser.c_str());
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->proxyDelegationId != "N/A")
//         printf("\tProxyDelegationId=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->proxyDelegationId.c_str());
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->proxyInfo != "N/A")
//         printf("\tProxyInfo=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->proxyInfo.c_str());
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->CREAMInputSandboxURI != "N/A")
//         printf("\tCREAMInputSandboxURI=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->CREAMInputSandboxURI.c_str());
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->CREAMOutputSandboxURI != "N/A")
//         printf("\tCREAMOutputSandboxURI=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->CREAMOutputSandboxURI.c_str());
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->JDL.compare("N/A") != 0)
//         printf("\tJDL=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->JDL.c_str());
// 
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->LRMSAbsLayerJobId.compare("N/A") != 0)
//         printf("\tLRMSAbsLayerJobId=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->LRMSAbsLayerJobId.c_str());
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->LRMSJobId.compare("N/A") != 0)
//         printf("\tLRMSJobId=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->LRMSJobId.c_str());
//       if(SOAP_JOBINFO_LIST_MEMBER.at(j)->workingDirectory != "N/A")
//         printf("\tWorkingDirectory=[%s]\n",SOAP_JOBINFO_LIST_MEMBER.at(j)->workingDirectory.c_str());
//     }
   }
}

//______________________________________________________________________________
void soapProxy::JobStatusList::getJobIDS(vector<string>& target) {
  if(!jobStatus.size()) return;
  for(vector<creamtypes__Status*>::const_iterator jit = jobStatus.begin();
      jit != jobStatus.end();
      jit++) { //unsigned int j=0; j<jobStatus.size(); j++) {
    target.push_back(*((*jit)->jobId));
  }
}

//______________________________________________________________________________
soapProxy::JobStatusList::~JobStatusList() {
  for(vector<creamtypes__Status*>::const_iterator jit = jobStatus.begin();
      jit != jobStatus.end();
      jit++) //unsigned int j=0; j<jobStatus.size(); j++)
    if(*jit)
      delete((JobStatusObject*)*jit);
}
