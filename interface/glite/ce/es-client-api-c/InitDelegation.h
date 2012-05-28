#ifndef EMIES_CLIENTLIB_WRAPPERS_INITDELEG_H
#define EMIES_CLIENTLIB_WRAPPERS_INITDELEG_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>

namespace emi_es {
  namespace client {
    namespace wrapper {
	
      class InitDelegation : public InitDelegationType {

      private:
	InitDelegation() : InitDelegationType() {}

      public:
	InitDelegation( const std::string&, 
			std::string*,
			const ULONG64 );

	virtual ~InitDelegation( ) { this->free( ); }

	InitDelegation( const InitDelegation& );
	
      private:
	void set( const InitDelegation& );
	void free( );
	InitDelegation& operator=( const InitDelegation& ) { return *this; }
      };
    }
  }
}

#endif
