#ifndef EMIES_CLIENTLIB_WRAPPERS_GETACTSTATRESP_H
#define EMIES_CLIENTLIB_WRAPPERS_GETACTSTATRESP_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"
#include "glite/ce/es-client-api-c/ActivityStatus.h"
#include "glite/ce/es-client-api-c/InternalBaseFault.h"

#include <string>
#include <vector>
#include <map>

namespace emi_es {
  namespace client {
    namespace wrapper {
 	
	class GetActivityStatusResponse : public GetActivityStatusResponseType
	{
	  private:
	    GetActivityStatusResponse( ) : GetActivityStatusResponseType( ) {}
	    GetActivityStatusResponse( const GetActivityStatusResponse& ) {}
	    virtual ~GetActivityStatusResponse( ) { }
	    GetActivityStatusResponse& operator=( const GetActivityStatusResponse& ) { return *this; }
	    
	  public:
	    void getActivityStatus( std::map<std::string, ActivityStatus>&,
				    std::map<std::string, InternalBaseFault>& ) const;
	    
	};
	   
    }
    
  }
  
}

#endif
