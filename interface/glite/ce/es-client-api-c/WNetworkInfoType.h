#ifndef EMIES_CLIENTLIB_WRAPPERS_NI_H
#define EMIES_CLIENTLIB_WRAPPERS_NI_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"


#include <string>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class WNetworkInfoType : public NetworkInfoType
      {
      private:
        WNetworkInfoType( ) : NetworkInfoType( ) { }
	
	public:
	  WNetworkInfoType( const int _item,
			    bool* optional );
	  
	  virtual ~WNetworkInfoType( ) { this->free( ); }
	  WNetworkInfoType( const WNetworkInfoType& );
	  
	  std::string toString( const bool tabbed = false ) const;

      private:
        WNetworkInfoType& operator=( const WNetworkInfoType& );
        void set( const WNetworkInfoType& );
	void free( );
      };
      
    }
  }
}

#endif
