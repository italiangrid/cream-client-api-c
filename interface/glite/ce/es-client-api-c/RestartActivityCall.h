#ifndef EMIES_CLIENTLIB_COMM_RESTARTACTCALL_H
#define EMIES_CLIENTLIB_COMM_RESTARTACTCALL_H

#include "glite/ce/es-client-api-c/ManageActivityCall.h"


#include <string>
#include <vector>
#include <map>

namespace emi_es {
  namespace client {
    namespace comm {
      
      class RestartActivityCall : public ManageActivityCall {
	friend class CallFactory;
      protected:
	RestartActivityCall( const std::string& endpoint,
			     const std::vector<std::string>& );
      public:
	virtual ~RestartActivityCall( ) throw() { }

	virtual bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );
	
      };

    }
  }
}

#endif
