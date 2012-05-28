#ifndef EMIES_CLIENTLIB_WRAPPERS_IBFAULT_H
#define EMIES_CLIENTLIB_WRAPPERS_IBFAULT_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
	
      class InternalBaseFault : public InternalBaseFaultType
      {
      private:
	//InternalBaseFault() : ES_USCORETYPES__InternalBaseFault_USCOREType() {}
	//std::string ActivityID;

      public:
	//std::string getActivityID( ) const { return ActivityID; }
	//void setActivityID( const std::string& id ) { ActivityID = id; }
	InternalBaseFault() : InternalBaseFaultType( ) {}
	InternalBaseFault( const InternalBaseFault& );
	virtual ~InternalBaseFault() { this->free( ); }
	std::string toString( const bool tabbed = false ) const;
	InternalBaseFault( const std::string&,
			   const time_t,
			   const std::string& desc,
			   const int failcode );

	InternalBaseFault& operator=( const InternalBaseFault& src ) { 
	  this->free();
	  this->set( src );
	  return *this; 
	}

      private:
	void set( const InternalBaseFault& );
	void free( );
      };
    }
  }
}

#endif
