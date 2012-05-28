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
#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBSTATUSWRAPPER_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBSTATUSWRAPPER_

#include "glite/ce/cream-client-api-c/cream_client_soapH.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"

#include "glite/ce/cream-client-api-c/JobIdWrapper.h"

#include <string>
#include <vector>

namespace glite {
namespace ce {
namespace cream_client_api {
namespace soap_proxy {
	
  /// Wrapper class for the job's status
  /**
     This class wraps few information about job's status and is used by the JobStatus operation as output. 
     See CreamProxyFactory for more details
     about the JobStatus operation.\n

     The user is not supposed to build objects of this class, even if he/she can. 
     It is conceived only to report results to the user. Objects of this class are created and filled 
     by the AbsCreamProxy::execute() method as result of the invocation of the remote 
     CREAM CE operation JobStatus, and the user can retrieve the information stored in it with the getter methods (see below).

     \see CreamProxyFactory
  */
  class JobStatusWrapper : public CREAMTYPES__Status
    {
      
      friend class JobInfoWrapper;
      //friend class std::vector<typename T> ;
      friend class std::vector<JobStatusWrapper>;
      friend class CreamProxy_Status;
      friend class processorStatusResult;

      //____________________________________________________________________
      void reset( void ) throw()
        {
	  delete jobId; jobId = 0;
	  delete exitCode; exitCode = 0;
	  delete failureReason; failureReason = 0;
	  delete description; description = 0;
        }
      
      //____________________________________________________________________
      void set( const CREAMTYPES__Status* aStatus ) throw();
      
    protected:
      
      //____________________________________________________________________
      JobStatusWrapper( const JobIdWrapper& aJob, 
			const std::string& name,
			const time_t timestamp, 
			const std::string& exitCode,
			const std::string& failureReason,
			const std::string& description) throw();
      
      /**
       *
       * CTOR FROM A PARENT OBJECT
       *
       */
      JobStatusWrapper( const CREAMTYPES__Status* aStatus ) throw() 
	{ 
	  this->set( aStatus ); 
	} 
      
    public:

      JobStatusWrapper( ) throw ()
        {
	  jobId = 0;
	  exitCode = 0;
	  failureReason = 0;
	  description = 0;
        }

      JobStatusWrapper( const JobStatusWrapper& aStatus ) throw() : CREAMTYPES__Status()
	{
	  this->set( &aStatus );
	}

      JobStatusWrapper& operator=( const JobStatusWrapper& aStatus) throw()
	{
	  if(this != &aStatus ) {
	    this->reset();
	    this->set( &aStatus );
	  }
	  
	  return *this;
	}

      virtual ~JobStatusWrapper( ) throw()
	{
	  this->reset();
	}

      /**
	 The result of JobStatus for one particular job of the collection sent by the client to CREAM
      */
      enum RESULT {
	OK,                   /**< The JobStatus operation is successfull */
	JOBUNKNOWN,           /**< The remote CREAM CE doesn't know the job ID asked by the client */
	JOBSTATUSINVALID,     /**< The status name(s) defined in the job filter of the request is(are) wrong */
	DELEGATIONIDMISMATCH, /**< The delegation identifier defined in the job filter of the request is wrong */
	DATEMISMATCH,         /**< The date(s) defined in the job filter request is(are) wrong */
	GENERIC,              /**< Another kind a failure occurred at server side */
	LEASEIDMISMATCH       /**< The lease identifier defined in the job filter of the request is wrong */
      };

      /**
	 Return the CREAM Job Identifier of the job the client asked the status of.
	 
	 \return std::string
      */
      std::string getCreamJobID() const { if(this->jobId) return this->jobId->id; else return ""; }
      
      /**
	 Return the current job's status name in a human readable form (see also job_statuses.h header for valid status names)
	 
	 \return std::string
      */
      std::string getStatusName() const { return this->name; }
      
      /**
	 Return the time (UTC) of the last status change

	 \return time_t
      */
      time_t      getTimestamp() const { return this->timestamp; }
      
      /**
	 For terminated jobs (see job_statuses.h for "terminated" definition), return the exit code of the job

	 \return std::string
      */
      std::string getExitCode() const { if(this->exitCode) return *this->exitCode; else return ""; }
      
      /**
	 For failed jobs (see job_statuses.h for "terminated" definition), return the failure reason

	 \return std::string
      */
      std::string getFailureReason() const { if(this->failureReason) return *this->failureReason; else return ""; }
      
      /**
	 Not in use for now
	 
	 \return std::string
      */
      std::string getDescription() const { if(this->description) return *this->description; else return ""; }
      
    };
}
}
}
}

#endif
