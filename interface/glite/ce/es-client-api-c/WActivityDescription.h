#ifndef EMIES_CLIENTLIB_WRAPPERS_ACTD_H
#define EMIES_CLIENTLIB_WRAPPERS_ACTD_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/WActivityIdentification.h"
#include "glite/ce/es-client-api-c/WApplication.h"
#include "glite/ce/es-client-api-c/WResources.h"
#include "glite/ce/es-client-api-c/WDataStaging.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
	
      class WActivityDescription : public ActivityDescription
      {
	
      private:
	WActivityDescription( ) : ActivityDescription( ) { }
	
      public:
	WActivityDescription( WActivityIdentification* act,
			      WApplication* appl,
			      WResources* res,
			      WDataStaging* datas );
	
	virtual ~WActivityDescription() { this->free( ); }
	
	WActivityDescription( const WActivityDescription& );
	
	std::string toString( const bool tabbed = false ) const;
	WActivityDescription& operator=(const WActivityDescription& src) 
	  { this->free(); this->set(src); return *this;}

      private:
	void set( const WActivityDescription& );
	void free( );
	
      };
      
    }
  }
}

#endif
