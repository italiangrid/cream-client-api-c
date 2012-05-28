#ifndef EMIES_CLIENTLIB_WRAPPERS_EXE_H
#define EMIES_CLIENTLIB_WRAPPERS_EXE_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"



#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class ExecutableType : public ExecutableClassType
      {
      private:
	ExecutableType() : ExecutableClassType( ) {}
	
      public:
	ExecutableType( const std::string& path,
			const std::vector<std::string>& args,
			const int failifexitcode );

	ExecutableType( const std::string& path,
                        const std::vector<std::string>& args);
	
	virtual ~ExecutableType( ) { this->free( ); }
	
	ExecutableType( const ExecutableType& );
	
	std::string toString( const bool tabbed = false ) const;
	ExecutableType& operator=(const ExecutableType& src) { this->free(); this->set( src) ;return *this; }

      private:
	void free( );
	void set( const ExecutableType& );
	
      };
      
    }
  }
}

#endif
