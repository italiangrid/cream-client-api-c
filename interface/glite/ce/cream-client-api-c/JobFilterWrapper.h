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
#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBFILTERWRAPPER_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JOBFILTERWRAPPER_

#include "glite/ce/cream-client-api-c/cream_client_soapH.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"

#include "glite/ce/cream-client-api-c/JobIdWrapper.h"

#include <string>
#include <list>
#include <utility>

namespace glite {
namespace ce {
namespace cream_client_api {
namespace soap_proxy {

  /// A wrap class to use as argument of the operations: JobStart, JobCancel, JobPurge, JobResume, JobSuspend, JobInfo, JobStatus
  /**
     The CREAM CE operations JobStart, JobCancel, JobPurge, JobResume, JobSuspend, JobInfo, JobStatus accept one or more jobs
     to process. The JobFilterWrapper class defines the list of jobs to apply the operation to 
     and some conditions that the jobs must satisfy in order to be processed.

     The conditions are: the jobs has been submitted in a particular time range; the jobs must have a status present in a user-defined list; the jobs has been submitted with a particular delegation identifier or lease identifier. See the JobFilterWrapper's constructor to better understand how to define these conditions.
  */
  class JobFilterWrapper : public CREAMTYPES__JobFilter {
    
    void reset( void ) throw();
    
    void set( const CREAMTYPES__JobFilter& aFilter ) throw();
    
    JobFilterWrapper(const JobFilterWrapper&) throw() : CREAMTYPES__JobFilter() {} // NO COPY CTOR
    JobFilterWrapper(const CREAMTYPES__JobFilter&) throw() {} 
    JobFilterWrapper& operator=(const CREAMTYPES__JobFilter&) throw() { return *this; } 
    JobFilterWrapper& operator=(const JobFilterWrapper&) throw() { return *this; } // NO COPY ASSIGNEMENT

    //__________________________________________________________________________
    JobFilterWrapper(const CREAMTYPES__JobFilter* aFilter) throw() 
      {
	this->set( *aFilter );
      }

  public:     
    //__________________________________________________________________________
    /**
       Class constructor. 
       \param jobs  A vector of jobs to apply the operation to (each job is represented by a JobIdWrapper object).
       \param states  The operation will process only jobs that are in one of the states listed in this vector. Each
       status is a string. For valid strings see the header file job_statuses.h .
       \param from  The operation will process only jobs submitted not before "from" (UTC time, number of seconds since unix 'epoch')
       \param to  The operation will process only jobs submitted not after "to" (UTC time, number of seconds since unix 'epoch')
       \param delegId  The operation will process only jobs submitted with this delegation ID. Empty delegation ID string means "all jobs".
       \param leaseId  The operation will process only jobs submitted with this lease ID. Empty lease ID string means "all jobs".
    */
    JobFilterWrapper(const std::vector< JobIdWrapper >& jobs,
		     const std::vector< std::string >& states,
		     const int from, const int to,
		     const std::string& delegId,
		     const std::string& leaseId) throw();
    
    //__________________________________________________________________________
    /**
       Class destructor
    */
    virtual ~JobFilterWrapper() throw() 
      {
	this->reset();
      }
    

  };
  
}
}
}
}

#endif

