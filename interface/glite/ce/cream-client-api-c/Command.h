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

#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_COMMAND_H_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_COMMAND_H_

//#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"
#include <string>
#include <vector>

class creamtypes__Command;

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {

	class Command {

	  std::string m_name;
	  std::string m_status;
	  std::string m_failureReason;
	  time_t      m_creationTime;
	  time_t      m_startSchedulingTime;
	  time_t      m_startProcessingTime;
	  time_t      m_executionCompletedTime;

	 public:
	  Command(creamtypes__Command*);
	  virtual ~Command() {}
	  std::string getCommandName( void ) const { return m_name; }
	  std::string getStatusName( void ) const { return m_status; }
	  std::string getFailureReason( void ) const { return m_failureReason; }
	  time_t      getCreationTime( void ) const { return m_creationTime; }
	  time_t      getStartSchedulingTime( void ) const { return m_startSchedulingTime; }
	  time_t      getStartProcessingTime( void ) const { return m_startProcessingTime; }
	  time_t      getExecutionCompletedTime( void ) const { return m_executionCompletedTime; }
        };
      }
    }
  }
}
#endif
