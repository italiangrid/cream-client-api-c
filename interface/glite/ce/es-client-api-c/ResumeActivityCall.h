#ifndef EMIES_CLIENTLIB_COMM_RESUMEACTCALL_H
#define EMIES_CLIENTLIB_COMM_RESUMEACTCALL_H

#include "glite/ce/es-client-api-c/ManageActivityCall.h"


#include <string>
#include <vector>
#include <map>

namespace emi_es {
  namespace client {
    namespace comm {
      
      class ResumeActivityCall : public ManageActivityCall {
	friend class CallFactory;
      protected:
	ResumeActivityCall( const std::string& endpoint,
			    const std::vector<std::string>& );
      public:
	virtual ~ResumeActivityCall( ) throw() { }

	virtual bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );
	
      };

    }
  }
}

#endif
