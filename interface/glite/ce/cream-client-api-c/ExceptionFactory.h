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
#ifndef _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_EXFACTORY_H_
#define _GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_EXFACTORY_H_

//#include "CREAM_CLIENTH.h"
//#include "CREAM_CLIENTStub.h"

#include "glite/ce/cream-client-api-c/cream_client_soapH.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"

#include "glite/ce/cream-client-api-c/auth_ex.h"
#include "glite/ce/cream-client-api-c/soap_ex.h"
#include "glite/ce/cream-client-api-c/invalidTimestamp_ex.h"
#include "glite/ce/cream-client-api-c/BaseException.h"
#include "glite/ce/cream-client-api-c/JobUnknownException.h"
#include "glite/ce/cream-client-api-c/InvalidArgumentException.h"
#include "glite/ce/cream-client-api-c/OperationNotSupportedException.h"
#include "glite/ce/cream-client-api-c/NoSuitableResourceException.h"
#include "glite/ce/cream-client-api-c/GridProxyDelegationException.h"
#include "glite/ce/cream-client-api-c/JobStatusInvalidException.h"
#include "glite/ce/cream-client-api-c/GenericException.h"
//#include "glite/ce/cream-client-api-c/AuthenticationException.h"
#include "glite/ce/cream-client-api-c/AuthorizationException.h"
#include "glite/ce/cream-client-api-c/DelegationException.h"
#include "glite/ce/cream-client-api-c/InternalException.h"
#include "glite/ce/cream-client-api-c/ConnectionTimeoutException.h"
#include "glite/ce/cream-client-api-c/JobSubmissionDisabledException.h"

#include "boost/thread/recursive_mutex.hpp"

namespace cream_ex = glite::ce::cream_client_api::cream_exceptions;

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace soap_proxy {
	namespace ExceptionFactory {

	  void raiseException(struct soap*, const bool ignore_tag_mismatch = false)
	    throw(cream_ex::BaseException&,
		  cream_ex::JobUnknownException&,
		  cream_ex::InvalidArgumentException&,
		  cream_ex::OperationNotSupportedException&,
		  cream_ex::NoSuitableResourceException&,
		  cream_ex::GridProxyDelegationException&,
		  cream_ex::JobStatusInvalidException&,
		  cream_ex::GenericException&,
		  //		  cream_ex::AuthenticationException&,
		  cream_ex::AuthorizationException&,
		  cream_ex::DelegationException&,
		  cream_ex::InternalException&,
		  cream_ex::JobSubmissionDisabledException&,
		  cream_ex::ConnectionTimeoutException&);
	  
	  std::string makeStringFromFault( CREAMTYPES__BaseFaultType* ) throw();
	  
	};
      }
      }
      }
      }
#endif

