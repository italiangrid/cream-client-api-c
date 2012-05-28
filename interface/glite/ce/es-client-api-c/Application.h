#ifndef EMIES_CLIENTLIB_WRAPPERS_APPL_H
#define EMIES_CLIENTLIB_WRAPPERS_APPL_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/ExecutableType.h"
#include "glite/ce/es-client-api-c/RemoteLoggingWrapper.h"
#include "glite/ce/es-client-api-c/Notification.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {    
      
      class Application : public ApplicationType
      {
      private:
        Application( ) : ApplicationType(){}
	
      public:
	Application( const ExecutableType* exe, 
		     std::string* in, 
		     std::string* out, 
		     std::string* err, 
		     const std::vector<OptionType>& env, 
		     const std::vector<ExecutableType>& preexe, 
		     const std::vector<ExecutableType>& postexe, 
		     const std::vector<RemoteLoggingWrapper>& rm, 
		     OptionalTime* exptime, 
		     OptionalDuration* wipetime, 
		     const std::vector<Notification>& notif );
	
	virtual ~Application( ) { this->free( ); }
	
	Application( const Application& );
	
	std::string toString( const bool tabbed = false ) const;

      private:
	void set( const Application& );
	void free( );
	Application& operator=(const Application& ) { return *this; }
	
      };
      
    }
  }
}

#endif
