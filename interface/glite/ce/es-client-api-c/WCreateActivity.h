#ifndef EMIES_CLIENTLIB_WRAPPERS_CRTACT_H
#define EMIES_CLIENTLIB_WRAPPERS_CRTACT_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/WActivityDescription.h"
//#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {    
      
      class WCreateActivity : public CreateActivity
      {
      private:
        WCreateActivity() : CreateActivity() {}
	
      public:
	WCreateActivity( const std::vector<WActivityDescription>& acts );
	  
	virtual ~WCreateActivity() { this->free( ); }
	WCreateActivity( const WCreateActivity& );

	std::string toString( const bool tabbed = false ) const;

      private:
	void set( const WCreateActivity& );
	void free( );
	WCreateActivity& operator=( const WCreateActivity& ) { return *this; }

      };
      
    }
  }
}

#endif
