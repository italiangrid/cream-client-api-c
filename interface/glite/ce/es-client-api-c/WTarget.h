#ifndef EMIES_CLIENTLIB_WRAPPERS_TRG_H
#define EMIES_CLIENTLIB_WRAPPERS_TRG_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class WTarget : public Target
      {
	
      private:
	WTarget() : Target() {}
	
      public:
	WTarget( const std::string& uri,
		 std::string* delegationid,
		 const std::vector<OptionType>& option,
		 bool* mandatory,
		 CreationFlagEnumeration*   creationflag,
		 bool  *useiffailure,
		 bool  *useifcancel,
		 bool  *useifsuccess );
	
	virtual ~WTarget( ) { this->free( ); }  
	WTarget( const WTarget& );
	
	
	std::string toString( const bool tabbed = false ) const;

	WTarget& operator=(const WTarget&);

      private:
	void set( const WTarget& );
	void free( );
      };
    }
  }
}

#endif
