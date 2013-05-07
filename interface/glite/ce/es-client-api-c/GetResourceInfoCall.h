#ifndef EMIES_CLIENTLIB_COMM_GETRESOURCEINFO_H
#define EMIES_CLIENTLIB_COMM_GETRESOURCEINFO_H

//#include "glite/ce/es-client-api-c/GetActivityStatusResponse.h"

#include "glite/ce/es-client-api-c/AbstractCall.h"

#include <string>
//#include <vector>

namespace emi_es {
  namespace client {
    namespace comm {

      class GetResourceInfoCall : public AbstractCall {

	//	GetActivityStatusType          m_request;
	//	GetActivityStatusResponseType  m_response;
	friend class CallFactory;
      protected:
	GetResourceInfoCall( const std::string& endpoint );

      public:
	virtual ~GetResourceInfoCall() throw() {}

	bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );

      };

    }
  }
}

#endif
