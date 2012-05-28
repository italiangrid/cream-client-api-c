#ifndef EMIES_CLIENTLIB_COMM_GETTDELEGINFOCALL_H
#define EMIES_CLIENTLIB_COMM_GETTDELEGINFOCALL_H

#include "glite/ce/es-client-api-c/AbstractCall.h"

#include <string>

namespace emi_es {
  namespace client {
    namespace comm {

      class GetDelegationInfoCall : public AbstractCall {

	GetDelegationInfoType          m_request;
	GetDelegationInfoResponseType  m_response;
	friend class CallFactory;
      protected:
	GetDelegationInfoCall( const std::string& endpoint,
			       const std::string& DelegationID );
      public:
	virtual ~GetDelegationInfoCall( ) throw( ) { }
	
	bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );

	virtual void getResponse( time_t& T, std::string& issuer, std::string& subj ) const
	{
	  T = m_response.Lifetime;
	  issuer = (m_response.Issuer != 0 ? *m_response.Issuer : "" );
	  subj   = (m_response.Subject != 0 ? *m_response.Subject : "" );
	}
	
      };

    }
  }
}

#endif
