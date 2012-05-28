#ifndef EMIES_CLIENTLIB_WRAPPERS_ACTD_H
#define EMIES_CLIENTLIB_WRAPPERS_ACTD_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/ActivityIdentification.h"
#include "glite/ce/es-client-api-c/Application.h"
#include "glite/ce/es-client-api-c/Resources.h"
#include "glite/ce/es-client-api-c/DataStaging.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
	
      class ActivityDescription : public ActivityDescriptionType
      {
	
      private:
	ActivityDescription( ) : ActivityDescriptionType( ) { }
	
      public:
	ActivityDescription(  ActivityIdentification* act,
			      const Application& appl,
			      Resources* res,
			      DataStaging* datas );
	
	virtual ~ActivityDescription() { this->free( ); }
	
	ActivityDescription( const ActivityDescription& );

	std::string toString( const bool tabbed = false ) const;
	ActivityDescription& operator=(const ActivityDescription& src) 
	  { this->free(); this->set(src); return *this;}

      private:
	void set( const ActivityDescription& );
	void free( );
	
      };
      
    }
  }
}

#endif
