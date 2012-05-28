#ifndef EMIES_CLIENTLIB_COMM_PUTDELEGCALL_H
#define EMIES_CLIENTLIB_COMM_PUTDELEGCALL_H

#include "glite/ce/es-client-api-c/AbstractCall.h"

#include <string>

namespace emi_es {
  namespace client {
    namespace comm {

      class PutDelegationCall : public AbstractCall {

	PutDelegationType          *m_request;
	std::string                 m_response;
	
	friend class CallFactory;
	
      protected:
	PutDelegationCall( const std::string& endpoint,
			   const std::string& DelegationID,
			   const std::string& Credential );
      public:
	virtual ~PutDelegationCall( ) throw( ) { delete m_request; }
	
	bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );

	virtual void getResponse( std::string& resp ) const 
	{ resp = m_response; }

      };

    }
  }
}

#endif
