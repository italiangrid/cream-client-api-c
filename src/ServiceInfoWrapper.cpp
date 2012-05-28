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

#include <glite/ce/cream-client-api-c/ServiceInfoWrapper.h>

using namespace std;
using namespace glite::ce::cream_client_api::soap_proxy;

//______________________________________________________________________________
void ServiceInfoWrapper::reset( void ) throw()
{
  if(description) {
    delete description;
    description = 0;
  }
  if(status) {
    delete status;
    status = 0;
  }
  std::vector<CREAMTYPES__Property*>::const_iterator it;
  for(it=property.begin(); it!=property.end(); ++it)
    if(*it)
      delete(*it);
  property.clear(); 
  std::vector<CREAMTYPES__ServiceMessage*>::const_iterator sit;
  for(sit=message.begin(); sit!=message.end(); ++sit)
    if(*sit)
      delete(*sit);
  message.clear();
}

//______________________________________________________________________________
void ServiceInfoWrapper::set(const CREAMTYPES__ServiceInfo& aServ) throw()
{
  
  this->interfaceVersion = aServ.interfaceVersion;
  this->serviceVersion   = aServ.serviceVersion;
  this->startupTime      = aServ.startupTime;
  this->doesAcceptNewJobSubmissions = aServ.doesAcceptNewJobSubmissions;
  
  std::vector<CREAMTYPES__Property*>::const_iterator it;
  
  for(it=aServ.property.begin(); it!=aServ.property.end(); ++it)
    {
      CREAMTYPES__Property* tmp = new CREAMTYPES__Property();
      tmp->value = (*it)->value;
      tmp->name  = (*it)->name;
      this->property.push_back(tmp);
    }
  
  if(aServ.description) {
    this->description = new std::string( *aServ.description );
  } else this->description = NULL;
  
  if(aServ.status) {
    this->status = new std::string( *aServ.status );
  } else this->status = NULL;
  
  
  std::vector<CREAMTYPES__ServiceMessage*>::const_iterator sit;
  
  for(sit=aServ.message.begin(); sit!=aServ.message.end(); ++sit)
    {
      CREAMTYPES__ServiceMessage* tmp = new CREAMTYPES__ServiceMessage();
      tmp->type      = (*sit)->type;
      tmp->message   = (*sit)->message;
      tmp->timastamp = (*sit)->timastamp;
      this->message.push_back(tmp);
    }
}
