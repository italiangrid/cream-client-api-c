#ifndef EMIES_CLIENTLIB_COMM_MANAGEACTCALL_H
#define EMIES_CLIENTLIB_COMM_MANAGEACTCALL_H

#include "glite/ce/es-client-api-c/AbstractCall.h"
#include "glite/ce/es-client-api-c/InternalBaseFault.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>
#include <map>

namespace emi_es {
  namespace client {
    namespace comm {
      
      class ManageActivityCall : public AbstractCall {
	friend class CallFactory;
      protected:	
	std::vector<std::string>                           m_IDs;
	std::map<std::string, long long int>               m_successful;
	std::map<std::string, wrapper::InternalBaseFault>  m_failed;


	ManageActivityCall( const std::string& endpoint,
			    const std::vector<std::string>& );
      public:
	virtual ~ManageActivityCall( ) throw() { }

	virtual bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& ) = 0;

	virtual void getResponse( std::map<std::string, long long int>& successfull,
	     			  std::map<std::string, wrapper::InternalBaseFault>& failed ) const
 	{ 
 	  successfull = m_successful; 
 	  failed      = m_failed; 
 	} 

      protected:
	void process_response( const std::vector<ResponseItemType*>& );
      };

    }
  }
}

#endif
