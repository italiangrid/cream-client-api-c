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
#ifndef GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBIDWRAPPER
#define GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBIDWRAPPER

#include "glite/ce/cream-client-api-c/cream_client_soapH.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"

#include "glite/ce/cream-client-api-c/JobPropertyWrapper.h"

#include <string>
#include <vector>
#include <map>
#include <list>

namespace glite {
namespace ce {
namespace cream_client_api {
namespace soap_proxy {
  
    //________________________________________________________________________

  // /// \class A Class to Wrap the Cream Job ID
  /**
     \class JobIdWrapper
     \brief A Class to Wrap the Cream Job

     This class is a structure containing the Cream Job ID string, the CREAM URL the job has been registered to, and a vector
     of properties, where each property is a couple of strings (name, value), and finally the result of the operation that has been invoked (JobRegister, JobInfo, JobStart, etc...).\n In fact this structure is tipically used as member of complex output of several CREAM remote operations.
  */
    class JobIdWrapper : public CREAMTYPES__JobId {    
            
    friend class JobInfoWrapper;
    friend class JobFilterWrapper;
    friend class JobStatusWrapper;
    friend class ResultWrapper;
    friend class processorRegisterResult;
    friend class processorListResult;

    protected:	
        void clone( const CREAMTYPES__JobId* other ) throw();
        void destroy( void ) throw(); 
	JobIdWrapper( const CREAMTYPES__JobId* other );
       
    public:
        /**
	   Creates a JobIdWrapper object. 
	   
	   \param CreamJobId const std::string& An unique identifier returned by the CREAM CE web service
	   \param CreamURL const std::string& The URL of the CREAM CE web service where this job comes from
	   \param prop const std::vector<JobPropertyWrapper>& A vector of JobPropertyWrapper

	   \see JobPropertyWrapper
         */
        JobIdWrapper( const std::string& CreamJobId, const std::string& CreamURL, const std::vector<JobPropertyWrapper>& prop) throw();
        
        
	/**
	   Simple constructor; this is needed when a JobIdWrapper object must be put in a vector/list or other containers
	*/
        JobIdWrapper( ) throw() 
        {

        }

        /**
	   Copy assignment operator
	*/
        JobIdWrapper& operator=( const JobIdWrapper& aJobId ) throw();
        
        /**
         * Copy Constructor
         */
        JobIdWrapper( const JobIdWrapper& aJob ) throw() ;
        
        /**
         * Class destructor
         */
        virtual ~JobIdWrapper() throw() ;
        
	/**
	   Gets the local Cream Job unique identifier
	   
	   \return std::string
	*/
        std::string getCreamJobID( void ) const { return id; }

	/**
	   Gets the local Cream URL the job has been submitted to

	   \return std::string
	*/
        std::string getCreamURL( void ) const { return creamURL; }

	/**
	  Fill its argument with all couples key-value returned by CREAM as properties of the job's registration (e.g. input sandbox path in the CE, the user should send his Input SandBox to.

	  \param target map<string, string> containing the couples key-value representing the properties
	*/	
        void getProperties( std::map< std::string, std::string >& target );

	/**
	   The types of result of a job operation (JogRegister, JobCancel, etc...)
	*/
	enum RESULT {
	  OK, /**< The operation related to the current Job is succesfull */
	  JOBUNKNOWN, /**< The current Job is unknown to the CREAM CE remote service */
	  JOBSTATUSINVALID, /**< The current Job's status is incompatible with the requested operation */
	  DELEGATIONIDMISMATCH, /**< The delegation ID used for job registration is not recognized by remote CREAM CE service */
	  DATEMISMATCH, /**< The date specified for the operation is not valid */
	  LEASEIDMISMATCH,/**< The Lease ID used for job registration is not recognized by remote CREAM CE service */
	  DELEGATIONPROXYERROR,/**< An error occurred during proxy delegation */
	  GENERIC/**< A generic error */
	};
    };
	  
}
}
}
}

#endif
