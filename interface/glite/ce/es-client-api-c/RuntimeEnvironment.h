#ifndef EMIES_CLIENTLIB_WRAPPERS_RE_H
#define EMIES_CLIENTLIB_WRAPPERS_RE_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class RuntimeEnvironment : public RuntimeEnvironmentType
      {
      
      private:
        RuntimeEnvironment( ) : RuntimeEnvironmentType( ) { }
	
      public:
	  RuntimeEnvironment( const std::string& _Name,
			      std::string* _Version,
			      const std::vector<std::string>& _Option,
			      const bool _optional );
	  
	  virtual ~RuntimeEnvironment( ) { this->free( ); }
	  RuntimeEnvironment( const RuntimeEnvironment& );
	  
	  std::string toString( const bool tabbed = false ) const;
	  
      public:
          RuntimeEnvironment& operator=( const RuntimeEnvironment& src) { this->free( ); this->set(src); return *this;}
	  
      private:
	  void set( const RuntimeEnvironment& );
	  void free( );
	  
      };
      
    }
  }
}

#endif
