#ifndef EMIES_CLIENTLIB_COMM_PAUSEACTCALL_H
#define EMIES_CLIENTLIB_COMM_PAUSEACTCALL_H

#include "glite/ce/es-client-api-c/ManageActivityCall.h"


#include <string>
#include <vector>
#include <map>

namespace emi_es {
  namespace client {
    namespace comm {
      
      class PauseActivityCall : public ManageActivityCall {
	friend class CallFactory;
      protected:
	PauseActivityCall( const std::string& endpoint,
			   const std::vector<std::string>& );
      public:
	virtual ~PauseActivityCall( ) throw() { }

	virtual bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );
	
      };

    }
  }
}

#endif
