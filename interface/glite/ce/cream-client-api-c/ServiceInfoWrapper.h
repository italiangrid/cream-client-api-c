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

#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_SERVICEINFOWRAPPER_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_SERVICEINFOWRAPPER_

//#include "CREAM_CLIENTH.h"
//#include "CREAM_CLIENTStub.h"

#include "glite/ce/cream-client-api-c/cream_client_soapH.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"

#include <vector>
#include <string>

namespace glite {
   namespace ce {
     namespace cream_client_api {
       namespace soap_proxy {

	 /// A class to wrap the information returned by the remote CREAM operation serviceInfo
	 /**
	    The ServiceInfoWrapper wraps the structured information returned by CREAM:
	    - Version\n
	    - Interface Version\n
	    - Startup time\n
	    - If submission is enabled or disabled
	    - The URL of the CEMon associated to the CREAM service
	    - more future properties
	 */
	 class ServiceInfoWrapper : public CREAMTYPES__ServiceInfo {

	   friend class CreamProxy_ServiceInfo;

	 protected:

	   //___________________________________________________________________
	   void reset( void ) throw();

	   //___________________________________________________________________
	   void set(const CREAMTYPES__ServiceInfo& aServ) throw();

	   //___________________________________________________________________
	   ServiceInfoWrapper( const CREAMTYPES__ServiceInfo& aServ ) throw()
	     {
	       this->set(aServ);
	     }

	   //___________________________________________________________________
	   ServiceInfoWrapper& operator=(const CREAMTYPES__ServiceInfo& aServ) throw()
	     {
	       this->reset();
	       this->set( aServ );
	       return *this;
	     }

	   //___________________________________________________________________
	   ServiceInfoWrapper( const ServiceInfoWrapper& aServ ) throw()
	     : CREAMTYPES__ServiceInfo()
	     {
	       this->set((const CREAMTYPES__ServiceInfo&)aServ);
	     }

	   //___________________________________________________________________
	   ServiceInfoWrapper& operator=(const ServiceInfoWrapper& aServ) throw()
	     {
	       this->reset();
	       this->set( (const CREAMTYPES__ServiceInfo&)aServ );
	       return *this;
	     }
	   
	 public:

	   //___________________________________________________________________
	   /**
	      Simple class constructor
	   */
	   ServiceInfoWrapper() {
	     description = NULL;
	     status      = NULL;
	   }

	   //___________________________________________________________________
	   /**
	      Class destructor
	   */
	   ~ServiceInfoWrapper( void ) throw()
	     {
	       this->reset();
	     }

	   //___________________________________________________________________
	   /**
	      Returns the version of CREAM CE web service

	      \return std::string
	   */
	   std::string getServiceVersion( void ) const { return serviceVersion; }
	   
	   //___________________________________________________________________
	   /**
	      Returns the version of the plugged web service interface into the CREAM CE engine

	      \return std::string
	   */
	   std::string getInterfaceVersion( void ) const { return interfaceVersion; }
	   
	   //___________________________________________________________________
	   /**
	      Return the time of the last startup
	      
	      \return time_t
	   */
	   time_t      getStartupTime( void ) const { return startupTime; }

	   //___________________________________________________________________

	   /**
	      Returns 'true' if the CREAM CE does accept job submission, 'false'  otherwise
	      
	      \return bool
	   */
	   bool        getAcceptJobSubmission( void ) const { return doesAcceptNewJobSubmissions; }
	   
	   //___________________________________________________________________
	   /**
	      Returns the URL of the CEMonitor web service associated to the CREAM CE

	      \return std::string
	   */
	   std::string getCEMonURL( void ) const {
	     if(property.empty()) return "";
	     std::vector<CREAMTYPES__Property*>::const_iterator it;
	     for(it=property.begin(); it!=property.end(); ++it)
	       if((*it)->name == "cemon_url") return (*it)->value;
	     
	     return "";
	     
	   }
	   
	 };

       }
     }
   }
}

#endif
