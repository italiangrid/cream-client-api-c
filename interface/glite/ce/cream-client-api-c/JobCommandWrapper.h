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
#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBCOMMANDWRAPPER_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBCOMMANDWRAPPER_

#include "glite/ce/cream-client-api-c/cream_client_soapH.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"

#include <string>
#include <ctime>

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {


	/// A wrapper class for the Command SOAP object
	/**
	   Objects of the JobCommandWrapper class are used by JobInfoWrapper as history of the CREAM commands
	   (or operations) issued by the user.
	   Each command has several characteristics as the submission time, scheduling time, completion time etc.
	   Commands may not be executed by CREAM for several reasons (e.g. cannot send a JobCancel to CREAM to cancel a 
	   terminated job); then a command also as a status and a failure reason. When, and only when, a user send a 
	   JobInfo request to CREAM, for each job a history of commands will be returned too.

	   The user is not supposed to build objects of this class, even if he/she can. It is conceived only to report results to the user.
	   
	   Objects of this class are created and filled by the AbsCreamProxy::execute() method as result of the invocation of the remote 
	   CREAM CE operations, and the user can retrieve the information stored in it and returned by CREAM.

	   \see JobInfoWrapper
	*/
	class JobCommandWrapper : public CREAMTYPES__Command
	{
	  
	  friend class JobInfoWrapper;

	  //____________________________________________________________________
	  void reset( void ) throw();

	  //____________________________________________________________________
	  void set( const CREAMTYPES__Command* aCommand ) throw();

	  JobCommandWrapper& operator=(const CREAMTYPES__Command& ) { return *this; }
	  
	protected:

	  //____________________________________________________________________
	  JobCommandWrapper( const CREAMTYPES__Command* aCommand ) {

	    this->set( aCommand );

	  }



	public:

	  /**
	     Class destructor
	  */
	  ~JobCommandWrapper() throw() 
	  {
	    this->reset();
	  }
	  
	  /**
	     Class constructor
	  */
	  JobCommandWrapper( const JobCommandWrapper& aCommand ) : CREAMTYPES__Command()
	  {
	    this->set( &aCommand );
	  }

	  /**
	     Copy assignment operator
	  */
	  JobCommandWrapper& operator=(const JobCommandWrapper& aCommand) 
	  {
	    if(this != &aCommand) {
	      this->reset();
	      this->set( &aCommand );
	    }
	    return *this;
	  }
	  
	  /**
	     Return the CREAM local command identifier

	     \return std::string
	  */
	  std::string getCommandId() const { if(id) return *id; else return ""; }
	  
	  /**
	     Return the Command name

	     \return std::string
	   */
	  std::string getCommandName() const { return name; }

	  /**
	     Return the command category name

	     \return std::string
	  */
	  std::string getCommandCategory() const { return category; }

	  /**
	     Return the command status

	     \return std::string
	  */
	  std::string getCommandStatus() const { return status; }

	  /**
	     Return the command failure reason (if the status is failed, else return an empty string)

	     \return std::string
	  */
	  std::string getCommandFailReason() const { if(failureReason) return *failureReason; else return ""; }
	  
	  /**
	     Return the command creation time

	     \return time_t
	  */
	  time_t getCreationTime() const { if(creationTime) return *creationTime; else return 0; }

	  /**
	     Return the command scheduling time

	     \return time_t
	  */
	  time_t getStartSchedulingTime() const { if(startSchedulingTime) return *startSchedulingTime; else return 0; }

	  /**
	     Return the command processing time

	     \return time_t
	  */
	  time_t getStartProcessingTime() const { if(startProcessingTime) return *startProcessingTime; else return 0; }

	  /**
	     Return the command completion time

	     \return time_t
	  */
	  time_t getExecutionCompletedTime() const { if(executionCompletedTime) return *executionCompletedTime; else return 0; }

	};
	
      }
    }
  }
}

#endif
