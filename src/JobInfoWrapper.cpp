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


#include "glite/ce/cream-client-api-c/JobInfoWrapper.h"


using namespace glite::ce::cream_client_api::soap_proxy;

//______________________________________________________________________________
void JobInfoWrapper::reset( void ) throw()
{
    delete jobId; jobId = 0;
    delete fatherJobId; fatherJobId = 0;
    
  std::vector<CREAMTYPES__JobId*>::iterator jit;
  for(jit=this->childJobId.begin(); jit != this->childJobId.end(); ++jit)
    delete( *jit );
  childJobId.clear();
  
  delete JDL; JDL = 0;
  delete lease; lease = 0;
  
  std::vector<CREAMTYPES__Command*>::const_iterator it;
  for(it = this->lastCommand.begin(); it != this->lastCommand.end(); ++it)
    delete( (JobCommandWrapper*)*it );
  lastCommand.clear();

  std::vector<CREAMTYPES__Status*>::const_iterator sit;
  for(sit = status.begin(); sit != status.end(); ++sit)
    delete( (JobStatusWrapper*)*sit );
  status.clear();
  
}

//______________________________________________________________________________
void JobInfoWrapper::set( const CREAMTYPES__JobInfo* anInfo) throw() 
{           
    if(anInfo->jobId)
        jobId = new JobIdWrapper( anInfo->jobId );
    else
        jobId = 0;
    
    if(anInfo->fatherJobId)
        fatherJobId = new JobIdWrapper( anInfo->fatherJobId );
    else
        fatherJobId = 0;
    
    std::vector<CREAMTYPES__JobId*>::const_iterator jit = anInfo->childJobId.begin();
    for( ; jit != anInfo->childJobId.end(); ++jit) {
        childJobId.push_back( new JobIdWrapper( *jit ));
    }
      
    childJobId            = anInfo->childJobId;
    GridJobId             = anInfo->GridJobId;
    LRMSAbsLayerJobId     = anInfo->LRMSAbsLayerJobId;
    LRMSJobId             = anInfo->LRMSJobId;
    delegationProxyId     = anInfo->delegationProxyId;
    delegationProxyInfo   = anInfo->delegationProxyInfo;
    workerNode            = anInfo->workerNode;
    localUser             = anInfo->localUser;
    workingDirectory      = anInfo->workingDirectory;
    CREAMInputSandboxURI  = anInfo->CREAMInputSandboxURI;
    CREAMOutputSandboxURI = anInfo->CREAMOutputSandboxURI;
  
    if(anInfo->JDL)
        JDL = new std::string( *anInfo->JDL );
    else
        JDL = 0;
  
  this->type = anInfo->type;
  
  if(anInfo->lease) {
    this->lease = new CREAMTYPES__Lease();
    this->lease->leaseId = anInfo->lease->leaseId;
    this->lease->leaseTime = anInfo->lease->leaseTime;
  } else {
    this->lease = NULL;
  }
  
  std::vector<CREAMTYPES__Status*>::const_iterator sit;
  for(sit = anInfo->status.begin(); sit != anInfo->status.end(); ++sit)
    this->status.push_back( new JobStatusWrapper( *sit ));
  
  std::vector<CREAMTYPES__Command*>::const_iterator it;
  for(it = anInfo->lastCommand.begin(); it != anInfo->lastCommand.end(); ++it)
    this->lastCommand.push_back( new JobCommandWrapper( *it ) );
}

//______________________________________________________________________________
void JobInfoWrapper::getStatus( std::vector<JobStatusWrapper>& target ) const
{
  std::vector<CREAMTYPES__Status*>::const_iterator sit;
  for(sit=status.begin(); sit != status.end(); ++sit)
    {
      target.push_back( JobStatusWrapper( *sit ) );
    }
}

//______________________________________________________________________________
void JobInfoWrapper::getCommand( std::vector<JobCommandWrapper>& target ) const
{
  std::vector<CREAMTYPES__Command*>::const_iterator cit;
  for(cit=lastCommand.begin(); cit != lastCommand.end(); ++cit)
    {
      target.push_back( JobCommandWrapper( *cit ) );
    }
}
