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
#include "glite/ce/cream-client-api-c/JobInfo.h"
#include "glite/ce/cream-client-api-c/job_statuses.h"

namespace soapProxy = glite::ce::cream_client_api::soap_proxy;
namespace job_states = glite::ce::cream_client_api::job_statuses;
using namespace std;

//______________________________________________________________________________
soapProxy::JobInfo::JobInfo( creamtypes__JobInfo* J)
{
  if(!J) return;
  m_CREAMJobId = J->CREAMJobId;
  m_GridJobId = J->GridJobId;
  m_LRMSAbsLayerJobId = J->LRMSAbsLayerJobId;
  m_LRMSJobId = J->LRMSJobId;
  m_proxyDelegationId = J->proxyDelegationId;
  m_workerNode = J->workerNode;
  m_localUser = J->localUser;
  if(J->leaseTime) m_leaseTime = *(J->leaseTime);
  else m_leaseTime = 0;
  m_workingDirectory = J->workingDirectory;
  m_CREAMInputSandboxURI = J->CREAMInputSandboxURI;
  m_CREAMOutputSandboxURI = J->CREAMOutputSandboxURI;
  m_JDL = J->JDL;
  m_proxyInfo = J->proxyInfo;


  vector<creamtypes__Status*>::const_iterator csit;
  for(csit = J->status.begin(); csit != J->status.end(); ++csit)
  {
    m_statusList.push_back( soapProxy::Status(*csit) ); // dont worry: soapProxy::Status is copyable
  }
  vector<creamtypes__Command*>::const_iterator ccit;
  for(ccit = J->lastCommand.begin(); ccit != J->lastCommand.end(); ++ccit)
  {
    m_lastCommandList.push_back( soapProxy::Command(*ccit) ); // dont worry: soapProxy::Command is copyable
  }
}

//______________________________________________________________________________
soapProxy::JobInfo::~JobInfo()
{

}

//______________________________________________________________________________
void soapProxy::JobInfo::print(const int level) const
{
    static char tstamp[256];
    static char command_creation_time[256], leaseTime[256];
    static char command_startscheduling_time[256];
    static char command_startprocessing_time[256];
    static char command_execompleted_time[256];
    static struct tm TSTAMP;
    static struct tm command_creation_time_TM, leaseTime_TM;
    static struct tm command_startscheduling_time_TM;
    static struct tm command_startprocessing_time_TM;
    static struct tm command_execompleted_time_TM;

    printf("\n****** JobID=[%s]\n", m_CREAMJobId.c_str() );
    
    printf("\tGridJobID      = [%s]\n", m_GridJobId.c_str() );
    printf("\tCurrent Status = [%s]\n", m_statusList.at(m_statusList.size()-1).getStatusName().c_str());
    if(level >= 1) {
	  string stName = m_statusList.at(m_statusList.size()-1).getStatusName();
	  if( job_states::isFinished( job_states::getStatusNum(stName) ) ) {
	    
	    printf("\tExitCode       = [%s]\n", m_statusList.at(m_statusList.size()-1).getExitCode().c_str());
	    
	    if(job_states::isFailed(job_states::getStatusNum(stName) ) ) {
	      printf("\tFailureReason  = [%s]\n", m_statusList.at(m_statusList.size()-1).getFailureReason().c_str());
	    }
          }
    }

    vector< soapProxy::Status >::const_iterator it;
    printf("\n\tJob status changes:\n\t-------------------\n");
    for(it = m_statusList.begin();
        it != m_statusList.end();
	it++)
    {
	  time_t tmp = (*it).getTimestamp();
          localtime_r(&tmp, &TSTAMP);
	  memset(tstamp, 0, 256);
	  if(tmp > 0 )
	    strftime(tstamp, sizeof(tstamp), "%a %d %b %Y %T", &TSTAMP);
	  else
	    sprintf(tstamp, "N/A");

	  string stmp = "[";
	  stmp +=  (*it).getStatusName() + "]";
 	  printf("\t\t*** Status=%18s Time=[%s] (%d)\n", stmp.c_str(),
	                                                 tstamp,(int)((*it).getTimestamp()));
	  //}
     }

     if( level >= 1 ) {
     vector< soapProxy::Command >::const_iterator cit;
     printf("\n\tIssued Commands:\n\t----------------\n");

	    for(cit = m_lastCommandList.begin();
	        cit != m_lastCommandList.end();
		cit++)
            {
	      printf("\t\t  [\n");
	      //if( (*cit) ) {
	        printf("\t\t   %-26s %s\n", "name", (*cit).getCommandName().c_str());
	        printf("\t\t   %-26s %s\n", "status", (*cit).getStatusName().c_str());
	        //if( (*cit)->failureReason )
		if( (*cit).getFailureReason() != "" )
                  printf("\t\t   %-26s %s\n", "failure reason", (*cit).getFailureReason().c_str());
		if( level >= 2 ) {
		    
		    time_t tmp = (*cit).getCreationTime();
		    localtime_r( &tmp, &command_creation_time_TM);
	    	    memset(command_creation_time, 0, 256);
		    if(tmp > 0)
	    	      strftime(command_creation_time, sizeof(command_creation_time), "%a %d %b %Y %T", &command_creation_time_TM);
		    else
		      sprintf(command_creation_time, "N/A");
		    printf("\t\t   %-26s %s (%d)\n", "creation time", command_creation_time, tmp);
		    //--------------------------------------
		    tmp = (*cit).getStartSchedulingTime();
		    localtime_r(&tmp, &command_startscheduling_time_TM);
	    	    memset(command_startscheduling_time, 0, 256);
		    if(tmp>0)
	    	      strftime(command_startscheduling_time, sizeof(command_startscheduling_time), "%a %d %b %Y %T", &command_startscheduling_time_TM);
		    else
		      sprintf(command_startscheduling_time, "N/A");
		    printf("\t\t   %-26s %s (%d)\n", "start scheduling time", command_startscheduling_time, tmp);
		    //--------------------------------------
		    tmp = (*cit).getStartProcessingTime();
		    localtime_r(&tmp, &command_startprocessing_time_TM);
	    	    memset(command_startprocessing_time, 0, 256);
		    if(tmp>0)
	    	      strftime(command_startprocessing_time, sizeof(command_startprocessing_time), "%a %d %b %Y %T", &command_startprocessing_time_TM);
		    else
		      sprintf(  command_startprocessing_time, "N/A" );
		    printf("\t\t   %-26s %s (%d)\n", "start processing time", command_startprocessing_time, tmp);
		    //--------------------------------------
		    tmp = (*cit).getExecutionCompletedTime();
		    localtime_r(&tmp, &command_execompleted_time_TM);
	    	    memset(command_execompleted_time, 0, 256);
		    if(tmp>0)
	    	      strftime(command_execompleted_time, sizeof(command_execompleted_time), "%a %d %b %Y %T", &command_execompleted_time_TM);
		    else
		      sprintf(  command_execompleted_time, "N/A");
		    printf("\t\t   %-26s %s (%d)\n", "execution completed time", command_execompleted_time, tmp);
		}
	      //}
	      printf("\t\t  ]\n");
	    }
	}



	if(level >=2 ) {
	  time_t tmp = m_leaseTime;
	  
	  localtime_r( &tmp, &leaseTime_TM);
	  memset(leaseTime, 0, 256);
	  strftime(leaseTime, sizeof(leaseTime), "%a %d %b %Y %T", &leaseTime_TM);
	  printf("\n\tExtra information:\n\t------------------\n");
	  printf("\tWorkerNode            = [%s]\n", m_workerNode.c_str());
	  printf("\tlocalUser             = [%s]\n", m_localUser.c_str());
	  printf("\tleaseTime             = [%s] (%d)\n", leaseTime, (int)(m_leaseTime) );
          printf("\tProxyDelegationId     = [%s]\n", m_proxyDelegationId.c_str());
          printf("\tProxyInfo             = [%s]\n", m_proxyInfo.c_str());
          printf("\tCREAMInputSandboxURI  = [%s]\n", m_CREAMInputSandboxURI.c_str());
	  printf("\tCREAMOutputSandboxURI = [%s]\n", m_CREAMOutputSandboxURI.c_str());
          printf("\tJDL                   = [%s]\n", m_JDL.c_str());
          printf("\tLRMSAbsLayerJobId     = [%s]\n", m_LRMSAbsLayerJobId.c_str());
          printf("\tLRMSJobId             = [%s]\n", m_LRMSJobId.c_str());
          printf("\tWorkingDirectory      = [%s]\n", m_workingDirectory.c_str());
   	}
}

//______________________________________________________________________________
void soapProxy::JobInfo::getStatusList(vector<soapProxy::Status>& target) const
{
//   for(vector<soapProxy::Status*>::const_iterator it=m_statusList.begin();
//       it != m_statusList.end();
//       ++it)
//       {
// 	target.push_back( soapProxy::Status((*it)) );
//       }
  target = m_statusList;
}


//______________________________________________________________________________
void soapProxy::JobInfo::getLastCommandList(vector<soapProxy::Command>& target) const
{
//   for(vector<soapProxy::Command*>::const_iterator it=m_lastCommandList.begin();
//       it != m_lastCommandList.end();
//       ++it)
//       {
// 	target.push_back( soapProxy::Command(*(*it)) );
//       }
  target = m_lastCommandList;
}

