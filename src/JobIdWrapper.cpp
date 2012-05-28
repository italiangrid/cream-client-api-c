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

#include "glite/ce/cream-client-api-c/JobIdWrapper.h"

using namespace glite::ce::cream_client_api::soap_proxy;
using namespace std;

//______________________________________________________________________________
void JobIdWrapper::clone( const CREAMTYPES__JobId* other ) throw()
{
    if ( other && other != this ) {
        destroy();
        id = other->id;
        creamURL = other->creamURL;
        for( vector<CREAMTYPES__Property*>::const_iterator it = other->property.begin(); it != other->property.end(); ++it ) {
            CREAMTYPES__Property* aProperty = new CREAMTYPES__Property();
            aProperty->value = (*it)->value;
            aProperty->name  = (*it)->name;
            property.push_back( aProperty );
        }
    }
}

void JobIdWrapper::destroy( void ) throw()
{
    vector<CREAMTYPES__Property*>::iterator it;
    for( it = property.begin(); it != property.end(); ++it ) {
        delete( *it );
    }
    property.clear();
}

//______________________________________________________________________________
JobIdWrapper& JobIdWrapper::operator=( const JobIdWrapper& aJobId ) throw() 
{   
    if ( &aJobId != this ) {
        clone( &aJobId );
    }
    return *this; 
}

//______________________________________________________________________________
JobIdWrapper::JobIdWrapper( const JobIdWrapper& aJob ) throw() 
  : CREAMTYPES__JobId()
{  
    clone( &aJob );
}

JobIdWrapper::JobIdWrapper( const CREAMTYPES__JobId* other ) 
{
    clone( other );
}

JobIdWrapper::JobIdWrapper( const string& CreamJobId, const string& CreamURL,
                            const vector<JobPropertyWrapper>& prop) throw() 
{
    id = CreamJobId;
    creamURL = CreamURL;            
    
    for( vector<JobPropertyWrapper>::const_iterator it = prop.begin(); it != prop.end(); ++it ) {
        CREAMTYPES__Property* aProperty = new CREAMTYPES__Property();
        aProperty->value = it->getPropertyName();
        aProperty->name  = it->getPropertyValue();
        property.push_back( aProperty );
    }
}

//______________________________________________________________________________
JobIdWrapper::~JobIdWrapper() throw() 
{
    destroy();
}

//______________________________________________________________________________
void JobIdWrapper::getProperties( map< string, string >& target ) 
{
    target.clear();
    vector<CREAMTYPES__Property*>::const_iterator it;
    for( it = property.begin(); it != property.end(); ++it ) {
        target[(*it)->name] = (*it)->value; 
    }
}
