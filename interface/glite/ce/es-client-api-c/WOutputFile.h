#ifndef EMIES_CLIENTLIB_WRAPPERS_OF_H
#define EMIES_CLIENTLIB_WRAPPERS_OF_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/WTarget.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class WOutputFile : public OutputFile
      {
      private:
        WOutputFile( ) : OutputFile( ) {}
	
      public:
	WOutputFile( const std::string& _name,
		     const std::vector<WTarget>& _Sources );
	
	virtual ~WOutputFile( ) { this->free( ); }
	WOutputFile( const WOutputFile& );

	std::string toString( const bool tabbed = false ) const;
	WOutputFile& operator=( const WOutputFile& src ) { this->free( ); this->set(src); return *this; }
      private:
	void free( );
	void set( const WOutputFile& );
	
      };
            
    }
  }
}

#endif
