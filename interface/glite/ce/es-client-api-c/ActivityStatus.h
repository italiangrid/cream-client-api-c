#ifndef EMIES_CLIENTLIB_WRAPPERS_ACSTATUS_H
#define EMIES_CLIENTLIB_WRAPPERS_ACSTATUS_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>
#include <map>

#include <boost/thread/recursive_mutex.hpp>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class ActivityStatus : public ActivityStatusType 
      {
      public:

	ActivityStatus() : ActivityStatusType() {}
	ActivityStatus( const ActivityStatus& );
	virtual ~ActivityStatus() { this->free( ); }
	ActivityStatus( const int,
			const std::vector<int>&,
			const time_t,
			const std::string&);


	enum ACTIVITYSTATUS {
	  NA                   = -1,
	  ACCEPTED             = ESTYPES__PrimaryActivityStatus__ACCEPTED,
	  PREPROCESSING        = ESTYPES__PrimaryActivityStatus__PREPROCESSING,
	  PROCESSING           = ESTYPES__PrimaryActivityStatus__PROCESSING,
	  PROCESSING_ACCEPTING = ESTYPES__PrimaryActivityStatus__PROCESSING_ACCEPTING,
	  PROCESSING_QUEUED    = ESTYPES__PrimaryActivityStatus__PROCESSING_QUEUED,
	  PROCESSING_RUNNING   = ESTYPES__PrimaryActivityStatus__PROCESSING_RUNNING,
	  POSTPROCESSING       = ESTYPES__PrimaryActivityStatus__POSTPROCESSING,
	  TERMINAL             = ESTYPES__PrimaryActivityStatus__TERMINAL
	};

	static char *ACTIVITYSTATUS_STRING[];

	enum ACTIVITYSTATUSATTRS {
	  VALIDATING = ESTYPES__ActivityStatusAttribute__VALIDATING,
	  SERVER_PAUSED = ESTYPES__ActivityStatusAttribute__SERVER_PAUSED,
	  PAUSED = ESTYPES__ActivityStatusAttribute__CLIENT_PAUSED,
	  CLIENT_STAGEIN_POSSIBLE = ESTYPES__ActivityStatusAttribute__CLIENT_STAGEIN_POSSIBLE,
	  CLIENT_STAGEOUT_POSSIBLE = ESTYPES__ActivityStatusAttribute__CLIENT_STAGEOUT_POSSIBLE,
	  PROVISIONING = ESTYPES__ActivityStatusAttribute__PROVISIONING,
	  DEPROVISIONING = ESTYPES__ActivityStatusAttribute__DEPROVISIONING,
	  SERVER_STAGEIN = ESTYPES__ActivityStatusAttribute__SERVER_STAGEIN,
	  SERVER_STAGEOUT = ESTYPES__ActivityStatusAttribute__SERVER_STAGEOUT,
	  BATCH_SUSPEND = ESTYPES__ActivityStatusAttribute__BATCH_SUSPEND,
	  APP_RUNNING = ESTYPES__ActivityStatusAttribute__APP_RUNNING,
	  PREPROCESSING_CANCEL = ESTYPES__ActivityStatusAttribute__PREPROCESSING_CANCEL,
	  PROCESSING_CANCEL = ESTYPES__ActivityStatusAttribute__PROCESSING_CANCEL,
	  POSTPROCESSING_CANCEL = ESTYPES__ActivityStatusAttribute__POSTPROCESSING_CANCEL,
	  VALIDATION_FAILURE = ESTYPES__ActivityStatusAttribute__VALIDATION_FAILURE,
	  PREPROCESSING_FAILURE = ESTYPES__ActivityStatusAttribute__PREPROCESSING_FAILURE,
	  PROCESSING_FAILURE = ESTYPES__ActivityStatusAttribute__PROCESSING_FAILURE,
	  POSTPROCESSING_FAILURE = ESTYPES__ActivityStatusAttribute__POSTPROCESSING_FAILURE,
	  APP_FAILURE = ESTYPES__ActivityStatusAttribute__APP_FAILURE,
	  EXPIRED = ESTYPES__ActivityStatusAttribute__EXPIRED
	};

	static char* ACTIVITYSTATUSATTRS_STRING[];

	ACTIVITYSTATUS getStatusNum( ) const { return (ACTIVITYSTATUS)Status; }
	std::string    getStatusString( ) const { return ACTIVITYSTATUS_STRING[Status]; }

	void getStatusAttributes( std::vector<ACTIVITYSTATUSATTRS>& ) const;
	void getStatusAttributesString( std::vector<std::string>& ) const;

	time_t getTimestamp( ) const { return Timestamp; }
	std::string getTimestampString( ) const;

	std::string getDescription( ) const {
	  if(Description) return *Description;
	  else return "";
	}

	std::string toString( const bool tabbed = false ) const;

	static ACTIVITYSTATUS getStatusNumber( const std::string& ) ;

      private:
	static std::map<std::string, ACTIVITYSTATUS> *StatusStringToNum;
	static boost::recursive_mutex  s_mutex;

	void set( const ActivityStatus& );
	void free( );

      public:
	ActivityStatus& operator=(const ActivityStatus& src )
	  {
	    this->free();
	    this->set( src );
	    return *this;
	  }
      };
    }
  }
}

#endif
