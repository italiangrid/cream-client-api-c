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
#ifndef __JOBSTATUSLIST_H__
#define __JOBSTATUSLIST_H__

//#include "glite/ce/cream-client-api-c/soap_definitions.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"
#include <string>
#include <vector>

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {
	
	class JobStatusList : public creamtypes__JobStatusList {
	  
	  JobStatusList(const JobStatusList& J) {}
	  
	public:
	  JobStatusList() {}
	  virtual ~JobStatusList();
	  virtual void print(const int&);
	  virtual void getJobIDS(std::vector<std::string>&);
	};
      }
    }
  }
}

#endif
