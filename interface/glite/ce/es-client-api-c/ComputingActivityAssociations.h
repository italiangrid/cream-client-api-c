#ifndef EMIES_CLIENTLIB_WRAPPERS_COMPACTASS_H
#define EMIES_CLIENTLIB_WRAPPERS_COMPACTASS_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
        
      class ComputingActivityAssociations : public ComputingActivityAssociationsType
      {
      private:
	ComputingActivityAssociations( ) : ComputingActivityAssociationsType( ) { }
      public:
	ComputingActivityAssociations( const std::string&,
				       const std::string&,
				       const std::string&,
				       const std::vector<std::string>& );

	ComputingActivityAssociations( const ComputingActivityAssociations& src) { this->set( src ); }
	virtual ~ComputingActivityAssociations( ) { this->free(); }
       
	std::string toString( const bool tabbed = false ) const;

      private:
	void set( const ComputingActivityAssociations& );
	void free( );
	ComputingActivityAssociations& operator=( const ComputingActivityAssociations& ) { return *this; }

      };
    }
  }
}

#endif
