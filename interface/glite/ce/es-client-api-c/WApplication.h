#ifndef EMIES_CLIENTLIB_WRAPPERS_APPL_H
#define EMIES_CLIENTLIB_WRAPPERS_APPL_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/WExecutable.h"
#include "glite/ce/es-client-api-c/WRemoteLogging.h"
#include "glite/ce/es-client-api-c/WNotification.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {    
      
      class WApplication : public Application
      {
      private:
        WApplication( ) : Application(){}
	
      public:
	WApplication( const WExecutable* exe, 
		      std::string* in, 
		      std::string* out, 
		      std::string* err, 
		      const std::vector<OptionType>& env, 
		      const std::vector<WExecutable>& preexe, 
		      const std::vector<WExecutable>& postexe, 
		      const std::vector<WRemoteLogging>& rm, 
		      OptionalTime* exptime, 
		      OptionalTime* wipetime, 
		      const std::vector<WNotification>& notif );
	
	virtual ~WApplication( ) { this->free( ); }
	
	WApplication( const WApplication& );
	
	std::string toString( const bool tabbed = false ) const;

      private:
	void set( const WApplication& );
	void free( );
	WApplication& operator=(const Application& ) { return *this; }
	
      };
      
    }
  }
}

#endif
