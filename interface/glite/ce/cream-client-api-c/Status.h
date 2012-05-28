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
#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_STATUS_H_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_STATUS_H_

//#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"
#include<string>
#include<ctime>

class creamtypes__Status;

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {
	/// A wrapper class for Job Information
	/**
		This class wraps the SOAP data structures deserialized by gSOAP runtime when
		CREAM returns information about a job.\n
		This class keeps less information than the JobInfo and is used for fast
		queries to CREAM service
	*/
      class Status {

	 friend class CreamProxy;

	 std::string m_name;
	 time_t      m_timestamp;
	 std::string m_exitCode;
	 std::string m_failureReason;
	 std::string m_jobId;

	public:
	 /// Default constructor
	 /**
	    The user is not supposed to explicitly build a Status object using this 
	    constructor.
	 */
	 Status(creamtypes__Status*);
	 /// Default destructor
	 ~Status();
	 /// Returns the status name
	 std::string getStatusName( void ) const { return m_name;}
	 /// Returns the timestamp of the creation of the job
	 time_t      getTimestamp( void ) const { return m_timestamp; }
	 /// Returns the exit code of the job
	 std::string getExitCode( void ) const { return m_exitCode; }
	 /// Returns the job identifier
	 std::string getJobID( void ) const { return m_jobId; }
	 /// Returns the reason of the failure (available only for falied jobs)
	 std::string getFailureReason( void ) const { return m_failureReason; }
	 /// Prints on STDOUT a human readable representation of the job information
	 /**
	    \param outputLevel An integer defining the level of verbosity. Considered value are 0, 1 or 2
	 */
	 void        print( const int outputLevel ) const;
      };

      }
    }
  }
}

#endif
