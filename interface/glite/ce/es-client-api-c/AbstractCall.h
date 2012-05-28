#ifndef EMIES_CLIENTLIB_COMM_ABSCALL_H
#define EMIES_CLIENTLIB_COMM_ABSCALL_H

#include "stdsoap2.h"
#include "glite/ce/es-client-api-c/es_client_soapStub.h"

#include "glite/ce/es-client-api-c/InternalBaseFault.h"
#include "glite/ce/es-client-api-c/ComputingActivity.h"
#include "glite/ce/es-client-api-c/ActivityCreationResponse.h"

#include <string>
#include <map>
#include <vector>

extern "C" {
#undef IOV_MAX
#include "glite/security/glite_gsplugin.h"
};

namespace emi_es {

  namespace client {

    namespace wrapper {
      class CreateActivities;
    }

    namespace comm {
      
      class AbstractCall {
	
      public:

	enum ACTIVITYMANAGEMENTCALLS {
	  CANCEL  = 0,
	  WIPE,
	  PAUSE,
	  RESTART,
	  RESUME,
	  STATUS
	};

	enum NOTIFYMESSAGE {
	  CLIENT_DATAPULL_DONE = 0,
	  CLIENT_DATAPUSH_DONE
	};
	
	enum SOAP_CALL_ERROR_CODES {
	  SOAP_CALL_ERROR_TIMEOUT      = 0,
	  SOAP_CALL_ERROR_CONNECT      = 1 ,
	  SOAP_CALL_ERROR_UNKNOWNFAULT = 2,
          SOAP_CALL_ERROR_FAULT = 3,
	  SOAP_CALL_ERROR_INTERNALBASEFAULT = SOAP_TYPE_ESTYPES__InternalBaseFault_USCOREType,
	  SOAP_CALL_ERROR_UNSUPPORTEDCAPABILITY = SOAP_TYPE__ESCREATIONTYPES__UnsupportedCapabilityFault,
	  SOAP_CALL_ERROR_INVALIDACTIVITYDESCSEMANTIC = SOAP_TYPE__ESCREATIONTYPES__InvalidActivityDescriptionSemanticFault,
	  SOAP_CALL_ERROR_INVALIDACTIVITYDESC = SOAP_TYPE__ESCREATIONTYPES__InvalidActivityDescriptionFault,
	  SOAP_CALL_ERROR_VECTORLIMITEXCEEDED = SOAP_TYPE__ESTYPES__VectorLimitExceededFault,
	  SOAP_CALL_ERROR_ACCESSCONTROL = SOAP_TYPE__ESTYPES__AccessControlFault,
	  SOAP_CALL_ERROR_INVALIDACTIVITYID = SOAP_TYPE__ESACTIVITYTYPES__InvalidActivityIDFault,
	  SOAP_CALL_ERROR_UNKNOWNACTIVITYID = SOAP_TYPE__ESACTIVITYTYPES__UnknownActivityIDFault,
	  SOAP_CALL_ERROR_UNABLERETRIEVESTATUS = SOAP_TYPE__ESACTIVITYTYPES__UnableToRetrieveStatusFault,
	  SOAP_CALL_ERROR_UNKNOWNGLUE2ACTIVITYATTR = SOAP_TYPE__ESACTIVITYTYPES__UnknownGlue2ActivityAttributeFault,
	  SOAP_CALL_ERROR_OPERATIONNOTALLOWED = SOAP_TYPE__ESACTIVITYTYPES__OperationNotAllowedFault,
	  SOAP_CALL_ERROR_ACTIVITYNOTFOUND = SOAP_TYPE__ESACTIVITYTYPES__ActivityNotFoundFault,
	  SOAP_CALL_ERROR_INTERNALNOTIF = SOAP_TYPE__ESACTIVITYTYPES__InternalNotificationFault,
	  SOAP_CALL_ERROR_OPERATIONNOTPOSSIBLE = SOAP_TYPE__ESACTIVITYTYPES__OperationNotPossibleFault,
	  SOAP_CALL_ERROR_INVALIDACTIVITYSTATE = SOAP_TYPE__ESACTIVITYTYPES__InvalidActivityStateFault,
	  SOAP_CALL_ERROR_ACTIVITYNOTINTERMINALSTATE = SOAP_TYPE__ESACTIVITYTYPES__ActivityNotInTerminalStateFault,
	  SOAP_CALL_ERROR_INVALIDACTIVITYLIMIT = SOAP_TYPE__ESACTIVITYTYPES__InvalidActivityLimitFault,
	  SOAP_CALL_ERROR_INVALIDPARAMETER = SOAP_TYPE__ESACTIVITYTYPES__InvalidParameterFault,
	  SOAP_CALL_ERROR_UNKNOWNDELEGID = SOAP_TYPE__ESDELEGATIONTYPES__UnknownDelegationIDFault,
	  SOAP_CALL_ERROR_INTERNALSERVICEDELEG = SOAP_TYPE__ESDELEGATIONTYPES__InternalServiceDelegationFault,
	  SOAP_CALL_ERROR_NOTSUPPORTEDQUERYDIALECT = SOAP_TYPE__ESRESOURCEINFOTYPES__NotSupportedQueryDialectFault,
	  SOAP_CALL_ERROR_NOTVALIDQUERYSTATEMENT = SOAP_TYPE__ESRESOURCEINFOTYPES__NotValidQueryStatementFault,
	  SOAP_CALL_ERROR_UNKNOWNQUERY = SOAP_TYPE__ESRESOURCEINFOTYPES__UnknownQueryFault,
	  SOAP_CALL_ERROR_INTERNALRESOURCEINFO = SOAP_TYPE__ESRESOURCEINFOTYPES__InternalResourceInfoFault,
	  SOAP_CALL_ERROR_RESOURCEINFONOTFOUND = SOAP_TYPE__ESRESOURCEINFOTYPES__ResourceInfoNotFoundFault,
	  SOAP_CALL_ERROR_UNKNOWNTYPE = 4
	};

	//static char *SOAP_CALL_ERROR_CODES_STRING[];

      private:
	glite_gsplugin_Context  m_gsoap_plugin_context;
	std::string             m_certificate_file;
	std::string             m_key_file;
	int                     m_soap_timeout;

      protected:
	struct soap*            m_SOAP;
	std::string             m_endpoint;

      public:
	virtual ~AbstractCall( ) throw();
	virtual bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES&  ) = 0;
	AbstractCall( const std::string& endpoint );

	void set_soap_timeout( const int T) { m_soap_timeout = T; }

	bool init( const std::string&,
		   const std::string&,
		   std::string& error );

	static void get_string_error( std::string&, const wrapper::InternalBaseFault& );

	virtual void   getResponse( std::vector<emi_es::client::wrapper::ActivityCreationResponse>& ) const {}

	virtual void   getResponse( std::map<std::string, wrapper::ComputingActivity>&, 
				    std::map<std::string, wrapper::InternalBaseFault>& ) const {}

	virtual void   getResponse( std::map<std::string, wrapper::ActivityStatus>& states,
				    std::map<std::string, wrapper::InternalBaseFault>& faults ) const {}

	virtual void   getResponse( time_t&, std::string&, std::string& ) const {} // subject/issuer

	virtual void   getResponse( std::string&, std::string& ) const {} //delegation id, anche server certificate
	virtual void   getResponse( std::string& ) const {} // putdeleg

	virtual void   getResponse(  bool&, std::vector<std::string>& ) const {}

	virtual void   getResponse( std::map<std::string, long long int >& successfull,
				    std::map<std::string, wrapper::InternalBaseFault>& failed ) const {}

	virtual void   getResponse( std::vector<std::pair<std::string, wrapper::InternalBaseFault> >& ) const {}
	
      protected:
	static void get_string_error( std::string&, InternalBaseFaultType* );

	void process_error( std::string&, enum SOAP_CALL_ERROR_CODES& );

	bool check_sub_fault( soap*, std::string& );

      private:
	bool init_credentials( const std::string&,
			       const std::string&,
			       std::string& error );

	bool init_soap( std::string& error );
	
      };

    }
  }
}

#endif
