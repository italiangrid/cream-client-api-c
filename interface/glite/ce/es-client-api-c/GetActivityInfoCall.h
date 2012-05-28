#ifndef EMIES_CLIENTLIB_COMM_GETINFOCALL_H
#define EMIES_CLIENTLIB_COMM_GETINFOCALL_H

#include "glite/ce/es-client-api-c/InternalBaseFault.h"
#include "glite/ce/es-client-api-c/ComputingActivity.h"
#include "glite/ce/es-client-api-c/AbstractCall.h"

#include <string>
#include <vector>
#include <map>
namespace emi_es {
  namespace client {
    namespace comm {

      class GetActivityInfoCall : public AbstractCall {

	GetActivityInfoType          m_request;
	GetActivityInfoResponseType  m_response;
	friend class CallFactory;
      protected:
	GetActivityInfoCall( const std::string& endpoint,
			     const std::vector<std::string>& ids,
			     const std::vector<std::string>& attrs = std::vector<std::string>() );
      public:
	virtual ~GetActivityInfoCall() throw() {}

	bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );

	virtual void getResponse( std::map<std::string, wrapper::ComputingActivity>&, 
				  std::map<std::string, wrapper::InternalBaseFault>& ) const;

      };

    }
  }
}

#endif
