#ifndef EMIES_CLIENTLIB_WRAPPERS_SRC_H
#define EMIES_CLIENTLIB_WRAPPERS_SRC_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class Source : public SourceType
      {
      private:
        Source() : SourceType() {}
      
      public:	  
	virtual ~Source( ) { this->free( ); }
	Source( const Source& );
	
	Source( const std::string& uri, const std::string& delegationid, const std::vector<OptionType>& option );
	Source( const std::string& uri, const std::vector<OptionType>& option );
	std::string toString( const bool tabbed = false ) const;
	Source& operator=(const Source&);

      private:
	//          Source& operator=(const Source&);
	  void set( const Source& );
	  void free( );
      };
    }
  }
}

#endif
