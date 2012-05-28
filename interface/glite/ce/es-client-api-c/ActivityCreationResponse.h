#ifndef EMIES_CLIENTLIB_WRAPPERS_ACTRESP_H
#define EMIES_CLIENTLIB_WRAPPERS_ACTRESP_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/InternalBaseFault.h"
#include "glite/ce/es-client-api-c/ActivityStatus.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include "glite/ce/es-client-api-c/util.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
	
      class ActivityCreationResponse : public ActivityCreationResponseType
      {
      private:
	ActivityCreationResponse() : ActivityCreationResponseType( ) { }
      public:
      
        enum FAULT_TYPE {
	  VECTORLIMITEXCEEDED = VectorLimitExceededFaultNumber,
	  INTERNALBASE        = InternalBaseFaultNumber,
	  ACCESSCONTROL       = AccessControlFaultNumber
	};
      
        FAULT_TYPE get_fault_type( ) const { return m_fault_type; }
      
	ActivityCreationResponse( const ActivityCreationResponse& );
	virtual ~ActivityCreationResponse( ) { this->free( ); }
	ActivityCreationResponse( InternalBaseFault*,
				  const std::string& ID,
				  const std::string& MgrURI,
				  const ActivityStatus&,
				  const time_t,
				  const DirectoryReferenceType&,
				  const DirectoryReferenceType&,
				  const DirectoryReferenceType& );
	
	InternalBaseFault* getFault() const { 
	  if(InternalBaseFaultField==0) 
	    return 0; 
	  else 
	    return (InternalBaseFault*)InternalBaseFaultField;
	}

	std::string getActivityID( ) const { 
	  if(!ActivityIDField) 
	    return ""; 
	  else 
	    return *ActivityIDField; 
	}

	std::string getActivityManagerURI( ) const { 
	  if(!ActivityManagerURI) 
	    return ""; 
	  else 
	    return *ActivityManagerURI; 
	}

	ActivityStatus* getActivityStatus( ) const {
	  if( !ActivityStatusField ) 
	    return 0;
	  else 
	    return (ActivityStatus*)ActivityStatusField;
	}
	
	ActivityCreationResponse& operator=(const ActivityCreationResponse& src)
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

	time_t getETNSC( ) const { if(ETNSC) return *ETNSC; else return 0; }

	std::string getETNSCString( ) const {
	  if(ETNSC)
	    return util::time_to_string( *ETNSC );
	  else
	    return "";
	}

	std::string toString( const bool tabbed = false ) const;
	
      private:
        FAULT_TYPE m_fault_type;
	void set( const ActivityCreationResponse& );
	void free( );				  
				  
      };
    }
  }
}

#endif
