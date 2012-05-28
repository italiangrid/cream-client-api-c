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

#include <glite/ce/cream-client-api-c/JobDescriptionWrapper.h>

using namespace glite::ce::cream_client_api::soap_proxy;
using namespace std;

//______________________________________________________________________________
JobDescriptionWrapper::JobDescriptionWrapper(const std::string& _jdl,
					     const std::string& _delegationId,
					     const std::string& _delegationProxy,
					     const std::string& _leaseId,
					     const bool         _autostart,
					     const std::string& _descId) throw()
{
  delegationId     = NULL;
  delegationProxy  = NULL;
  leaseId          = NULL;
  jobDescriptionId = NULL;
  
  
  JDL              = _jdl;
  
  if(!_delegationId.empty())
    delegationId     = new std::string( _delegationId );
  
  if(!_delegationProxy.empty())
    delegationProxy  = new std::string( _delegationProxy );
  
  if(! _leaseId.empty())
    leaseId          = new std::string( _leaseId );
  
  autoStart        = _autostart;
  
  if(!_descId.empty())
    jobDescriptionId = new std::string(_descId);
  
}

JobDescriptionWrapper::~JobDescriptionWrapper( ) throw()
{
  //delete JDL;
  delete delegationId;    delegationId=0;
  delete delegationProxy; delegationProxy=0;
  delete leaseId;         leaseId=0;
  delete jobDescriptionId;jobDescriptionId=0;
}

//______________________________________________________________________________	    
// JobDescriptionWrapper::JobDescriptionWrapper( const CREAMTYPES__JobDescription& jd ) throw()
// {
//   JDL              = jd.JDL;
//   delegationId     = NULL;
//   delegationProxy  = NULL;
//   leaseId          = NULL;
//   jobDescriptionId = NULL;
  
  
//   if( jd.delegationId )
//     delegationId    = new std::string( *jd.delegationId );
  
//   if( jd.delegationProxy )
//     delegationProxy = new std::string( *jd.delegationProxy );
  
//   if( jd.leaseId )
//     leaseId         = new std::string( *jd.leaseId );
  
//   if( jd.jobDescriptionId )
//     jobDescriptionId= new std::string( *jd.jobDescriptionId );
  
//   autoStart         = jd.autoStart;
  
// }
