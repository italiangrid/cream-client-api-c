#ifndef EMIES_CLIENTLIB_WRAPPERS_NOTIFYSERV_H
#define EMIES_CLIENTLIB_WRAPPERS_NOTIFYSERV_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <vector>
#include <string>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class NotifyService : public NotifyServiceType
      {
      private:
        NotifyService( ) : NotifyServiceType( ) { }
	
      public:
	virtual ~NotifyService( ) { this->free( ) ;}
	NotifyService( const NotifyService& src) { this->set( src ); }
	NotifyService( const std::vector<NotifyRequestItemType>& );
	
      private:
	void set( const NotifyService& );
	void free( );
	NotifyService& operator=(const NotifyService&) { return *this; }

      };

    }
  }
}

#endif
