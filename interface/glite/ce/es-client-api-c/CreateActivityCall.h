#ifndef EMIES_CLIENTLIB_COMM_CRTACT_H
#define EMIES_CLIENTLIB_COMM_CRTACT_H

#include "glite/ce/es-client-api-c/ActivityCreationResponse.h"
#include "glite/ce/es-client-api-c/CreateActivities.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include "glite/ce/es-client-api-c/AbstractCall.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {

    namespace wrapper {
      class CreateActivities;
    }

    namespace comm {

      //friend class AbstractCall;

      class CreateActivityCall : public AbstractCall
      {
	friend class CallFactory;
	CreateActivitiesType*         m_request;
	CreateActivitiesResponseType  m_response;
	
      protected:
	CreateActivityCall( const std::string& endpoint,
			    emi_es::client::wrapper::CreateActivities* );
      public:
	virtual ~CreateActivityCall( ) throw( ) { }
	
	bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );
	
//	void getActivityCreationResponse( std::vector<emi_es::client::wrapper::ActivityCreationResponse>& ) const;
	virtual void getResponse( std::vector<emi_es::client::wrapper::ActivityCreationResponse>& ) const;

      };

    }
  }
}

#endif
