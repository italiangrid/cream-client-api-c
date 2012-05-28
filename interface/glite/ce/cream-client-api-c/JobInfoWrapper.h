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

#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBINFOWRAPPER_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBINFOWRAPPER_

//#include "CREAM_CLIENTH.h"
//#include "CREAM_CLIENTStub.h"

#include "glite/ce/cream-client-api-c/cream_client_soapH.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"

#include "glite/ce/cream-client-api-c/JobCommandWrapper.h"
#include "glite/ce/cream-client-api-c/JobStatusWrapper.h"

#include <string>
#include <utility>

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {
	
	/// A class to wrap the structured information about jobs
	/**
	   The JobInfo operation return a complex structured information that is stored in an object
	   of this class. This class is not conceived to be built/filled by the user; he/she can invoke the 'getter' 
	   methods to retrieve information about the job.\n
	   To be more precise: the user passes an array of JobFilterWrapper objects 
	   to the CreamProxyFactory::make_CreamProxyInfo method, and after the invocation of AbsCreamProxy::execute(...) method, 
	   these JobFilterWrapper objects are filled with the requested information, accessible through the getter methods.

	   \see CreamProxyFactory::make_CreamProxyInfo(...)
	*/
	class JobInfoWrapper : public CREAMTYPES__JobInfo
	{

	  friend class processorInfoResult;
	  //friend class CreamProxy_Info;

            void reset( void ) throw();
            void set( const CREAMTYPES__JobInfo* anInfo) throw();
	    
	    JobInfoWrapper( const CREAMTYPES__JobInfo* anInfo ) throw() {
	      this->set( anInfo );
	    }
	    
            
            
            
	    
	public:            
            enum RESULT {
	      OK,                    /**< The JobInfo is successfull */
	      JOBUNKNOWN,            /**< The job asked for Info is not existing on the remote CREAM CE */
	      JOBSTATUSINVALID,      /**< The job status specified as filter is not recognized by CREAM */
	      DELEGATIONIDMISMATCH,  /**< The deleg. proxy identifier specified by the user as filter is not recognized by CREAM */
	      DATEMISMATCH,          /**< The date specified by the user as filter is not valid */
	      LEASEIDMISMATCH,       /**< The lease identifier specified by the user as filter is not recognized by CREAM */
	      GENERIC                /**< Another kind of error */
            };
            
	    /**
	       Simple class costructor. It is needed to put objects of this class into STL containers
	    */
            JobInfoWrapper() throw ()                {
                this->jobId       = NULL;
                this->fatherJobId = NULL;
                this->JDL         = NULL;
                this->lease       = NULL;                
	    }
            
	    /**
	       Copy constructor
	    */
	    JobInfoWrapper( const JobInfoWrapper& anInfo ) throw() : CREAMTYPES__JobInfo() {
	      this->set( (const CREAMTYPES__JobInfo*)&anInfo );
	    }
	    
	    /**
	       Copy assignment
	    */
	    JobInfoWrapper& operator=( const JobInfoWrapper& anInfo) throw()
	      {
                this->reset();
                this->set( (const CREAMTYPES__JobInfo*)&anInfo );
                return *this;
	      }
	    
	    /**
	       Class destructor
	    */
            virtual ~JobInfoWrapper( ) throw() {
                this->reset();
	    }
            


	  /**************************************************************************
	   * GETTER METHODS
	   *************************************************************************/
	    
	    /**
	       Returns the local Cream Job ID
	    */
	    std::string getCreamJobID() const { if(jobId) return jobId->id; else return ""; }

	    /**
	       Returns the CREAM URL the job comes from
	    */
	    std::string getCreamURL() const { if(jobId) return jobId->creamURL; else return "";}
	    
	    /**
	       Returns the grid Job ID related to this job (if it has been submitted by the WMS, otherwise returns an empty string)
	    */
	    std::string getGridJobId() const { return GridJobId; }
	    
	    /**
	       Returns the job ID of the BLAH layer
	    */
	    std::string getLRMSAbsLayerJobId() const { return LRMSAbsLayerJobId; }

	    /**
	       Returns the batch system's (PBS, LSF, ...) job ID
	    */
	    std::string getLRMSJobId() const { return LRMSJobId; }

	    /**
	       Returns the delegation proxy identifier (that one the job has been submitted with, see JobDescriptionWrapper)
	    */
	    std::string getDelegationProxyId() const { return delegationProxyId; }
	    
	    /**
	       Returns information about the delegated proxy
	    */
	    std::string getDelegationProxyInfo() const { return delegationProxyInfo; }

	    /**
	       Returns the worker node name where the job has been dispatched 
	    */
	    std::string getWorkerNode() const { return workerNode; }

	    /**
	       Returns the local unix username that will run the job on the worker node
	    */
	    std::string getLocalUser() const { return localUser; }

	    /**
	       Returns the working directory of the job
	    */
	    std::string getWorkingDirectory() const { return workingDirectory; }

	    /**
	       Returns the URI where the input sandbox is
	    */
	    std::string getCreamISBURI() const { return CREAMInputSandboxURI; }

	    /**
	       Returns the URI where the output sandbox will be put
	    */
	    std::string getCreamOSBURI() const { return CREAMOutputSandboxURI; }

	    /**
	       Returns the job's JDL
	    */
	    std::string getJDL() const { if(JDL) return *JDL; else return ""; }

	    /**
	       Returns the type of the job (mpi, normal, ...)
	    */
	    std::string getType() const { return type; }
	    
	    /**
	       Returns the identifier of the lease time of the job
	    */
	    std::string getLeaseId() const { if(lease) return lease->leaseId; else return ""; }
	    
	    /**
	       Returns the lease time of the job
	    */
	    time_t getLeaseTime() const { if(lease) return lease->leaseTime; else return 0; }
	    
	    /**
	       Returns the status history of the job (see JobStatusWrapper)
	    */
	    void getStatus( std::vector<JobStatusWrapper>& target ) const;
	    
	    /**
	       Returns the history of the commands (or operation) applied to the job (see JobCommandWrapper)
	    */
	    void getCommand( std::vector<JobCommandWrapper>& target ) const;
	  
	};
      }
    }
  }
}

#endif
