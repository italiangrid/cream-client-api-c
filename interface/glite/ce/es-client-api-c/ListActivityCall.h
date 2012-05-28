#ifndef EMIES_CLIENTLIB_COMM_LISTACTCALL_H
#define EMIES_CLIENTLIB_COMM_LISTACTCALL_H

#include "glite/ce/es-client-api-c/AbstractCall.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {

    namespace wrapper {
      class ListActivities;
    }

    namespace comm {

      class ListActivityCall : public AbstractCall {
	friend class CallFactory;
	wrapper::ListActivities     *m_request;
	ListActivitiesResponseType   m_response;

      protected:
	ListActivityCall( const std::string& endpoint,
			  wrapper::ListActivities* );
      public:
	virtual ~ListActivityCall() throw() {}

	bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );

	virtual void getResponse( bool&, std::vector<std::string>& ) const;

      };

    }
  }
}

#endif
