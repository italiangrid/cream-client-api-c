#ifndef EMIES_CLIENTLIB_WRAPPERS_CARESP_H
#define EMIES_CLIENTLIB_WRAPPERS_CARESP_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/ActivityCreationResponse.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
	
      class CreateActivitiesResponse : public CreateActivitiesResponseType
      {
      private:
	CreateActivitiesResponse() : CreateActivitiesResponseType( ) { }
	CreateActivitiesResponse(const CreateActivitiesResponse&) {}
	CreateActivitiesResponse& operator=( const CreateActivitiesResponse& ) { return *this; }
	virtual ~CreateActivitiesResponse() {}
	
      public:
	void getActivityCreationResponse( std::vector<ActivityCreationResponse>& ) const;
	
      };
    }
  }
}

#endif
