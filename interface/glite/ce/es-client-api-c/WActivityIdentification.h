#ifndef EMIES_CLIENTLIB_WRAPPERS_ACTI_H
#define EMIES_CLIENTLIB_WRAPPERS_ACTI_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"


#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
	
	class WActivityIdentification : public ActivityIdentification
	{
	private:
	  WActivityIdentification() : ActivityIdentification( ) { }
	    
	public:

	  WActivityIdentification( std::string* name,
				   std::string* Description,
				   ActivityTypeEnumeration* type,
				   const std::vector<std::string>& annotation );
	    
	  virtual ~WActivityIdentification( ) { this->free( ); }
	  WActivityIdentification( const WActivityIdentification& );
	    
	  static char *ACTIVITYTYPE_STRING[];

	  std::string toString( const bool tabbed = false ) const;

	private:
	  void free( );
	  void set( const WActivityIdentification& );
	  WActivityIdentification& operator=(const WActivityIdentification& ) { return *this; }
	};
	
    }
  }
}

#endif
