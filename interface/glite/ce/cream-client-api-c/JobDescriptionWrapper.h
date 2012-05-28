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
#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBDESCRIPTIONWRAPPER_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBDESCRIPTIONWRAPPER_

//#include "CREAM_CLIENTH.h"
//#include "CREAM_CLIENTStub.h"

#include "glite/ce/cream-client-api-c/cream_client_soapH.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"

#include <string>

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {
	/// A class to wrap all the job-related information
	/**
	   The JobDescriptionWrapper class wraps all the information related to a job to be submitted to a 
	   CREAM CE. It is conceived only to build objects that will be arguments for the 
	   CreamProxyFactory::make_CreamProxyRegister static method.
	*/
	//_________________________________________________________________________________
	class JobDescriptionWrapper : public CREAMTYPES__JobDescription {
	  
	protected:
	  JobDescriptionWrapper( const JobDescriptionWrapper& ) throw() : CREAMTYPES__JobDescription() {} // NOT USE COPYCTOR
	  JobDescriptionWrapper& operator=( const JobDescriptionWrapper& ) throw() { return *this; } // DO NOT COPY

	public:

	  /**
	     Class constructor.
	     \param JDL A string containing the JDL describing the user's job
	     \param DelegationId The identifier of a previously delegated proxy
	     \param DelegationProxy Not in use now (for future developments); just laeve it empty
	     \param LeaseID The identifier of a pre-negotiated lease time (see CREAM documentation for more detail about lease time). The user should not be interested to it unless he/she does not have to make a job control system like ICE
	     \param Autostart The user should set it to true if he/she want the job be automatically started.
	     \param JobDescriptionID const std::string& Job Identifier. This string is useful when the user is registering more than one job and the output of the AbsCreamProxy::execute(...) contains a complex structure containing information for multiple jobs whose identifier is the JobDescriptionID
	   */
	  JobDescriptionWrapper(const std::string& JDL,
			        const std::string& DelegationId,
			        const std::string& DelegationProxy,
			        const std::string& LeaseId,
			        const bool         Autostart,
			        const std::string& JobDescriptionID) throw();
	    
	    /**
	       Class Destructor
	     */
	    virtual ~JobDescriptionWrapper( ) throw();
	    
	    
	    /*
	     *  GETTER Methods
	     */

	    /**
	       Return the JDL describing the Job

	       \return std::string
	    */
	    std::string getJDL( void ) const { return JDL;  }

	    /**
	       Return the Delegation ID the job will be submitted with

	       \return std::string
	    */
	    std::string getDelegationID( void ) const { if(delegationId) return *delegationId; else return ""; }
	    
	    /**
	       Return the Delegation Proxy identifier that will be used to submit the job

	       \return std::string
	    */
	    std::string getDelegationProxy( void ) const { if(delegationProxy) return *delegationProxy; else return "";}

	    /**
	       Return the Lease identifier that will be used to submit the job

	       \return std::string
	    */
	    std::string getLeaseID( void ) const { if(leaseId) return *leaseId; else return ""; }
	    
	    /**
	       Return the Autostart flag
	       
	       \return bool
	    */
	    bool        getAutostart( void ) const { return autoStart; }

	    /**
	       Return the Job Description identifier
	       
	       \return std::string
	    */
	    std::string getJobDescriptionId( void ) const { if(jobDescriptionId) return *jobDescriptionId; else return ""; }
	    
	};
	
      }
    }
  }
}

#endif
