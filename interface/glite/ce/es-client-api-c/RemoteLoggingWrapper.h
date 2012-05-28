#ifndef EMIES_CLIENTLIB_WRAPPERS_REMLOG_H
#define EMIES_CLIENTLIB_WRAPPERS_REMLOG_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"


#include <string>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class RemoteLoggingWrapper : public RemoteLoggingType
      {
      private:
        RemoteLoggingWrapper() : RemoteLoggingType( ) { }
	
      public:
	RemoteLoggingWrapper( const std::string& servicetype,
		       std::string* url,
		       const bool optional );
	
	virtual ~RemoteLoggingWrapper( ) { this->free( ); }
	RemoteLoggingWrapper( const RemoteLoggingWrapper& );
	
	std::string toString( const bool tabbed = false ) const;
	RemoteLoggingWrapper& operator=( const RemoteLoggingWrapper& src ) { this->free(); this->set(src); return *this; }

      private:
	void free( );
	void set( const RemoteLoggingWrapper& );
	
      };
      
    }
  }
}

#endif
