#ifndef EMIES_CLIENTLIB_WRAPPERS_IBFAULT_H
#define EMIES_CLIENTLIB_WRAPPERS_IBFAULT_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
	
      class WInternalBaseFault : public InternalBaseFault
      {
      private:
	//InternalBaseFault() : ES_USCORETYPES__InternalBaseFault_USCOREType() {}
	//std::string ActivityID;

      public:
	WInternalBaseFault() : InternalBaseFault( ) {}
	WInternalBaseFault( const WInternalBaseFault& );
	virtual ~WInternalBaseFault() { this->free( ); }
	std::string toString( const bool tabbed = false ) const;
	WInternalBaseFault( const std::string&,
			    time_t*,
			    std::string* desc,
			    int* failcode );

	WInternalBaseFault& operator=( const WInternalBaseFault& src ) { 
	  this->free();
	  this->set( src );
	  return *this; 
	}

      private:
	void set( const WInternalBaseFault& );
	void free( );
      };
    }
  }
}

#endif
