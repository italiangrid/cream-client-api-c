#ifndef EMIES_CLIENTLIB_WRAPPERS_NOTIF_H
#define EMIES_CLIENTLIB_WRAPPERS_NOTIF_H

//#include "autogen/ES_CLIENTStub.h"
#include "glite/ce/es-client-api-c/ActivityStatus.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <vector>
#include <string>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class Notification : public NotificationType
      {
      private:
	Notification( ) : NotificationType( ) { }
	
      public:
	Notification( const int protocol,
		      const std::vector<std::string>& recipient,
		      const std::vector<ActivityStatus::ACTIVITYSTATUS> onstate,
		      const bool optional );
	  
	  
	  
	virtual ~Notification() { this->free( ); }
	Notification( const Notification& );

	std::string toString( const bool tabbed = false ) const;

	Notification& operator=( const Notification& src ) { this->free( ); this->set(src); return *this; }

      private:
	void free( );
	void set( const Notification& );
      };
      
    }
  }
}

#endif
