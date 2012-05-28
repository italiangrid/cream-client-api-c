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

#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_CPF_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_CPF_

#include <list>
#include <string>
#include <utility>
#include <map>

#include "glite/ce/cream-client-api-c/CreamProxy_Impl.h"
#include "glite/ce/cream-client-api-c/JobFilterWrapper.h"
#include "glite/ce/cream-client-api-c/ResultWrapper.h"
#include "glite/ce/cream-client-api-c/ServiceInfoWrapper.h"
#include "glite/ce/cream-client-api-c/JobIdWrapper.h"

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {
	
	/// A Factory Class to properly create an AbsCreamProxy instance
	/**
	   CreamProxyFactory creates for the user the proper instance of AbsCreamProxy to interact with
	   a CREAM CE Web Service.\n AbsCreamProxy has several 'personalities': one for the 
	   JobRegister operation, another one for the JobList operation, and so on... Each personality is, in practice, 
	   a child class that implements a pure virtual method execute() of AbsCreamProxy class. AbsCreamProxy is not
	   instantiable because it is an abstract class (it has the execute() pure virtual method).\n
	   The child classes have the constructors protected; only CreamProxyFactory is allowed 
	   to invoke the constructor methods of the child classes and return the created 
	   objects to the user; he/she may invoke on them the execute() method to communicate with the remote CREAM web
	   service.
	   
	   \see AbsCreamProxy

	*/
	class CreamProxyFactory 
	{
	  CreamProxyFactory() throw() {}
	  CreamProxyFactory( const CreamProxyFactory& ) throw() {}
	  ~CreamProxyFactory() throw() {}

	public:

	  /**
	     Creates an AbsCreamProxy's instance able to perform the JobRegister operation to the remote CREAM CE 
	     Web Service.\n
	     Please refer to the CREAM service documentation for the details about the JobRegister operation.\n
	     The user can use the instance returned by this method, to register one or more jobs in one shot.\n
	     In order to register job(s) the user must before prepare a list of JobDescriptionWrapper objects 
	     (one for each JDL). The data type AbsCreamProxy::RegisterArrayRequest is an alias (typedef) 
	     for std::list< JobDescriptionWrapper *>. So the user should take a look at the JobDescriptionWrapper 
	     documentation to know how to prepare a collection of JobDescriptionWrapper objects from his/her JDLs,
	     then he/she has to put the pointers into an
	     std::list<JobDescrptionWrapper*> and pass a pointer to it as first (input) argument of
	     the static method CreamProxyFactory::make_CreamProxyRegister.
	     
	     The output of the JobRegister operation is put into the second argument. Its type is a 
	     <b>std::map<std::string, boost::tuple<JobIdWrapper::RESULT, JobIdWrapper, std::string> ></b>. 
	     The key of this map
	     is a JobDescriptionID (see JobIdWrapper for its meaning) identifying each job inside 
	     a collection of jobs.
	     The value corresponding to each key of this map is a tuple composed by:
	     - The result of the JobRegsiter operation for the job identified by the current key, i.e. a variable of type JobIdWrapper::RESULT
	     - An object JobIdWrapper that contains information about the registration information of the job 
	     identified by the current key, 
	     - A string containing the error message if the first element of the tuple is NOT JobIdWrapper::OK, i.e. if the registration operation is failed.
	     
	     Please refer to the boost tuple documentation (http://www.boost.org) to know how to get access to the
	     pieces of the tuple structure.

	     \see JobDescriptionWrapper
	     \see JobIdWrapper
	     \param param1 An std::list of pointers to JobDescriptionWrapper objects
	     \param param2 A complex structure that contains the results of the registration of multiple jobs
	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response
	  */
	  static AbsCreamProxy* make_CreamProxyRegister(const AbsCreamProxy::RegisterArrayRequest* param1, 
							AbsCreamProxy::RegisterArrayResult* param2, 
							const int timeout) throw()
	  {
	    return new CreamProxy_Register( param1, param2, timeout );
	  }
	  
	  /**
	     Creates an AbsCreamProxy's instance able to perform the JobInfo operation to the remote 
	     CREAM CE Web Service.

	     \param param1 A JobFilterWrapper object that contains the jobs the JobInfo should 
	     process and a filter to specifies the conditions the jobs should satisfy 
	     in order to be processed
	     
	     \param param2 A complex map; the keys of the map are the job description IDs 
	     (those ones used to register the jobs)
	     and the values are boost::tuple. The single tuple is structured as:

	     - JobInfoWrapper::RESULT indicating if the operation for the job identified by the 
	     corresponding key is successfull
	     or not
	     - JobInfoWrapper The class wrapping the complex result (for a single job) of the JobInfo operation
	     - A string that is not empty if the first field of this tuple is not JobInfoWrapper::OK;
	     it represents the human readable description of the failure.

	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response
	     
	     \see JobInfoWrapper
	     \see JobFilterWrapper
	  */
	  static AbsCreamProxy* make_CreamProxyInfo(const JobFilterWrapper* param1, 
						    AbsCreamProxy::InfoArrayResult* param2, 
						    const int timeout) throw() 
	  {
	    return new CreamProxy_Info(param1, param2, timeout);
	  }

	  /**
	     Creates an AbsCreamProxy's instance able to perform the JobStart operation to the remote 
	     CREAM CE Web Service.

	     \param param1 A JobFilterWrapper object that contains the jobs that should be started and a filter that
	     specifies the conditions the jobs must satisfy in order to be started.

	     \param param2 A ResultWrapper object that contains the results of the JobStart for each job (please see the
	     ResultWrapper documentation).
	    
	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response
	     
	     \see ResultWrapper
	     \see JobFilterWrapper
	  */
	  static AbsCreamProxy* make_CreamProxyStart(const  JobFilterWrapper* param1, 
									ResultWrapper* param2, 
									const int timeout) throw()
	  {
	    return new CreamProxy_Start( param1, param2, timeout );
	  }
	  
	  /**
	     Creates an AbsCreamProxy's instance able to perform the JobStatus operation to the remote 
	     CREAM CE Web Service; in other words, it is needed to query the job's states and some other few 
	     jobs's information.

	     \param param1 A pointer to a JobFilterWrapper object that contains the jobs the user wants to 
	     query and a filter that specifies the conditions the jobs should satisfy in order to be queried. 
	     See the JobFilterWrapper documentaton to know how to create this filter.

	     \param param2 A pointer to an AbsCreamProxy::StatusArrayResult object;
	     AbsCreamProxy::StatusArrayResult is a typedef for a complex structure 
	     std::map< std::string, boost::tuple<JobStatusWrapper::RESULT, JobStatusWrapper, std::string> >. 
	     Each key's content of the map is the Cream Job identifier; the corresponding value is a boost:tuple of three elements:

	     - The first element of the tuple reports the operation result, whose code is specified by the JobStatusWrapper::RESULT
	     - The second element is a JobStatusWrapper object (see its documentation to know how to extract the relevant information from it). It also contains a replication of the Cream Job ID already contained in the key.
	     - The third element is the error reason (in a human readable form); this string is non-empty if the first element was different than JobStatusWrapper::OK. 

	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response

	     See the JobStatusWrapper documentation for more details.
	     
	     \see JobStatusWrapper
	     \see JobFilterWrapper
	  */
	  static AbsCreamProxy* make_CreamProxyStatus(const  JobFilterWrapper* param1, 
						      AbsCreamProxy::StatusArrayResult* param2, 
						      const int timeout) throw()
	  {
	    return new CreamProxy_Status( param1, param2, timeout );
	  }
	  
	  /**
	     Creates an AbsCreamProxy's instance able to perform the setLease operation to the 
	     remote CREAM CE Web Service.

	     \param param1 A couple of Lease identifier string and lease time (number of seconds since the unix 'epoch') choosen by the user. The identifier can be used successively to register jobs
	     \param param2 The negotiated lease: a couple of Lease identifier and lease time; the 
	     negotiation is needed because the CREAM Web Service could decide for some reason 
	     to actualy set the lease time to a different value than that one proposed by the client
	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response
	  */
	  static AbsCreamProxy* make_CreamProxyLease(const std::pair<std::string, time_t>& param1, 
						     std::pair<std::string, time_t>* param2, 
						     const int timeout) throw() 
	  {
	    return new CreamProxy_Lease( param1, param2, timeout );
	  }

	  /**
	     Creates an AbsCreamProxy's instance able to perform the LeaseInfo operation to the remote 
	     CREAM CE Web Service
	     \param param1 The lease identifier the client is asking the time of
	     \param param2 The couple of lease identifier and lease time that will contain the 
	     server's response
	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response
	  */
	  static AbsCreamProxy* make_CreamProxyLeaseInfo(const std::string& param1, 
							 std::pair<std::string, time_t>* param2, 
							 const int timeout) throw()
          {
            return new CreamProxy_LeaseInfo( param1, param2, timeout );
          }

	  /**
	     Creates an AbsCreamProxy's instance able to perform the JobSuspend operation to the remote 
	     CREAM CE Web Service

	     \param param1 A JobFilterWrapper object that contains the jobs the user wants to suspend 
	     and a filter that specifies the conditions the jobs must satisfy in order to be suspended.

	     \param param2 A ResultWrapper object that contains the results of the JobSuspend. 
	    
	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response
	     
	     \see ResultWrapper for more details.

	  */
	  static AbsCreamProxy* make_CreamProxySuspend(const  JobFilterWrapper* param1, 
						       ResultWrapper* param2, 
						       const int timeout) throw() 
	  {
	    return new CreamProxy_Suspend( param1, param2, timeout );
	  }

	  /**
	     Creates an AbsCreamProxy's instance able to perform the JobResume operation to the remote 
	     CREAM CE Web Service

	     \param param1 A JobFilterWrapper object that contains the jobs the user wants to resume 
	     and a filter that specifies the conditions the jobs must satisfy in order to be resumed.

	     \param param2 A ResultWrapper object that contains the results of the JobResume. 
	    
	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response
	     
	     \see ResultWrapper for more details.
	  */
	  static AbsCreamProxy* make_CreamProxyResume(const  JobFilterWrapper* param1, 
						      ResultWrapper* param2, 
						      const int timeout) throw()
	  {
	    return new CreamProxy_Resume( param1, param2, timeout );
	  }

	  /**
	     Creates an AbsCreamProxy's instance able to perform the JobCancel operation to the remote 
	     CREAM CE Web Service

	     \param param1 A JobFilterWrapper object that contains the jobs the user wants to cancel 
	     and a filter that specifies the conditions the jobs must satisfy in order to be cancelled.

	     \param param2 A ResultWrapper object that contains the results of the JobCancel. 
	    
	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response
	     
	     \see ResultWrapper for more details.
	  */
	  static AbsCreamProxy* make_CreamProxyCancel(const  JobFilterWrapper* param1, 
						      ResultWrapper* param2, 
						      const int timeout) throw()
	  {
	    return new CreamProxy_Cancel( param1, param2, timeout );
	  }

	  /**
	     Creates an AbsCreamProxy's instance able to perform the JobPurge operation to the remote 
	     CREAM CE Web Service

	     \param param1 A JobFilterWrapper object that contains the jobs the user wants to purge 
	     and a filter that specifies the conditions the jobs must satisfy in order to be purged.

	     \param param2 A ResultWrapper object that contains the results of the JobPurge. 
	    
	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response
	     
	     \see ResultWrapper for more details.
	  */
	  static AbsCreamProxy* make_CreamProxyPurge(const  JobFilterWrapper* param1, 
						     ResultWrapper* param2, 
						     const int timeout) throw()
	  {
	    return new CreamProxy_Purge( param1, param2, timeout );
	  }

	  /**
	     Creates an AbsCreamProxy's instance able to perform the proxy delegation operation to the remote 
	     CREAM CE Web Service

	     \param param1 The delegation identifier to use in successive calls (e.g. JobRegister)
	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response
	  */
	  static AbsCreamProxy* make_CreamProxyDelegate(const std::string& param1, 
							const int timeout) throw()
	  {
	    return new CreamProxy_Delegate( param1, timeout );
	  }

	  /**
	     Creates an AbsCreamProxy's instance able to perform the ServiceInfo operation to the remote 
	     CREAM CE Web Service

	     \param param1 The structure that will receive the CREAM's response and will contain the 
	     service's information.
	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response

	     \see ServiceInfoWrapper
	  */
	  static AbsCreamProxy* make_CreamProxyServiceInfo( ServiceInfoWrapper* param1, 
							    const int verbosity,
							    const int timeout) throw()
          {
            return new CreamProxy_ServiceInfo( param1, verbosity, timeout );
          }

	  /**
	     Creates an AbsCreamProxy's instance able to perform the AcceptNewJobSubmissions 
	     operation to the remote CREAM CE Web Service. This operation enable/disable
	     the possibility to submit jobs to the CE basing on the value of the first parameter

	     \param param1 If true the CREAM Web Service will be accepting job submissions, if false
	     the submission will be disabled

	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response

	  */
	  static AbsCreamProxy* make_CreamProxyAcceptNewJobSubmissions( const bool param1, 
									const int timeout) throw()
          {
            return new CreamProxy_AcceptNewJobSubmissions( param1, timeout );
          }
	  
	  /**
	     Creates an AbsCreamProxy's instance able to perform the JobList operation to the remote 
	     CREAM CE Web Service

	     \param param1 A pointer to a std::vector of jobs that will contain the CREAM CE's response; 
	     the jobs put in the vector by the invocation of the AbsCreamProxy::execute(...) method 
	     are wrapped by JobIdWrapper objects;
	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response

	     \see JobIdWrapper
	  */
	  static AbsCreamProxy* make_CreamProxyList( std::vector<JobIdWrapper>* param1, 
						     const int timeout) throw()
          {
            return new CreamProxy_List( param1, timeout );
          }

	  /**
	     Creates an AbsCreamProxy's instance able to perform the proxy renew operation to the 
	     remote CREAM CE Web Service

	     \param param1 The delegation identifier whose proxy is to renew
	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response

	  */
	  static AbsCreamProxy* make_CreamProxy_ProxyRenew(const std::string& param1, 
							   const int timeout) throw()
          {
            return new CreamProxy_ProxyRenew( param1, timeout );
          }

	  /**
	     Creates an AbsCreamProxy's instance able to perform the Query Event operation to the 
	     remote CREAM CE Web Service

	     \param param1 The delegation identifier whose proxy is to renew
	     \param timeout An integer specifying the maximum time (in seconds) the client must wait before a response

	  */
	  static AbsCreamProxy* make_CreamProxy_QueryEvent(const std::pair<std::string, std::string> range_eventID,
							   const std::pair<time_t, time_t> range_time,
							   const std::string& eventType,
							   const int max_events,
							   const int verbosity,
							   const std::vector<std::pair<std::string, std::string> >& prop,
							   time_t& execTime,
							   std::string& DB_ID,
							   std::list<EventWrapper*>& events, 
							   const int timeout) throw()
          {
            return new CreamProxy_QueryEvent( range_eventID, range_time, eventType, max_events, verbosity, prop, &execTime, &DB_ID, &events, timeout );
          }

	};
/* 	/home/dorigoa/glite/workarea_new/stage/include/glite/ce/cream-client-api-c/CreamProxyFactory.h:395: undefined reference to `glite::ce::cream_client_api::soap_proxy::CreamProxy_QueryEvent::CreamProxy_QueryEvent(std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::pair<long, long>, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int, int, long*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*, std::list<glite::ce::cream_client_api::soap_proxy::EventWrapper, std::allocator<glite::ce::cream_client_api::soap_proxy::EventWrapper> >*, int)' */

      }
      }
      }
      }

#endif
