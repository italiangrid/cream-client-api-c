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

#ifndef GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_EW
#define GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_EW

#include "glite/ce/cream-client-api-c/cream_client_soapH.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"

#include <string>
#include <map>

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {

        /// A Class to wrap the Event received by the CE as result of invocation of QueryEvent remote operation.
        /**
	        The user is not supposed to create an object of this class at all. She/he can 'consume' information embedded in it
		after an invocation of QueryEvent remote operation.
		
                To be more precise: the user passes an array of pointers to EventWrapper objects 
                to the CreamProxyFactory::make_CreamProxy_QueryEvent method, and after the invocation of AbsCreamProxy::execute(...) method, 
                these EventWrapper objects are filled with the requested information, accessible through the getter methods.

                \see CreamProxyFactory::make_CreamProxy_QueryEvent(...)

        */

	
	class EventWrapper : public CREAMTYPES__Event {
	
	  //void clone( const CREAMTYPES__Event* other ) throw();
	  void destroy( void ) throw(); 
	  
	  EventWrapper( const CREAMTYPES__Event*) {}
	  EventWrapper& operator=( const CREAMTYPES__Event& ) {return *this;}
	  EventWrapper( const EventWrapper& ) {}
	  EventWrapper( const CREAMTYPES__Event&) {}
	  
	  std::map< std::string, std::string > props;

	protected:

	public:
	
	  /**
	    The default and unique constructor. The user is not supposed to invoke it.
	    This object is created (and returned in an array) by the internal API classes's methods, hidden from user.
	  */
	  EventWrapper( const std::string& id,
			const std::string& type,
			const time_t T,
			const std::vector<CREAMTYPES__Property*>&);
	  

	  

	  ~EventWrapper() throw();
	  /**
	    Return the event ID. It's about an unique 64bit unsigned integer that uniquely identifies an event
	    generated on the CE for the user that invoked the QueryEvent remote operation. Up to now the events in the CE are only
	    job status changes.
	    
	    \return A C++ string (std::string) containing the ID number of the event received.  
	  */
	  std::string   get_event_id( void ) const { return id; }
	  
	  /**
	    In a CE, in future, there will be events different than job status changes. So, up to now the user can simply ignore it.
	    
	    \return A C++ string (std::string) containing the type of the event.
	  */
	  std::string   get_event_type( void ) const { return type; }
	  
	  /**
	    Return the time the event has been generated at.
	    
	    \return The timestamp (time_t) at which the event has been generated in the CE 
	  */
	  time_t        get_event_timestamp( void ) const { return timestamp; }
	  
	  /**
	    Return a map of properties. This method is there for completeness, but the user can ignore it.
	  */
	  void          get_event_properties( std::map< std::string, std::string >& ) const;
	  
	  /**
	    This method is the mean to get access to the message contained in the event.
	    As said above, up to now the events are only describing job status changes. In order to obtain the status contained in the current 
	    event, the user must get the property specifying "type" as argument.
	    
	    \param A string, for now, containing "type" that will allow to get the job status contained in the current event
	    \return A C++ string (std::string) containing a number representing the current job status. It must be converted into a number.
	  */
	  std::string   getPropertyValue( const std::string& name ) { return props[name]; }
	};
      }
    }
  }
}

#endif
