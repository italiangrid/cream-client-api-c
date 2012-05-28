#ifndef EMIES_CLIENTLIB_WRAPPERS_CT_H
#define EMIES_CLIENTLIB_WRAPPERS_CT_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"


namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class CoprocessorType : public CoprocessorClassType
      {
      private:
        CoprocessorType( ) : CoprocessorClassType( ) { }
	
      public:
	  CoprocessorType( const int _item,
			   const bool optional );
	  
	  virtual ~CoprocessorType( ) { this->free( ); }
	  
	  CoprocessorType(const CoprocessorType& );
	  
	  std::string toString( const bool tabbed = false ) const;
	   
      private:
          CoprocessorType& operator=(const CoprocessorType&);
	  void set( const CoprocessorType& );
	  void free( );
      };
      
    }
  }
}

#endif
