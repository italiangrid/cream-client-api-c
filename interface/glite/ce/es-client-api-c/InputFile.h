#ifndef EMIES_CLIENTLIB_WRAPPERS_IF_H
#define EMIES_CLIENTLIB_WRAPPERS_IF_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/Source.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class InputFile : public InputFileType
      {
      private:
        InputFile( ) : InputFileType( ) {}

      public:
	InputFile( const std::string& _name,
		   const std::vector<Source>& _Sources,
		   const bool _IsExecutable );

//        InputFile( const std::string& _name,
//                   const std::vector<Source>& _Sources );
	
	std::vector<Source> getSources( ) const;
	
	virtual ~InputFile( ) { this->free( ); }
	InputFile( const InputFile& );
	
	std::string toString( const bool tabbed = false ) const;
	InputFile& operator=( const InputFile& src ) { this->free( ); this->set( src); return *this; }
      private:
	void free( );
	void set( const InputFile& );
	
      };
      
    }
  }
}

#endif
