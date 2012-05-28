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

#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_RESULTWRAPPER_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_RESULTWRAPPER_

#include "glite/ce/cream-client-api-c/cream_client_soapH.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"

#include <string>
#include <vector>
#include <list>
#include <utility>

#include "glite/ce/cream-client-api-c/JobIdWrapper.h"
#include "glite/ce/cream-client-api-c/ExceptionFactory.h"

namespace glite {
namespace ce {
namespace cream_client_api {
namespace soap_proxy {
    
  /// Wrapper class to collect cumulative information about multiple jobs.
  /**
     When invoking JobStart/JobPurge/JobCancel/JobSuspend/JobResume for multiple jobs, the results are stored
     by the AbsCreamProxy::execute() method into this structure. It contains the list of jobs for which the operation has been
     successfull, those ones that were not existing in the remote CREAM CE service, those ones that were not in the
     specified states, those ones that were not submitted in the specified date, those ones that have not been
     submitted with the specified delegation proxy identifier and those one that have not been submitted with
     the specified lease identifier.\n

     The user is not supposed to fill objects of this class, even if he/she can; he/she can only build 
     blank object that will be filled by the AbsCreamProxy::execute() method. The user can retrieve 
     the information stored using the 'getter' methods.
     
     \see CreamProxyFactory
  */
    class ResultWrapper
    {
       
      friend class CreamProxy_Start;
      friend class CreamProxy_Cancel;
      friend class CreamProxy_Suspend;
      friend class CreamProxy_Resume;
      friend class CreamProxy_Purge;
      
      std::list<std::pair<JobIdWrapper, std::string> > notExistingJobs;
      std::list<std::pair<JobIdWrapper, std::string> > notMatchingStatusJobs;
      std::list<std::pair<JobIdWrapper, std::string> > notMatchingDateJobs;
      std::list<std::pair<JobIdWrapper, std::string> > notMatchingProxyDidJobs;
      std::list<std::pair<JobIdWrapper, std::string> > notMatchingLeaseJobs;
      
      //____________________________________________________________________
      void set(const std::vector<CREAMTYPES__Result * >& results) throw(); 
      
      //____________________________________________________________________________
      void fill(std::list<std::pair<JobIdWrapper, std::string> >& target, 
		const std::list<std::pair<JobIdWrapper, std::string> >& source) 
	const throw();
      
      ResultWrapper(const ResultWrapper&) {}
      ResultWrapper& operator=(const ResultWrapper&) { return *this; }
      
      //____________________________________________________________________
      ResultWrapper(const std::vector<CREAMTYPES__Result * >& results ) 
	throw()	{
	this->set( results );
      } 
      
      //____________________________________________________________________
      ResultWrapper& 
	operator=( const std::vector<CREAMTYPES__Result * >& results ) throw();
     
    public:
      
      //____________________________________________________________________
      /**
	 Class constructor (needed to put this objects into STL container)
      */
      ResultWrapper( ) throw() {}
      
      
      //____________________________________________________________________
      /**
	 Method to get the jobs that were not existing in the remote CREAM CE web service
	 
	 \param target Is filled by this method with the jobs
      */
      void 
	getNotExistingJobs( std::list<std::pair<JobIdWrapper, 
			    std::string> >& target)
	const throw()
	{
	  this->fill( target, notExistingJobs );
	}
      
      //____________________________________________________________________
      /**
	 Method to get the jobs that were not in the status specified by the user

	 \param target Is filled by this method with the jobs
      */
      void 
	getNotMatchingStatusJobs( std::list<std::pair<JobIdWrapper, 
				  std::string> >& target) 
	const throw()
	{
	  this->fill( target, notMatchingStatusJobs );
	}
      
      //____________________________________________________________________
      /**
	 Method to get the jobs that were not submitted in the date specified by the user

	 \param target Is filled by this method with the jobs
      */
      void 
	getNotMatchingDateJobs( std::list<std::pair<JobIdWrapper, 
				std::string> >& target) 
	const throw()
	{
	  this->fill( target, notMatchingDateJobs );
	}
      
      //____________________________________________________________________
      /**
	 Method to get the jobs that were not submitted with the delegation
	 proxy identifier specified by the user

	 \param target Is filled by this method with the jobs
      */
      void 
	getNotMatchingProxyDelegationIdJobs( std::list<std::pair<JobIdWrapper, 
					     std::string> >& target) 
	const throw()
	{
	  this->fill( target, notMatchingProxyDidJobs );
	}
      
      //____________________________________________________________________
      /**
	 Method to get the jobs that were not submitted with the lease
	 identifier specified by the user

	 \param target Is filled by this method with the jobs
      */
      void 
	getNotMatchingLeaseIdJobs( std::list<std::pair<JobIdWrapper, 
				   std::string> >& target) 
	const throw()
	{
	  this->fill( target, notMatchingLeaseJobs );
	}
      
    }; // end ResultWrapper class
    
}
}
}
}

#endif
