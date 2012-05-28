#ifndef EMIES_CLIENTLIB_WRAPPERS_LOCATION_H
#define EMIES_CLIENTLIB_WRAPPERS_LOCATION_H


#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"
#include "glite/ce/es-client-api-c/ExtensionsType.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class Location : public OGF_USCOREGLUE2SCHEMA__Location_USCOREt
      {
      private:
	Location( ) : OGF_USCOREGLUE2SCHEMA__Location_USCOREt( ) { }
	  
      public:
	Location( const std::string&,
		  const std::string&,
		  const std::string&,
		  const std::string&,
		  const float,
		  const float,
		  // for Entity
		  const std::string& _ID,
		  const std::string& _Name,
		  const std::vector<std::string>& info,
		  const ExtensionsType& exts,
		  const time_t c_time,
		  const ULONG64 val);

	Location( const Location& src ) { this->set( src ); }

	virtual ~Location( ) { this->free( ); }
	
	//std::string toString( const bool tabbed = false ) const;

      private:
	void set(const Location& );
	void free( );
	Location& operator=(const Location& ) { return *this; }
      };
    }
  }
}

#endif
