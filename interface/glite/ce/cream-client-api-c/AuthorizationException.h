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

#ifndef __AUTHZEX_H__
#define __AUTHZEX_H__

#include "glite/ce/cream-client-api-c/BaseException.h"

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace cream_exceptions {
	

	/// An object of this class is raised as an exception when the remote CREAM web service cannot authorize the user for the requested operation
	
	class AuthorizationException : public BaseException {
	  
	  
	public:
	  AuthorizationException(const std::string& mn,
				 const std::string& ec,
				 const std::string& des,
				 const std::string& fc,
				 const time_t& t) : BaseException(mn, ec, des, fc, t) {}
	  virtual ~AuthorizationException() throw() {}
	};
      }
    }
  }
}

#endif
