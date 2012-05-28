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
#ifndef __JOBSTATUSOBJECT_H__
#define __JOBSTATUSOBJECT_H__

//#include "glite/ce/cream-client-api-c/soap_definitions.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"
#include <string>

class JobStatusObject : public creamtypes__Status {
 public:
  //____________________________________________________________________________
  JobStatusObject(const creamtypes__Status& J)
    : creamtypes__Status(J)
  {
    if(J.exitCode)
      exitCode = new std::string(*(J.exitCode));
    if(J.failureReason)
      failureReason = new std::string(*(J.failureReason));
  }

  //____________________________________________________________________________
  JobStatusObject(const JobStatusObject& J)
    : creamtypes__Status(J)
  {
    if(J.exitCode)
      exitCode = new std::string(*(J.exitCode));
    if(J.failureReason)
      failureReason = new std::string(*(J.failureReason));

  }
  //____________________________________________________________________________
  virtual ~JobStatusObject() { 
    if(exitCode) delete(exitCode);
    if(failureReason) delete(failureReason);
  }

};

#endif
