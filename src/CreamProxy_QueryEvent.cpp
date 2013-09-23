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

#include "glite/ce/cream-client-api-c/EventWrapper.h"
#include "glite/ce/cream-client-api-c/CreamProxy_Impl.h"
#include "glite/ce/cream-client-api-c/creamApiLogger.h"


#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>
//#include <sstream>

using namespace glite::ce::cream_client_api::soap_proxy;
using namespace std;

//______________________________________________________________________________
CreamProxy_QueryEvent::CreamProxy_QueryEvent( const pair<string, string> range_eventID,
					      const pair<time_t, time_t> range_time,
					      const std::string& eventType,
					      const int max_events,
					      const int verbosity,
					      const vector< pair<string,string> >& prop,
					      time_t* T,
					      string* DB_ID,
					      list<EventWrapper*>* target, 
					      const int timeout ) throw()
  : AbsCreamProxy( timeout ), m_target( target ), 
    m_time_t(T), m_database_id(DB_ID ), m_eventid_range( range_eventID ),
    m_time_range( range_time ), m_event_type( eventType),  m_max_events( max_events ),
    m_verbosity( verbosity ), m_request_prop( prop )
{
}

//______________________________________________________________________________
void CreamProxy_QueryEvent::execute(const string& serviceURL, const bool ignore_tag_mismatch) 
  throw(BaseException&,
	InvalidArgumentException&,
	GenericException&,
	AuthorizationException&,
	InternalException&,
	ConnectionTimeoutException&,
	auth_ex&,
	soap_ex&,
	soap_runtime_ex&)
{
  //  static const char* method_name = "CreamProxy_Info::execute() - ";
  initSoap init(this);
  
#ifdef DOPROFILE
  apiUtil::scoped_timer T("CreamProxy_QueryEvent::execute-soap_call___CREAM__QueryEvent");
#endif  

  _CREAMTYPES__QueryEventResult result;
  _CREAMTYPES__QueryEventRequest req;
  //ostringstream tmp;

  //string tmp;

  req.fromEventId = NULL;
  req.toEventId   = NULL;
  req.fromDate    = NULL;
  req.toDate      = NULL;
  
  boost::scoped_ptr< string > s1,s2;

  if(atoll(m_eventid_range.first.c_str()) > -1) {
    //tmp = boost::lexical_cast<string>(  m_eventid_range.first );
    //tmp << m_eventid_range.first;
    req.fromEventId = new string( boost::lexical_cast<string>(  m_eventid_range.first ) );
    s1.reset( req.fromEventId );
  }

  
  if(atoll(m_eventid_range.second.c_str()) > -1) {
    //tmp.str( "" );
    //tmp = boost::lexical_cast<string>(m_eventid_range.second);
    req.toEventId = new string( boost::lexical_cast<string>(m_eventid_range.second) );
    //boost::scoped_ptr< string > s2( req.toEventId );
    s2.reset( req.toEventId );
  }

  boost::scoped_ptr< time_t > t1;
  if( m_time_range.first > -1 ) {
    req.fromDate = new time_t;
    *req.fromDate = m_time_range.first;
    t1.reset( req.fromDate );
  }

  boost::scoped_ptr< time_t > t2;
  if( m_time_range.second > -1 ) {
    req.toDate = new time_t;
    *req.toDate = m_time_range.second;
    t2.reset( req.toDate );
  }
  
  req.eventType = m_event_type;
  req.maxQueryEventResultSize = m_max_events ;
  req.verbosityLevel = m_verbosity; 

  vector<pair<string, string> >::const_iterator it = m_request_prop.begin();
  while( it != m_request_prop.end() ) {
    //JobPropertyWrapper *w = new JobPropertyWrapper( it->first, it->second );
    CREAMTYPES__Property *P = new CREAMTYPES__Property();
    P->name  = it->first;
    P->value = it->second;
    req.property.push_back( P );
    ++it;
  }
  
  if(SOAP_OK != soap_call___CREAM__QueryEvent(m_soap, 
					      serviceURL.c_str(), 
					      NULL, 
					      &req, 
					      &result))
    {
      vector<CREAMTYPES__Property*>::iterator _pit = req.property.begin();
      while( _pit != req.property.end() ) {
        delete(*_pit);
	++_pit;
      }
    
      ExceptionFactory::raiseException(m_soap, ignore_tag_mismatch);
    } else {
   
    CREAM_SAFE_LOG(*m_log_dev << log4cpp::Priority::WARN
                     << "CreamProxy_QueryEvent::execute() - "
                     << "CREAM RETURNED DB_ID IN EventQuery=[" << result.dbId << "] FOR CE ["<< serviceURL << "]");
 
    (*m_time_t)      = result.queryExecutionTimeInMillis;
    (*m_database_id) = result.dbId;

    for(vector<CREAMTYPES__Event*>::const_iterator it = result.event.begin();
	it != result.event.end();
	++it)
      {
	
	CREAMTYPES__Event* anEvent = *it;
	vector<CREAMTYPES__Property*>::const_iterator pit = anEvent->property.begin();
	while( pit != anEvent->property.end() ) {
	  //CREAMTYPES__Property *p = *pit;
	
// 	  cout << "property name=" << p->name << endl;
// 	  cout << "property val =" << p->value << endl;
	  pit++;
	}
	
	EventWrapper *evtTmp = new EventWrapper(anEvent->id, anEvent->type, anEvent->timestamp, anEvent->property);
	//m_target->push_back( new EventWrapper( anEvent->id, anEvent->type, anEvent->timestamp, anEvent->property ) );
	m_target->push_back( evtTmp );
      }
     vector<CREAMTYPES__Property*>::iterator _pit = req.property.begin();
     while( _pit != req.property.end() ) {
       delete(*_pit);
       ++_pit;
     }
  }
}
