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

#ifndef _GLITE_CE_CREAM_CLIENT_API_STATES_H_
#define _GLITE_CE_CREAM_CLIENT_API_STATES_H_

#include <string>
#include <map>

namespace glite {
  namespace ce {
    namespace cream_client_api {
      /**
      	This namespace is used to keep all possible job states. It also provides some methods
	to manipulate states.
      */
      namespace job_statuses {
	
	/**
		Enumerates all states accepted for a Job in the CREAM environment
	*/
	enum job_status {

	  REGISTERED = 0 ,
	  PENDING        ,
	  IDLE           ,
	  RUNNING        ,
	  REALLY_RUNNING ,
	  CANCELLED      ,
	  HELD           ,
	  DONE_OK        ,
	  DONE_FAILED    ,
	  PURGED         ,
	  ABORTED        ,
	  UNKNOWN        ,
	  NA
	};
	
	/**
		This array is useful to obtain the string representation of a status
		by its number (enumerated in job_status)
	*/
	extern std::string job_status_str[];
	/* = {
	  "REGISTERED",
	  "PENDING",
	  "IDLE",
	  "RUNNING",
	  "CANCELLED",
	  "HELD",
	  "ABORTED",
	  "DONE-OK",
	  "DONE-FAILED",
	  "UNKNOWN",
	  "PURGED",
	  "NA"
	};*/
	
	//	extern std::map<std::string, int> job_status_map;

	/// Retrieve the number corrensponding to a string status representation
	/**
		This method converts a string-status in its corresponding number
		as defined in the job_status enum
		\param status The string representation of the status
		\return The status number corresponding to the status specified as argument
	*/
	inline job_status getStatusNum(const std::string& status) {
	  
	  int j=0;
	  while(std::string(job_status_str[j]) != std::string("")) {
	    if(status == job_status_str[j]) return (job_status)j;
	    j++;
	  }
	  return NA;
	};
	
	
	//______________________________________________________________________________
	/// Checks is a job is finished
	/**
	   This method checks if a job is finished or not
	   \param status The status to check
	   \return True if the job is in a terminal state (CANCELLED, ABORTED, DONE-OK, DONE-FAILED), False otherwise
	*/
	inline bool isFinished(const job_status status)
	{
	  return (status == job_statuses::CANCELLED) ||
	    (status == job_statuses::ABORTED) ||
	    (status == job_statuses::DONE_OK) ||
	    (status == job_statuses::DONE_FAILED);
	}

	//______________________________________________________________________________
	/// Checks if a job is failed
	/**
	   This method checks if a job is terminated in an unsuccesful way
	   \param status The status to check
	   \return True if the job is in a unsuccesful terminal state (ABORTED or DONE-FAILED), False otherwise
	*/
	inline bool isFailed(const job_status& status)
	{
	  return (status == job_statuses::DONE_FAILED) ||
	    (status == job_statuses::ABORTED) ;
	}

      } // job_statuses
    } // cream_client_api
  } // ce
}; // glite

#endif

