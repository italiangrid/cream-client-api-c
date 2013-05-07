#ifndef EMIES_CLIENTLIB_WRAPPERS_EXE_H
#define EMIES_CLIENTLIB_WRAPPERS_EXE_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"



#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class WExecutable : public ExecutableType //ESADL__Executable_USCOREType
      {
      private:
	WExecutable() : ExecutableType( ) {}
	
      public:
	WExecutable( const std::string& path,
		     const std::vector<std::string>& args,
		     int* failifexitcode );

	virtual ~WExecutable( ) { this->free( ); }
	
	WExecutable( const WExecutable& );
	
	std::string toString( const bool tabbed = false ) const;
	WExecutable& operator=(const WExecutable& src) { this->free(); this->set( src) ;return *this; }

      private:
	void free( );
	void set( const WExecutable& );
	
      };
      
    }
  }
}

#endif
