#ifndef EMIES_CLIENTLIB_WRAPPERS_CT_H
#define EMIES_CLIENTLIB_WRAPPERS_CT_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"


namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class WCoprocessorType : public CoprocessorType
      {
      private:
        WCoprocessorType( ) : CoprocessorType( ) { }
	
      public:
	  WCoprocessorType( const int _item,
			    bool* optional );
	  
	  virtual ~WCoprocessorType( ) { this->free( ); }
	  
	  WCoprocessorType(const WCoprocessorType& );
	  
	  std::string toString( const bool tabbed = false ) const;
	   
      private:
          WCoprocessorType& operator=(const WCoprocessorType&);
	  void set( const WCoprocessorType& );
	  void free( );
      };
      
    }
  }
}

#endif
