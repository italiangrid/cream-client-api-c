#ifndef EMIES_CLIENTLIB_WRAPPERS_ACTRESP_H
#define EMIES_CLIENTLIB_WRAPPERS_ACTRESP_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/WInternalBaseFault.h"
#include "glite/ce/es-client-api-c/WActivityStatus.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include "glite/ce/es-client-api-c/util.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
	
      class WActivityCreationResponse : public ActivityCreationResponse
      {
      private:
	WActivityCreationResponse() : ActivityCreationResponse( ) { }
      public:
      
        enum FAULT_TYPE {
	  NONE = 0,
 	  NUM_INVALIDACTIVITYDESCRIPTIONSEMANTIC,
	  NUM_INVALIDACTIVITYDESCRIPTION,
	  NUM_UNSUPPORTEDCAPABILITY,
 	  NUM_INTERNALBASE,
 	  NUM_ACCESSCONTROL
 	};
      
        FAULT_TYPE get_fault_type( ) const { return m_fault_type; }
	void       set_fault_type( const int ftype ) { m_fault_type = (FAULT_TYPE)ftype; }
	void       set_fault_message( const std::string& fmex ) { m_fault_message =fmex; }
      
	WActivityCreationResponse( const WActivityCreationResponse& );
	virtual ~WActivityCreationResponse( ) { this->free( ); }
	WActivityCreationResponse( const FAULT_TYPE,
				   WInternalBaseFault*,
				   std::string*,
				   std::string*,
				   std::string*,
				   WActivityStatus*,
				   time_t*,
				   DirectoryReference*,
				   DirectoryReference*,
				   DirectoryReference*
				  );
	
	std::string getActivityID( ) const { 
#if GSOAP_VERSION_NUM==20709
 	  return ActivityIDField;
#else

	  return (ActivityIDField ? *ActivityIDField : "N/A" );
#endif
	}

	std::string getActivityManagementURL( ) const { 
#if GSOAP_VERSION_NUM==20709
          return ActivityMgmtEndpointURLField;
#else
	  return (ActivityMgmtEndpointURLField ? *ActivityMgmtEndpointURLField : "N/A" );
#endif
	}
	
	std::string getResourceInfoURL( ) const { 
#if GSOAP_VERSION_NUM==20709
	  return ResourceInfoEndpointURLField;
#else
	  return (ResourceInfoEndpointURLField ? *ResourceInfoEndpointURLField : "N/A" );
#endif
	}

	WActivityStatus* getActivityStatus( ) const {
	  return (ActivityStatusField ? (WActivityStatus*)ActivityStatusField : 0 );
	}
	
	WActivityCreationResponse& operator=(const WActivityCreationResponse& src)
	{
	  this->free( );
	  this->set( src );
	  return *this;
	}

	std::vector<std::string> getStageInDirectory( ) const { 
	  if(!StageInDirectory) return std::vector<std::string>();
	  else return StageInDirectory->URL;
	}

	std::vector<std::string> getStageOutDirectory( ) const { 
	  if(!StageOutDirectory) return std::vector<std::string>();
	  else return StageOutDirectory->URL;
	}

	std::vector<std::string> getSessionDirectory( ) const { 
	  if(!SessionDirectory) return std::vector<std::string>();
	  return SessionDirectory->URL;
	}

	time_t getETNSC( ) const { 
	  return ( ETNSC ? *ETNSC : 0 );
	}

	std::string getETNSCString( ) const {
	  return (ETNSC ? util::time_to_string( *ETNSC ) : "N/A" );
	}

	std::string toString( const bool tabbed = false ) const;
	
      private:
        FAULT_TYPE m_fault_type;
	std::string m_fault_message;
	void set( const WActivityCreationResponse& );
	void free( );				  
				  
      };
    }
  }
}

#endif
