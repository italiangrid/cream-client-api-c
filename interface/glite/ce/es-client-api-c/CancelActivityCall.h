#ifndef EMIES_CLIENTLIB_COMM_CANCELACTCALL_H
#define EMIES_CLIENTLIB_COMM_CANCELACTCALL_H

#include "glite/ce/es-client-api-c/ManageActivityCall.h"


#include <string>
#include <vector>
#include <map>

namespace emi_es {
  namespace client {
    namespace comm {
      
      class CancelActivityCall : public ManageActivityCall {
	friend class CallFactory;
      protected:
	CancelActivityCall( const std::string& endpoint,
			    const std::vector<std::string>& );
      public:
	virtual ~CancelActivityCall( ) throw() { }

	virtual bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );
	
      };

    }
  }
}

#endif
