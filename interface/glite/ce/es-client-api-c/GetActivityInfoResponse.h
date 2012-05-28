#ifndef EMIES_CLIENTLIB_WRAPPERS_GETACTINFORESP_H
#define EMIES_CLIENTLIB_WRAPPERS_GETACTINFORESP_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <map>

namespace emi_es {
  namespace client {
    namespace wrapper {
        
      class ComputingActivity;
      class InternalBaseFault;

      class GetActivityInfoResponse : public GetActivityInfoResponseType 
	{
	private:
	  GetActivityInfoResponse() : GetActivityInfoResponseType() {}
	  virtual ~GetActivityInfoResponse() {}
	  GetActivityInfoResponse( const GetActivityInfoResponse& ) {}
	  GetActivityInfoResponse& operator=( const GetActivityInfoResponse& ) { return *this; }

	public:
	  void getActivityInfoItems( std::map<std::string, ComputingActivity*>& sucessful, 
				     std::map<std::string, InternalBaseFault*>& failed) const;
	};
    }
  }
}

#endif
