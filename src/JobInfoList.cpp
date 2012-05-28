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

#include "glite/ce/cream-client-api-c/JobInfoList.h"
#include "glite/ce/cream-client-api-c/job_statuses.h"
#include <string>

using namespace std;
namespace soapProxy = glite::ce::cream_client_api::soap_proxy;

//______________________________________________________________________________
void soapProxy::JobInfoList::print(const int& level) {
  if( !jobInfo.size() ) return;
  vector<creamtypes__JobInfo*>::const_iterator jit;
  for( jit = jobInfo.begin(); jit != jobInfo.end(); jit++ ) {

    static char tstamp[256];
    static char command_creation_time[256];
    static char command_startscheduling_time[256];
    static char command_startprocessing_time[256];
    static char command_execompleted_time[256];
    static struct tm TSTAMP;
    static struct tm command_creation_time_TM;
    static struct tm command_startscheduling_time_TM;
    static struct tm command_startprocessing_time_TM;
    static struct tm command_execompleted_time_TM;

    printf("\n****** JobID=[%s]\n", (*jit)->CREAMJobId.c_str() );
    if(level >= 1)
      printf("\tGridJobID=[%s]\n", (*jit)->GridJobId.c_str());
    printf("\tCurrent Status=[%s]\n", (*jit)->status.at((*jit)->status.size()-1)->name.c_str());
    vector<creamtypes__Status*>::const_iterator it;
    printf("\tJob status changes:\n");
    for(it = (*jit)->status.begin();
        it != (*jit)->status.end();
	it++)
	{
	  if(level<1)
	    printf("\tStatus=[%s]\n", (*it)->name.c_str());
	  else {
            localtime_r(&((*it)->timestamp), &TSTAMP);
	    memset(tstamp, 0, 256);
	    strftime(tstamp, sizeof(tstamp), "%a %d %b %Y %T", &TSTAMP);
 	    printf("\t*** Status=[%s] Time=[%s] (%d)\n", (*it)->name.c_str(),
	                                                 tstamp,(int)((*it)->timestamp));
	  }

	  if(level >= 1) {
	    if( (*it)->exitCode )
	      printf("\tExitCode      = [%s]\n", (*it)->exitCode->c_str());
	    if( (*it)->failureReason )
	      printf("\tFailureReason = [%s]\n", (*it)->failureReason->c_str());
      	    }
	  }


	if( level >= 1 ) {
	    vector<creamtypes__Command*>::const_iterator cit;
	    printf("\tIssued Commands=\n");

	    for(cit=(*jit)->lastCommand.begin();
	        cit != (*jit)->lastCommand.end();
		cit++)
            {
	      printf("\t  [\n");
	      if( (*cit) ) {
	        printf("\t   %-24s %s\n", "name", (*cit)->name.c_str());
	        printf("\t   %-24s %s\n", "status", (*cit)->status.c_str());
	        if( (*cit)->failureReason )
                  printf("\t   %-24s %s\n", "failure reason", (*cit)->failureReason->c_str());
		if( level >= 2 ) {
		  if( (*cit)->creationTime ) {
		    localtime_r((*cit)->creationTime, &command_creation_time_TM);
	    	    memset(command_creation_time, 0, 256);
	    	    strftime(command_creation_time, sizeof(command_creation_time), "%a %d %b %Y %T", &command_creation_time_TM);
		    printf("\t   %-24s %s\n", "creation time", command_creation_time);
		  }
		  if( (*cit)->startSchedulingTime ) {
		    localtime_r((*cit)->startSchedulingTime, &command_startscheduling_time_TM);
	    	    memset(command_startscheduling_time, 0, 256);
	    	    strftime(command_startscheduling_time, sizeof(command_startscheduling_time), "%a %d %b %Y %T", &command_startscheduling_time_TM);
		    printf("\t   %-24s %s\n", "start scheduling time", command_startscheduling_time);
		  }
		  if( (*cit)->startProcessingTime ) {
		    localtime_r((*cit)->startProcessingTime, &command_startprocessing_time_TM);
	    	    memset(command_startprocessing_time, 0, 256);
	    	    strftime(command_startprocessing_time, sizeof(command_startprocessing_time), "%a %d %b %Y %T", &command_startprocessing_time_TM);
		    printf("\t   %-24s %s\n", "start processing time", command_startprocessing_time);
		  }
		  if( (*cit)->executionCompletedTime ) {
		    localtime_r((*cit)->startProcessingTime, &command_execompleted_time_TM);
	    	    memset(command_execompleted_time, 0, 256);
	    	    strftime(command_execompleted_time, sizeof(command_execompleted_time), "%a %d %b %Y %T", &command_execompleted_time_TM);
		    printf("\t   %-24s %s\n", "execution completed time", command_execompleted_time);
		  }
		}
	      }
	      printf("\t  ]\n");
	    }
	}

	if(level >=2 ) {
	  printf("\tWorkerNode    = [%s]\n", (*jit)->workerNode.c_str());
	  printf("\tlocalUser=[%s]\n", (*jit)->localUser.c_str());
	  if( (*jit)->leaseTime )
	    printf("\tleaseTime=[%d]\n", (int)(*((*jit)->leaseTime)) );
          printf("\tProxyDelegationId=[%s]\n", (*jit)->proxyDelegationId.c_str());
          printf("\tProxyInfo=[%s]\n", (*jit)->proxyInfo.c_str());
          printf("\tCREAMInputSandboxURI=[%s]\n", (*jit)->CREAMInputSandboxURI.c_str()); 	  		  printf("\tCREAMOutputSandboxURI=[%s]\n", (*jit)->CREAMOutputSandboxURI.c_str());
          printf("\tJDL=[%s]\n", (*jit)->JDL.c_str());
          printf("\tLRMSAbsLayerJobId=[%s]\n", (*jit)->LRMSAbsLayerJobId.c_str());
          printf("\tLRMSJobId=[%s]\n", (*jit)->LRMSJobId.c_str());
          printf("\tWorkingDirectory=[%s]\n", (*jit)->workingDirectory.c_str());
   	}
     }
}


//______________________________________________________________________________
void soapProxy::JobInfoList::getJobIDS(vector<string>& target) {
  if(!jobInfo.size()) return;
  for(vector<creamtypes__JobInfo*>::const_iterator it=jobInfo.begin();
      it != jobInfo.end();
      it++)
      target.push_back((*it)->CREAMJobId);
}

//______________________________________________________________________________
soapProxy::JobInfoList::~JobInfoList() {
}

//______________________________________________________________________________
soapProxy::JobInfoList::getStatusList(vector<soapProxy::Status>& target) const
{
  for(vector<creamtypes__Status*>::const_iterator it=status.begin();
      it != status.end();
      ++it)
      {
	target.push_back( *(*it) );
      }
}

//______________________________________________________________________________
soapProxy::JobInfoList::getLastCommandList(vector<soapProxy::Cmd>& target)
const
{
  for(vector<creamtypes__Command*>::const_iterator it=lastCommand.begin();
      it != lastCommand.end();
      ++it)
      {
	target.push_back( *(*it) );
      }
}
