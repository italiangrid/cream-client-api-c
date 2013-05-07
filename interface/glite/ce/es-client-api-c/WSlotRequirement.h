#ifndef EMIES_CLIENTLIB_WRAPPERS_SREQ_H
#define EMIES_CLIENTLIB_WRAPPERS_SREQ_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class WSlotRequirement : public SlotRequirement
      {
      private:
	WSlotRequirement( ) : SlotRequirement( ) { }
	
      public:
        WSlotRequirement( const ULONG64 num, SlotRequirement_SlotsPerHost* _sl, bool* excl );
	virtual ~WSlotRequirement( ) { this->free( ); }
	WSlotRequirement( const WSlotRequirement& );
	
	std::string toString(  const bool tabbed = false ) const;
	
      private:
        WSlotRequirement& operator=(const WSlotRequirement&);
        void set( const WSlotRequirement& );
	void free( );
      };
      
    }
  }
}

#endif
