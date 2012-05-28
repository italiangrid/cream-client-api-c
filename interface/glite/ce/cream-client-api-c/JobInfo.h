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

#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBINFO_H_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBINFO_H_

//#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"
#include "glite/ce/cream-client-api-c/Status.h"
#include "glite/ce/cream-client-api-c/Command.h"
#include<vector>
#include<string>
#include<ctime>

class creamtypes__JobInfo;

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {


        /// A wrapper class for Job Information
	/**
		This class wraps the SOAP data structures deserialized by gSOAP runtime when
		CREAM returns information about a job.\n
		Not all information returned by the methods of this
		class is available; it depends whether the user is recognized as admin of the CREAM-based CE or not.
	*/
	class JobInfo {

	   std::string           m_CREAMJobId;
	   std::string           m_GridJobId;
	   std::string           m_LRMSAbsLayerJobId;
	   std::string           m_LRMSJobId;
	   std::string           m_proxyDelegationId;
	   std::string           m_workerNode;
	   std::string           m_localUser;
	   time_t                m_leaseTime;
	   std::string           m_workingDirectory;
	   std::string           m_CREAMInputSandboxURI;
	   std::string           m_CREAMOutputSandboxURI;
	   std::string           m_JDL;
	   std::string           m_proxyInfo;
	   std::vector<Status>   m_statusList;
	   std::vector<Command>  m_lastCommandList;


	  public:
	   /// Default constructor
	   /**
	      The user is not supposed to explicitly build a JobInfo object using this 
	      constructor.
	   */
	   JobInfo(creamtypes__JobInfo*);
	   /// Default destructor
	   ~JobInfo();
	   /// Prints on STDOUT a human readable representation of the job information
	   /**
		\param outputLevel An integer defining the level of verbosity. Considered value are 0, 1 or 2
	   */
	   void print(const int outputLevel) const;
	   /// Returns the CREAM job identifier
	   std::string getCreamJobID( void ) const { return m_CREAMJobId; }
	   /// Returns the Grid WMS job identifier
	   std::string getGridJobId( void ) const { return m_GridJobId; }
	   /// Returns the job identifier wrt underlying batch system abstraction layer (i.e. BLAH)
	   std::string getLRMSAbsLayerJobId( void ) const { return m_LRMSAbsLayerJobId; }
	   /// Returns the job identifier of the underlying physical batch system (e.g. the PBS JobID/LSF JobID/...)
	   std::string getLRMSJobId( void ) const { return m_LRMSJobId; }
	   /// Returns the proxy delegation identifier
	   std::string getProxyDelegationId( void ) const { return m_proxyDelegationId; }
	   /// Returns the node name where the job is running/was executed
	   std::string getWorkerNode( void ) const { return m_workerNode; }
	   /// Returns the local user ID which is executing/executed the job
	   std::string getLocalUser( void ) const { return m_localUser; }
	   /// Returns the Lease time of the job
	   time_t      getLeaseTime( void ) const { return m_leaseTime; }
	   /// Returns the working directory of the running job on the CREAM CE service. Please note that this is not the workdir on the worker node
	   std::string getWorkingDirectory( void ) const { return m_workingDirectory; }
	   /// Returns the URI address of the InputSandbox
	   std::string getCREAMInputSandboxURI( void ) const { return m_CREAMInputSandboxURI; }
	   /// Returns the URI address of the OutputSandbox
	   std::string getCREAMOutputSandboxURI( void ) const { return m_CREAMOutputSandboxURI; }
	   /// Returns the JDL describing the job
	   std::string getJDL( void ) const { return m_JDL; }
	   /// Fills the argument with all job status changes occurred for the job
	   void        getStatusList(std::vector<Status>&) const;
	   /// Fills the argument with all command issued on the job
	   void        getLastCommandList(std::vector<Command>&) const;
	};

      }
    }
  }
}

#endif
