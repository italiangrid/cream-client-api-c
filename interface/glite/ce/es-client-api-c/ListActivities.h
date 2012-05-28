#ifndef EMIES_CLIENTLIB_WRAPPERS_LISTA_H
#define EMIES_CLIENTLIB_WRAPPERS_LISTA_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/ActivityStatus.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
	
      class ListActivities : public ListActivitiesType
      {
	
      private:
	ListActivities() : ListActivitiesType( ) { }
	
      public:
      ListActivities(  time_t* fromDate,
		       time_t* toDate,
		       int* limit,
		       const std::vector<ActivityStatus::ACTIVITYSTATUS>      states,
		       const std::vector<ActivityStatus::ACTIVITYSTATUSATTRS> attrs );
	
	virtual ~ListActivities() { this->free( ); }
	
	ListActivities( const ListActivities& );

	std::string toString( const bool tabbed = false ) const;

	ListActivities& operator=(const ListActivities& src) 
	  { this->free(); this->set(src); return *this; }

      private:
	void set( const ListActivities& );
	void free( );
	
      };
      
    }
  }
}

#endif
