#ifndef EMIES_CLIENTLIB_WRAPPERS_OS_H
#define EMIES_CLIENTLIB_WRAPPERS_OS_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class OperatingSystem : public OperatingSystemType
      {
      
      private:
        OperatingSystem( ) : OperatingSystemType() {}
      
      public:
	  OperatingSystem( const std::string& _Name,
			   std::string* _Family = 0,
			   std::string* _Version= 0 );
	  
	  virtual ~OperatingSystem( ) { this->free( ); }
	  OperatingSystem( const OperatingSystem& );
	  
	  std::string toString( const bool tabbed = false ) const;

      public:
          OperatingSystem& operator=( const OperatingSystem& src ) { this->free(); this->set(src); return *this;}

      private:
          
	  void set( const OperatingSystem& );
	  void free( );
      };
      
    }
  }
}

#endif
