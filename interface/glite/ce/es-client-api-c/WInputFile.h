#ifndef EMIES_CLIENTLIB_WRAPPERS_IF_H
#define EMIES_CLIENTLIB_WRAPPERS_IF_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/WSource.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class WInputFile : public InputFile
      {
      private:
        WInputFile( ) : InputFile( ) {}

      public:
	WInputFile( const std::string& _name,
		    const std::vector<WSource>& _Sources,
		    bool *_IsExecutable );
	
	void getSources( std::vector<WSource>& ) const;
	
	virtual ~WInputFile( ) { this->free( ); }
	WInputFile( const WInputFile& );
	
	std::string toString( const bool tabbed = false ) const;
	WInputFile& operator=( const WInputFile& src ) { this->free( ); this->set( src); return *this; }
      private:
	void free( );
	void set( const WInputFile& );
	
      };
      
    }
  }
}

#endif
