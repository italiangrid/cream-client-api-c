#ifndef EMIES_CLIENTLIB_WRAPPERS_OF_H
#define EMIES_CLIENTLIB_WRAPPERS_OF_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/Target.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class OutputFile : public _ESADL__OutputFile
      {
      private:
        OutputFile( ) : _ESADL__OutputFile( ) {}
	
      public:
	OutputFile( const std::string& _name,
		    const std::vector<Target>& _Sources );
	
	//std::vector<Target> getTargets( ) const;
	
	virtual ~OutputFile( ) { this->free( ); }
	OutputFile( const OutputFile& );

	std::string toString( const bool tabbed = false ) const;
	OutputFile& operator=( const OutputFile& src ) { this->free( ); this->set(src); return *this; }
      private:
	void free( );
	void set( const OutputFile& );
	
      };
            
    }
  }
}

#endif
