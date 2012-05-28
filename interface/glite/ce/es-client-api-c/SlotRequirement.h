#ifndef EMIES_CLIENTLIB_WRAPPERS_SREQ_H
#define EMIES_CLIENTLIB_WRAPPERS_SREQ_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class SlotRequirement : public SlotRequirementType
      {
      private:
	SlotRequirement( ) : SlotRequirementType( ) { }
	
      public:
        SlotRequirement( const ULONG64 num, SlotsPerHostType* _sl, bool* excl );
	virtual ~SlotRequirement( ) { this->free( ); }
	SlotRequirement( const SlotRequirement& );
	
	std::string toString(  const bool tabbed = false ) const;
	
      private:
        SlotRequirement& operator=(const SlotRequirement&);
        void set( const SlotRequirement& );
	void free( );
      };
      
    }
  }
}

#endif
