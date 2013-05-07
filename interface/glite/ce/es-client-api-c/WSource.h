#ifndef EMIES_CLIENTLIB_WRAPPERS_SRC_H
#define EMIES_CLIENTLIB_WRAPPERS_SRC_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class WSource : public Source
      {
      private:
        WSource() : Source() {}
      
      public:	  
	virtual ~WSource( ) { this->free( ); }
	WSource( const WSource& );
	
	WSource( const std::string& uri, std::string* delegationid, const std::vector<OptionType>& option );
	std::string toString( const bool tabbed = false ) const;
	WSource& operator=(const WSource&);

      private:
	//          Source& operator=(const Source&);
	void set( const WSource& );
	void free( );
      };
    }
  }
}

#endif
