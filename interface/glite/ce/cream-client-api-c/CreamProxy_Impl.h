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
#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_CREAMPROXYIMPL_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_CREAMPROXYIMPL_

#include "glite/ce/cream-client-api-c/AbsCreamProxy.h"
#include "glite/ce/cream-client-api-c/JobIdWrapper.h"
#include "glite/ce/cream-client-api-c/EventWrapper.h"
#include "glite/ce/cream-client-api-c/auth_ex.h"

#include <map>
#include <utility>
#include <list>
#include <vector>
#include <string>

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {
	
	class JobDescriptionWrapper;
	class ResultWrapper;
	class JobFilterWrapper;
 	class ServiceInfoWrapper;
	
	class processorStatusResult {

	  AbsCreamProxy::StatusArrayResult* m_target;
	  
	public:
	  /**
	   *
	   * StatusArrayResult = map <string, pair< bool, StatusResult> >
	   * StatusResult      = union...
	   *
	   */
	  processorStatusResult( AbsCreamProxy::StatusArrayResult* target ) 
	    : m_target(target) {}
	  
	  void operator()( const CREAMTYPES__JobStatusResult* jr ) ;
	    
	};
	
	class processorRegisterResult {
	  
	  AbsCreamProxy::RegisterArrayResult* m_target;
	  
	public:
	  
	  /**
	   *
	   * RegisterArrayResult = map <string, pair< bool, RegisterResult> >
	   * RegisterResult      = union...
	   *
	   */
	  processorRegisterResult( AbsCreamProxy::RegisterArrayResult* target ) 
	    : m_target(target) {}
	    
	    void operator()( const CREAMTYPES__JobRegisterResult* jr ) ;
	    
	};
	
	class processorInfoResult {
	  
	  AbsCreamProxy::InfoArrayResult* m_target;
	  
	public:
	  
	  /**
	   *
	   * InfoArrayResult = map <string, pair< bool, InfoResult> >
	   * InfoResult      = union...
	   *
	   */
	  processorInfoResult( AbsCreamProxy::InfoArrayResult* target ) 
	    : m_target(target) {}
	    
	    //____________________________________________________________________________
	    void operator()( const CREAMTYPES__JobInfoResult* jr ) ; //  operator()
	    
	};
	
	class processorListResult {
	  
	  std::vector<JobIdWrapper> *m_target;
	  
	public:
	  processorListResult( std::vector<JobIdWrapper>* target ) : m_target( target ) {}
	    
	    void operator()( const CREAMTYPES__JobId* aJob );
	};

	//______________________________________________________________________________
	class CreamProxy_Register : public AbsCreamProxy 
	{
	  
	  const AbsCreamProxy::RegisterArrayRequest* m_jd_list;
	  AbsCreamProxy::RegisterArrayResult* m_target;
	  
	  CreamProxy_Register( const CreamProxy_Register& ) throw() : AbsCreamProxy(30) {}
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_Register( const RegisterArrayRequest*, RegisterArrayResult*, const int timeout = 30 ) throw();
	  
	  
	  
	public:
	  
	  virtual void execute(const std::string& serviceURL, const bool ignore_tag_mismatch = false) 
	    throw(BaseException&,
		  InvalidArgumentException&,
		  GridProxyDelegationException&,
		  JobSubmissionDisabledException&,
		  GenericException&,
		  AuthorizationException&,
		  DelegationException&,
		  InternalException&,
		  ConnectionTimeoutException&,
		  auth_ex&,
		  soap_ex&,
		  soap_runtime_ex&);
	  
	  virtual ~CreamProxy_Register( void ) throw() {}
	  
	};

	//______________________________________________________________________________
	class CreamProxy_QueryEvent : public AbsCreamProxy 
	{
	  
	  //const AbsCreamProxy::RegisterArrayRequest* m_jd_list;
	  //AbsCreamProxy::RegisterArrayResult* m_target;
	  
	  CreamProxy_QueryEvent( const CreamProxy_QueryEvent& ) throw() : AbsCreamProxy(30), m_eventid_range(), m_time_range(), m_event_type(), m_max_events(), m_verbosity() {}
	  
	    //	  const _CREAMTYPES__QueryEventRequest&   m_request;
	  std::list<EventWrapper*>                   *m_target;
	  time_t                                     *m_time_t;
	  std::string                                *m_database_id;
	  std::pair<std::string, std::string>         m_eventid_range;
	  std::pair<time_t, time_t >                  m_time_range;
	  std::string                                 m_event_type;
	  int                                         m_max_events;
	  int                                         m_verbosity;
	  std::vector< std::pair<std::string, std::string> > m_request_prop;

	protected:

	  friend class CreamProxyFactory;

	  CreamProxy_QueryEvent( const std::pair< std::string, std::string> range_eventID,
				 const std::pair<time_t, time_t> range_time,
				 const std::string& eventType,
				 const int max_events,
				 const int verbosity,
				 const std::vector< std::pair<std::string, std::string> >& prop, 
				 time_t*,
				 std::string* DB_ID,
				 std::list<EventWrapper*>*, 
				 const int timeout = 30 ) throw();
	  
	  
	  
	public:
	  
	  virtual void execute(const std::string& serviceURL, const bool ignore_tag_mismatch = false) throw(BaseException&,
								    InvalidArgumentException&,
								    GenericException&,
								    AuthorizationException&,
								    InternalException&,
								    ConnectionTimeoutException&,
								    auth_ex&,
								    soap_ex&,
								    soap_runtime_ex&);
	  
	  virtual ~CreamProxy_QueryEvent( void ) throw() {}
	  
	};
	//______________________________________________________________________________
	class CreamProxy_Info : public AbsCreamProxy 
	{
	  
	  const JobFilterWrapper* m_jobFilter;
	  AbsCreamProxy::InfoArrayResult* m_target;
	  
	  CreamProxy_Info( const CreamProxy_Info& ) throw() : AbsCreamProxy(30) {}
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_Info( const JobFilterWrapper*, InfoArrayResult*, const int timeout = 30 ) throw();
	  
	public:
	  virtual void execute(const std::string& serviceURL, const bool ignore_tag_mismatch = false) throw(BaseException&,
								    InvalidArgumentException&,
								    GridProxyDelegationException&,
								    JobSubmissionDisabledException&,
								    GenericException&,
								    //AuthenticationException&,
								    AuthorizationException&,
								    DelegationException&,
								    InternalException&,
								    ConnectionTimeoutException&,
								    auth_ex&,
								    soap_ex&,
								    soap_runtime_ex&);
	  
	  
	  ~CreamProxy_Info( void ) throw() {}
	};
	
	
	//______________________________________________________________________________
	class CreamProxy_Start : public AbsCreamProxy 
	{
	  
	  CreamProxy_Start( const CreamProxy_Start& ) throw() : AbsCreamProxy(30) {}
	  
	  const JobFilterWrapper *m_jobFilter;
	  ResultWrapper    *m_result;
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_Start( const JobFilterWrapper*, ResultWrapper*, const int timeout = 30 ) throw();
	  
	public:
	  
	  virtual ~CreamProxy_Start( void ) throw() {}
	  
	  virtual void execute(const std::string& serviceURL, const bool ignore_tag_mismatch = false) throw(BaseException&,
								    InvalidArgumentException&,
								    GridProxyDelegationException&,
								    JobSubmissionDisabledException&,
								    GenericException&,
								    //AuthenticationException&,
								    AuthorizationException&,
								    DelegationException&,
								    InternalException&,
								    ConnectionTimeoutException&,
								    auth_ex&,
								    soap_ex&,
							  	    soap_runtime_ex&);
	  
	};
	
	//______________________________________________________________________________
	class CreamProxy_List : public AbsCreamProxy 
	{
	  
	  CreamProxy_List( const CreamProxy_List& ) throw() : AbsCreamProxy(30) {}
	  
	  std::vector<JobIdWrapper>* m_result;
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_List( std::vector<JobIdWrapper>* result, const int timeout = 30 ) throw();
	  
	public:
	  
	  virtual ~CreamProxy_List( void ) throw() {}
	  
	  virtual void execute(const std::string& serviceURL, const bool ignore_tag_mismatch = false) throw(BaseException&,
								    InvalidArgumentException&,
								    GridProxyDelegationException&,
								    JobSubmissionDisabledException&,
								    GenericException&,
								    //AuthenticationException&,
								    AuthorizationException&,
								    DelegationException&,
								    InternalException&,
								    ConnectionTimeoutException&,
								    auth_ex&,
								    soap_ex&,
								    soap_runtime_ex&);
	  
	};
	
	//______________________________________________________________________________
	class CreamProxy_Status : public AbsCreamProxy 
	{
	  
	  const JobFilterWrapper* m_jobFilter;
	  AbsCreamProxy::StatusArrayResult* m_target;
	  
	  CreamProxy_Status( const CreamProxy_Status& ) throw() : AbsCreamProxy(30) {}
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_Status( const JobFilterWrapper*, StatusArrayResult*, const int timeout = 30 ) throw();
	  
	public:
	  virtual void execute(const std::string& serviceURL, const bool ignore_tag_mismatch = false) throw(BaseException&,
								    InvalidArgumentException&,
								    GridProxyDelegationException&,
								    JobSubmissionDisabledException&,
								    GenericException&,
								    //AuthenticationException&,
								    AuthorizationException&,
								    DelegationException&,
								    InternalException&,
								    ConnectionTimeoutException&,
								    auth_ex&,
								    soap_ex&,
								    soap_runtime_ex&);
	  
	  ~CreamProxy_Status( void ) throw() { }
	  
	};
	
	//______________________________________________________________________________
	class CreamProxy_Lease : public AbsCreamProxy 
	{
	  
	  const std::string m_leaseID;
	  const time_t      m_leaseTime;
	  std::pair<std::string, time_t>* m_resp_lease;
	  
	  CreamProxy_Lease( const CreamProxy_Lease& ) throw() : AbsCreamProxy(30), m_leaseID(""), m_leaseTime(0) {}
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_Lease( const std::pair<std::string, time_t>& Lease, std::pair<std::string, time_t>*, const int timeout = 30 ) throw();
	  
	public:
	  virtual void execute(const std::string& serviceURL, const bool ignore_tag_mismatch = false) throw(BaseException&,
								    InvalidArgumentException&,
								    GridProxyDelegationException&,
								    JobSubmissionDisabledException&,
								    GenericException&,
								    //AuthenticationException&,
								    AuthorizationException&,
								    DelegationException&,
								    InternalException&,
								    ConnectionTimeoutException&,
								    auth_ex&,
								    soap_ex&,
								    soap_runtime_ex&);
	  
	  
	  virtual ~CreamProxy_Lease( void ) throw() { }
	  
	};
		
	//______________________________________________________________________________
	class CreamProxy_LeaseInfo : public AbsCreamProxy 
	{
	  
	  const std::string m_leaseID;
	  //const time_t      m_leaseTime;
	  std::pair<std::string, time_t>* m_resp_lease;
	  
	  CreamProxy_LeaseInfo( const CreamProxy_LeaseInfo& ) throw() 
	    : AbsCreamProxy(30), m_leaseID("") {}
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_LeaseInfo( const std::string& LeaseID, std::pair<std::string, time_t>*, const int timeout = 30 ) throw();
	  
	public:
	  virtual void execute(const std::string& serviceURL, const bool ignore_tag_mismatch = false) throw(BaseException&,
								    InvalidArgumentException&,
								    GridProxyDelegationException&,
								    JobSubmissionDisabledException&,
								    GenericException&,
								    //AuthenticationException&,
								    AuthorizationException&,
								    DelegationException&,
								    InternalException&,
								    ConnectionTimeoutException&,
								    auth_ex&,
								    soap_ex&,
								    soap_runtime_ex&);
	  
	  
	  virtual ~CreamProxy_LeaseInfo( void ) throw() { }
	  
	};
	
	//______________________________________________________________________________
	class CreamProxy_Suspend : public AbsCreamProxy 
	{
	  
	  const JobFilterWrapper *m_jobFilter;
	  ResultWrapper          *m_result;
	  
	  CreamProxy_Suspend( const CreamProxy_Suspend& ) throw() : AbsCreamProxy(30) {}
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_Suspend( const JobFilterWrapper*, ResultWrapper*, const int timeout = 30 ) throw();
	  
	public:
	  virtual void execute(const std::string& serviceURL, const bool ignore_tag_mismatch = false) throw(BaseException&,
								    InvalidArgumentException&,
								    GridProxyDelegationException&,
								    JobSubmissionDisabledException&,
								    GenericException&,
								    //AuthenticationException&,
								    AuthorizationException&,
								    DelegationException&,
								    InternalException&,
								    ConnectionTimeoutException&,
								    auth_ex&,
								    soap_ex&,
								    soap_runtime_ex&);
	  
	  
	  ~CreamProxy_Suspend( void ) throw() { }
	  
	  
	};
	
	//______________________________________________________________________________
	class CreamProxy_Resume : public AbsCreamProxy 
	{
	  
	  const JobFilterWrapper *m_jobFilter;
	  ResultWrapper    *m_result;
	  
	  CreamProxy_Resume( const CreamProxy_Resume& ) throw() : AbsCreamProxy(30) {}
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_Resume( const JobFilterWrapper*, ResultWrapper*, const int timeout = 30 ) throw(); 
	public:
	  virtual void execute(const std::string& serviceURL, const bool ignore_tag_mismatch = false) throw(BaseException&,
								    InvalidArgumentException&,
								    GridProxyDelegationException&,
								    JobSubmissionDisabledException&,
								    GenericException&,
								    //AuthenticationException&,
								    AuthorizationException&,
								    DelegationException&,
								    InternalException&,
								    ConnectionTimeoutException&,
								    auth_ex&,
								    soap_ex&,
								    soap_runtime_ex&);
	  
	  
	  ~CreamProxy_Resume( void ) throw() { }
	  
	};
	
	//______________________________________________________________________________
	class CreamProxy_Cancel : public AbsCreamProxy 
	{
	  
	  const JobFilterWrapper *m_jobFilter;
	  ResultWrapper    *m_result;
	  
	  CreamProxy_Cancel( const CreamProxy_Cancel& ) throw() : AbsCreamProxy(30) {}
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_Cancel( const JobFilterWrapper*, ResultWrapper*, const int timeout = 30 ) throw();
	  
	public:
	  
	  virtual void execute(const std::string& serviceURL, const bool ignore_tag_mismatch = false) throw(BaseException&,
								    InvalidArgumentException&,
								    GridProxyDelegationException&,
								    JobSubmissionDisabledException&,
								    GenericException&,
								    //AuthenticationException&,
								    AuthorizationException&,
								    DelegationException&,
								    InternalException&,
								    ConnectionTimeoutException&,
								    auth_ex&,
								    soap_ex&,
								    soap_runtime_ex&);
	  
	  
	  ~CreamProxy_Cancel( void ) throw() { }
	  
	};
	
	//______________________________________________________________________________
	class CreamProxy_Purge : public AbsCreamProxy 
	{
	  
	  const JobFilterWrapper* m_jobFilter;
	  ResultWrapper*    m_result;
	  
	  CreamProxy_Purge( const CreamProxy_Purge& ) throw() : AbsCreamProxy(30) {}
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_Purge( const JobFilterWrapper*, ResultWrapper*, const int timeout = 30) throw();
	  
	public:
	  
	  virtual void execute(const std::string& serviceURL, const bool ignore_tag_mismatch = false) throw(BaseException&,
								    InvalidArgumentException&,
								    GridProxyDelegationException&,
								    JobSubmissionDisabledException&,
								    GenericException&,
								    //AuthenticationException&,
								    AuthorizationException&,
								    DelegationException&,
								    InternalException&,
								    ConnectionTimeoutException&,
								    auth_ex&,
								    soap_ex&,
								    soap_runtime_ex&);
	  
	  ~CreamProxy_Purge( void ) throw() { }
	  
	};
	
	//______________________________________________________________________________
	class CreamProxy_Delegate : public AbsCreamProxy 
	{
	  const std::string m_delegation_ID;
//	  std::string* m_certtxt;
	  
	  CreamProxy_Delegate( const CreamProxy_Delegate& ) throw() : AbsCreamProxy(30), m_delegation_ID("") {};
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_Delegate( const std::string& delegID, /*std::string*,*/ const int timeout = 30 ) throw();
	  
	public:
	  virtual void execute( const std::string& serviceURL, const bool ignore_tag_mismatch = false) throw(BaseException&,
								     InvalidArgumentException&,
								     GridProxyDelegationException&,
								     JobSubmissionDisabledException&,
								     GenericException&,
								     //AuthenticationException&,
								     AuthorizationException&,
								     DelegationException&,
								     InternalException&,
								     ConnectionTimeoutException&,
								     auth_ex&,
								     soap_ex&,
								     soap_runtime_ex&);
	  
	  
	  virtual ~CreamProxy_Delegate( void ) throw() { };
	  
	};
	
	//______________________________________________________________________________
	class CreamProxy_ProxyRenew : public AbsCreamProxy 
	{
	  const std::string m_delegation_ID;
	  
	  CreamProxy_ProxyRenew( const CreamProxy_ProxyRenew& ) throw() : AbsCreamProxy( 30 ) {}
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_ProxyRenew( const std::string& delegID/*, std::string* S_certtxt*/, const int timeout ) throw();
	  
	public:
	  virtual void execute( const std::string& serviceURL, const bool ignore_tag_mismatch = false) throw(BaseException&,
								     InvalidArgumentException&,
								     GridProxyDelegationException&,
								     JobSubmissionDisabledException&,
								     GenericException&,
								     //AuthenticationException&,
								     AuthorizationException&,
								     DelegationException&,
								     InternalException&,
								     ConnectionTimeoutException&,
								     auth_ex&,
								     soap_ex&,
								     soap_runtime_ex&);
	  
	  
	  ~CreamProxy_ProxyRenew( void ) throw() { }
	  
	};
	
	//______________________________________________________________________________
	class CreamProxy_ServiceInfo : public AbsCreamProxy 
	{
	  
	  //std::string* m_info;
	  ServiceInfoWrapper* m_target;
	  int                 m_verbosity;
	  

	  CreamProxy_ServiceInfo( const CreamProxy_ServiceInfo& ) throw() 
	    : AbsCreamProxy(30) { }
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_ServiceInfo( ServiceInfoWrapper*, const int verb, const int) throw();
	  
	public:
	  
	  virtual void execute( const std::string&, const bool ignore_tag_mismatch = false ) throw(BaseException&,
							   InvalidArgumentException&,
							   GridProxyDelegationException&,
							   JobSubmissionDisabledException&,
							   GenericException&,
							   //AuthenticationException&,
							   AuthorizationException&,
							   DelegationException&,
							   InternalException&,
							   ConnectionTimeoutException&,
							   auth_ex&,
							   soap_ex&,
							   soap_runtime_ex&);
	  
	  
	  ~CreamProxy_ServiceInfo( void ) throw() { }
	  
	};
		
	//______________________________________________________________________________
	class CreamProxy_AcceptNewJobSubmissions : public AbsCreamProxy 
	{
	  
	  bool m_set;

	  CreamProxy_AcceptNewJobSubmissions( const CreamProxy_AcceptNewJobSubmissions& ) throw() 
	    : AbsCreamProxy(30) { }
	  
	protected:
	  friend class CreamProxyFactory;
	  CreamProxy_AcceptNewJobSubmissions( const bool, const int ) throw();
	  
	public:
	  
	  virtual void execute( const std::string&, const bool ignore_tag_mismatch = false ) throw(BaseException&,
							   InvalidArgumentException&,
							   GridProxyDelegationException&,
							   JobSubmissionDisabledException&,
							   GenericException&,
							   //AuthenticationException&,
							   AuthorizationException&,
							   DelegationException&,
							   InternalException&,
							   ConnectionTimeoutException&,
							   auth_ex&,
							   soap_ex&,
							   soap_runtime_ex&);
	  
	  
	  ~CreamProxy_AcceptNewJobSubmissions( void ) throw() { }
	  
	};
	
      }
    }
  }
}

#endif
