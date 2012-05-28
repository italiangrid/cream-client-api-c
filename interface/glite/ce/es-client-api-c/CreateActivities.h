#ifndef EMIES_CLIENTLIB_WRAPPERS_CRTACT_H
#define EMIES_CLIENTLIB_WRAPPERS_CRTACT_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/ActivityDescription.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {    
      
      class CreateActivities : public CreateActivitiesType
      {
      private:
        CreateActivities() : CreateActivitiesType() {}
	
      public:
	CreateActivities( const std::vector<ActivityDescription>& acts );
	  
	virtual ~CreateActivities() { this->free( ); }
	CreateActivities( const CreateActivities& );

	std::string toString( const bool tabbed = false ) const;

      private:
	void set( const CreateActivities& );
	void free( );
	CreateActivities& operator=( const CreateActivities& ) { return *this; }
      };
      
    }
  }
}

#endif
