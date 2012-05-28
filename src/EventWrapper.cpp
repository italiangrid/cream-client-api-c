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
#include "glite/ce/cream-client-api-c/JobPropertyWrapper.h"

using namespace glite::ce::cream_client_api::soap_proxy;
using namespace std;

EventWrapper::EventWrapper( const std::string& _id,
			    const std::string& _type,
			    const time_t _timestamp,
			    const std::vector<CREAMTYPES__Property*>& prop)
{

  id = _id;
  type = _type;
  timestamp = _timestamp;

  vector<CREAMTYPES__Property*>::const_iterator it = prop.begin();
  while( it!=prop.end() ) {
    //    property.push_back( new JobPropertyWrapper( (*it)->name, (*it)->value ) );
    props[(*it)->name]=(*it)->value;
    ++it;
  }
  
}

//______________________________________________________________________________
void EventWrapper::destroy( void ) throw()
{
//   vector<CREAMTYPES__Property*>::iterator it;
//   for( it = property.begin(); it != property.end(); ++it ) {
//     delete( *it );
//   }
//   property.clear();
}

//______________________________________________________________________________
// EventWrapper::EventWrapper( const EventWrapper& anEvent )
//   : CREAMTYPES__Event()
// {  
//   this->clone( &anEvent );
// }

//______________________________________________________________________________
// EventWrapper::EventWrapper( const CREAMTYPES__Event* other ) 
// {
//   this->clone( other );
// }

//______________________________________________________________________________
void 
EventWrapper::get_event_properties( map< string, string >& target) const
{
//   vector<CREAMTYPES__Property*>::const_iterator it = property.begin();
//   while( it != property.end() ) {
    
//     cout << "name="<< (*it)->name << endl;
//     cout << "val ="<< (*it)->value << endl;

//     target[ (*it)->name ] = (*it)->value;

//     ++it;
//   }
  target = props;
}

//______________________________________________________________________________
// void 
// EventWrapper::set( const CREAMTYPES__Event& anEvent )
// {
//   this->id        = anEvent.id;
//   this->type      = anEvent.type;
//   this->timestamp = anEvent.timestamp;
  
//   vector<CREAMTYPES__Property*>::const_iterator it = anEvent.property.begin();
//   while( it != anEvent.property.end() ) {
    
//     JobPropertyWrapper *jwp = new JobPropertyWrapper( (*it)->name, (*it)->value );
    
//     property.push_back( jwp );
    
//     ++it;
//   }
// }

//______________________________________________________________________________
EventWrapper::~EventWrapper( ) throw()
{
  //destroy();
}

//______________________________________________________________________________
// EventWrapper::EventWrapper( const CREAMTYPES__Event& anEvent ) 
// {
//   this->set( anEvent );
// }

//______________________________________________________________________________
// EventWrapper::EventWrapper& 
// EventWrapper::operator=( const CREAMTYPES__Event& anEvent )
// {
//   this->clone( &anEvent );
//   return *this;
// }
