#ifndef EMIES_CLIENTLIB_WRAPPERS_TRG_H
#define EMIES_CLIENTLIB_WRAPPERS_TRG_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class Target : public TargetType
      {
	
      private:
	Target() : TargetType() {}
	
      public:
	Target( const std::string& uri,
		std::string* delegationid,
		const std::vector<OptionType>& option,
		bool* mandatory,
		int   creationflag,
		bool  useiffailure,
		bool  useifcancel,
		bool  useifsuccess );
	
	virtual ~Target( ) { this->free( ); }  
	Target( const Target& );
	
	
	std::string toString( const bool tabbed = false ) const;

	Target& operator=(const Target&);

      private:
	void set( const Target& );
	void free( );
      };
    }
  }
}

#endif
