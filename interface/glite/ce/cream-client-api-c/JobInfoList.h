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
#ifndef __JOBINFOLIST_H__
#define __JOBINFOLIST_H__

//#include "glite/ce/cream-client-api-c/soap_definitions.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"
//#include "glite/ce/cream-client-api-c/AbsJobInfoList.h"
#include <string>
#include <vector>

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {

	class JobInfoList { //: public creamtypes__JobInfoList {//, public AbsJobInfoList {

	  JobInfoList(const JobInfoList& J) {}
	  JobInfoList& operator=(const JobInfoList&) {}

	  std::string         CREAMJobId;
	  std::string         GridJobId;
	  std::string         LRMSAbsLayerJobId;
	  std::string         LRMSJobId;
	  std::string         proxyDelegationId;
	  std::string         workerNode;
	  std::string         localUser;
	  time_t              leaseTime;
	  std::string         workingDirectory;
	  std::string         CREAMInputSandboxURI;
	  std::string         CREAMOutputSandboxURI;
	  std::string         JDL;
	  std::string         proxyInfo;
	  std::vector<Status> statusList;
	  std::vector<Cmd>    lastCommandList;

	public:
	  JobInfoList(creamtypes__JobInfoList*);
	  virtual ~JobInfoList();
	  virtual void print(const int&);
	  virtual void getJobIDS(std::vector<std::string>&);
	  virtual std::string getCreamJobID( void ) const { return CREAMJobId; }
	  virtual std::string getGridJobId( void ) const { return GridJobId; }
	  virtual std::string getLRMSAbsLayerJobId( void ) const { return LRMSAbsLayerJobId; }
	  virtual std::string getLRMSJobId( void ) const { return LRMSJobId; }
	  virtual std::string getProxyDelegationId( void ) const { return proxyDelegationId; }
	  virtual std::string getWorkerNode( void ) const { return workerNode; }
	  virtual std::string getLocalUser( void ) const { return localUser; }
	  virtual time_t      getLeaseTime( void ) const { leaseTime; }
	  virtual std::string getWorkingDirectory( void ) const { return workingDirectory; }
	  virtual std::string getCREAMInputSandboxURI( void ) const { return CREAMInputSandboxURI; }
	  virtual std::string getCREAMOutputSandboxURI( void ) const { return CREAMOutputSandboxURI; }
	  virtual std::string getJDL( void ) const { return JDL; }
	  virtual void        getStatusList(std::vector<Status>&) const;
	  virtual void        getLastCommandList(std::vector<Cmd>&) const;
      }
    }
  }
}

#endif
