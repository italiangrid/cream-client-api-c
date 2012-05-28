#ifndef EMIES_CLIENTLIB_COMM_INITDELEGCALL_H
#define EMIES_CLIENTLIB_COMM_INITDELEGCALL_H

#include "glite/ce/es-client-api-c/AbstractCall.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>

namespace emi_es {
  namespace client {

    namespace wrapper {
      class InitDelegation;
    }

    namespace comm {

      class InitDelegationCall : public AbstractCall {
	friend class CallFactory;
	InitDelegationType         *m_request;
	InitDelegationResponseType  m_response;

      protected:
	InitDelegationCall( const std::string& endpoint,
			    wrapper::InitDelegation* );
      public:
	virtual ~InitDelegationCall( ) throw( ) { }
	
	bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );

	virtual void getResponse( std::string& delegID, std::string& serverCert) const
	{
	  delegID = m_response.DelegationID;
	  serverCert = ( m_response.CSR!=0 ? *m_response.CSR : "" );
	}

      };

    }
  }
}

#endif
