#ifndef EMIES_CLIENTLIB_WRAPPERS_RES_H
#define EMIES_CLIENTLIB_WRAPPERS_RES_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/RuntimeEnvironment.h"
#include "glite/ce/es-client-api-c/ParallelEnvironment.h"
#include "glite/ce/es-client-api-c/OperatingSystem.h"
#include "glite/ce/es-client-api-c/CoprocessorType.h"
#include "glite/ce/es-client-api-c/NetworkInfoType.h"
#include "glite/ce/es-client-api-c/SlotRequirement.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <vector>
#include <string>

namespace emi_es {
  namespace client {
    namespace wrapper {
    
      class Resources : public ResourcesType
      {
      private:
	Resources( ) : ResourcesType( ) {}

      public:
	  Resources( const std::vector<OperatingSystem>& os, 
	  	     std::string* platform,
	  	     const std::vector<RuntimeEnvironment>& runtimes,
		     ParallelEnvironment* pe,
		     CoprocessorType* cop,
		     NetworkInfoType* netinfo,
		     int* nodes,
		     ULONG64* mem,
		     ULONG64* vmem,
		     ULONG64* disk,
		     bool* remotesessionaccess,
	  	     BenchmarkClassType* benchmark,
		     SlotRequirement* slotreq,
		     std::string* queuename,
		     ULONG64* cputime,
		     ULONG64* totcputime,
		     ULONG64* walltime );
	  	  
	  virtual ~Resources( ) { this->free(); }
	  Resources( const Resources& );
	  
	  std::string toString( const bool tabbed = false ) const;
	  
      private:
          Resources& operator=(const Resources& ) { return *this; }
	  void free( );
	  void set( const Resources& );
      };
      
    }
  }
}

#endif
