#ifndef EMIES_CLIENTLIB_COMM_GETSTATUS_H
#define EMIES_CLIENTLIB_COMM_GETSTATUS_H

#include "glite/ce/es-client-api-c/GetActivityStatusResponse.h"

#include "glite/ce/es-client-api-c/AbstractCall.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace comm {

      class GetActivityStatusCall : public AbstractCall {

	GetActivityStatusType          m_request;
	GetActivityStatusResponseType  m_response;
	friend class CallFactory;
      protected:
	GetActivityStatusCall( const std::string& endpoint,
			       const std::vector<std::string>& ids );
      public:
	virtual ~GetActivityStatusCall() throw() {}

	bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );

	virtual void getResponse( std::map<std::string, wrapper::ActivityStatus>& states,
				  std::map<std::string, wrapper::InternalBaseFault>& faults ) const
	{
	  ((wrapper::GetActivityStatusResponse*)&m_response)->getActivityStatus( states, faults );
	}

      };

    }
  }
}

#endif
