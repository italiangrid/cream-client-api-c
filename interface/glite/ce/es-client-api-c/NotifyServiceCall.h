#ifndef EMIES_CLIENTLIB_COMM_NOTIFYACTCALL_H
#define EMIES_CLIENTLIB_COMM_NOTIFYACTCALL_H

#include "glite/ce/es-client-api-c/InternalBaseFault.h"
#include "glite/ce/es-client-api-c/AbstractCall.h"

#include <string>
#include <vector>
#include <utility>

namespace emi_es {
  namespace client {
    namespace comm {

      class NotifyServiceCall : public AbstractCall {

	std::vector<std::pair<std::string, AbstractCall::NOTIFYMESSAGE> >  m_request;
	std::vector<std::pair<std::string, wrapper::InternalBaseFault> >   m_response;
	friend class CallFactory;

      protected:
	NotifyServiceCall( const std::string&,
			   const std::vector< std::pair<std::string, AbstractCall::NOTIFYMESSAGE> >&);
	
      public:
	virtual ~NotifyServiceCall() throw() {}

	bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );

	virtual void getResponse( std::vector<std::pair<std::string, wrapper::InternalBaseFault> >& tgt) const
	{
	  tgt = m_response;
	}

      };

    }
  }
}

#endif
