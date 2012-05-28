#ifndef EMIES_CLIENTLIB_WRAPPERS_NI_H
#define EMIES_CLIENTLIB_WRAPPERS_NI_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"


#include <string>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class NetworkInfoType : public NetworkInfoClassType
      {
      private:
        NetworkInfoType( ) : NetworkInfoClassType( ) { }
	
	public:
	  NetworkInfoType( const int _item,
			   const bool optional );
	  
	  virtual ~NetworkInfoType( ) { this->free( ); }
	  NetworkInfoType( const NetworkInfoType& );
	  
	  std::string toString( const bool tabbed = false ) const;

      private:
        NetworkInfoType& operator=( const NetworkInfoType& );
        void set( const NetworkInfoType& );
	void free( );
      };
      
    }
  }
}

#endif
