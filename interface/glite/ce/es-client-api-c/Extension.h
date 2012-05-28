#ifndef EMIES_CLIENTLIB_WRAPPERS_EXTENSION_H
#define EMIES_CLIENTLIB_WRAPPERS_EXTENSION_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class Extension : public ns1__Extension_USCOREt
      {
      private:
	Extension( ) : ns1__Extension_USCOREt() { }
	
      public:
	Extension( const std::string&, const std::string&,
		   const std::string&, const char* );

	Extension( const Extension& src ) { this->set( src ); }

	virtual ~Extension() { this->free( ); }

	std::string toString( const bool tabbed = false ) const;
	
      private:
	void set( const Extension& );
	void free( );
	Extension& operator=( const Extension& src ) { 
	  this->free( ); 
	  this->set( src ); 
	  return *this; 
	}

      };
    }
  }
}

#endif
