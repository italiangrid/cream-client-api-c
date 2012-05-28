#ifndef EMIES_CLIENTLIB_WRAPPERS_EXTENSIONSTYPE_H
#define EMIES_CLIENTLIB_WRAPPERS_EXTENSIONSTYPE_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class ExtensionsType : public ns1__Extensions_USCOREt
      {

      public:
	std::string toString( const bool tabbed = false ) const;
	
      };
    }
  }
}

#endif
