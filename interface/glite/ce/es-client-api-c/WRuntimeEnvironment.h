#ifndef EMIES_CLIENTLIB_WRAPPERS_RE_H
#define EMIES_CLIENTLIB_WRAPPERS_RE_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class WRuntimeEnvironment : public RuntimeEnvironment
      {
      
      private:
        WRuntimeEnvironment( ) : RuntimeEnvironment( ) { }
	
      public:
	  WRuntimeEnvironment( const std::string& _Name,
			       std::string* _Version,
			       const std::vector<std::string>& _Option,
			       const bool _optional );
	  
	  virtual ~WRuntimeEnvironment( ) { this->free( ); }
	  WRuntimeEnvironment( const WRuntimeEnvironment& );
	  
	  std::string toString( const bool tabbed = false ) const;
	  
      public:
          WRuntimeEnvironment& operator=( const WRuntimeEnvironment& src) { this->free( ); this->set(src); return *this;}
	  
      private:
	  void set( const WRuntimeEnvironment& );
	  void free( );
	  
      };
      
    }
  }
}

#endif
