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

#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_AUTHEX_H_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_AUTHEX_H_

#include<exception>
#include<string>

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {
	
	/// An object of this class is raised as an exception when a proxy-related operations fail
	class auth_ex : public std::exception {
	  
	  std::string m_error_message;
	  
	public:
	  auth_ex(const std::string& err_info) : m_error_message(err_info) {}
	  virtual ~auth_ex() throw() {}
	  virtual const char* what() const throw() { return m_error_message.c_str(); }
	  
	};
      }
    }
  }
}

#endif
