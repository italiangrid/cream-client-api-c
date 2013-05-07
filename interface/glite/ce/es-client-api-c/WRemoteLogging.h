#ifndef EMIES_CLIENTLIB_WRAPPERS_REMLOG_H
#define EMIES_CLIENTLIB_WRAPPERS_REMLOG_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"


#include <string>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class WRemoteLogging : public RemoteLogging
      {
      private:
        WRemoteLogging() : RemoteLogging( ) { }
	
      public:
	WRemoteLogging( const std::string& servicetype,
		        std::string* url,
		        const bool optional );
	
	virtual ~WRemoteLogging( ) { this->free( ); }
	WRemoteLogging( const WRemoteLogging& );
	
	std::string toString( const bool tabbed = false ) const;
	WRemoteLogging& operator=( const WRemoteLogging& src ) { this->free(); this->set(src); return *this; }

      private:
	void free( );
	void set( const WRemoteLogging& );
	
      };
      
    }
  }
}

#endif
