#ifndef EMIES_CLIENTLIB_WRAPPERS_RES_H
#define EMIES_CLIENTLIB_WRAPPERS_RES_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/WRuntimeEnvironment.h"
#include "glite/ce/es-client-api-c/WParallelEnvironment.h"
#include "glite/ce/es-client-api-c/WOperatingSystem.h"
#include "glite/ce/es-client-api-c/WCoprocessorType.h"
#include "glite/ce/es-client-api-c/WNetworkInfoType.h"
#include "glite/ce/es-client-api-c/WSlotRequirement.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <vector>
#include <string>

namespace emi_es {
  namespace client {
    namespace wrapper {
    
      class WResources : public Resources
      {
      private:
	WResources( ) : Resources( ) {}

      public:
	  WResources( const std::vector<WOperatingSystem>& os, 
	  	      std::string* platform,
	  	      const std::vector<WRuntimeEnvironment>& runtimes,
		      WParallelEnvironment* pe,
		      WCoprocessorType* cop,
		      WNetworkInfoType* netinfo,
		      NodeAccessEnumeration* nodes,
		      ULONG64* mem,
		      ULONG64* vmem,
		      ULONG64* disk,
		      bool* remotesessionaccess,
	  	      Benchmark* benchmark,
		      WSlotRequirement* slotreq,
		      std::string* queuename,
		      ULONG64* cputime,
		      ULONG64* totcputime,
		      ULONG64* walltime );
	  	  
	  virtual ~WResources( ) { this->free(); }
	  WResources( const WResources& );
	  
	  std::string toString( const bool tabbed = false ) const;
	  
      private:
          WResources& operator=(const WResources& ) { return *this; }
	  void free( );
	  void set( const WResources& );
      };
      
    }
  }
}

#endif
