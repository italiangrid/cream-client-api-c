#ifndef EMIES_CLIENTLIB_COMM_WIPEACTCALL_H
#define EMIES_CLIENTLIB_COMM_WIPEACTCALL_H

#include "glite/ce/es-client-api-c/ManageActivityCall.h"


#include <string>
#include <vector>
#include <map>

namespace emi_es {
  namespace client {
    namespace comm {
      
      class WipeActivityCall : public ManageActivityCall {
	
	friend class CallFactory;
	
      protected:
	WipeActivityCall( const std::string& endpoint,
			  const std::vector<std::string>& );
      public:
	virtual ~WipeActivityCall( ) throw() { }

	virtual bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );
	
      };

    }
  }
}

#endif
