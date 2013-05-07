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
      
      class WActivityStatus : public ActivityStatus 
      {
      public:

	WActivityStatus() : ActivityStatus() {}
	WActivityStatus( const WActivityStatus& );
	virtual ~WActivityStatus() { this->free( ); }
	WActivityStatus( const ActivityStatusState,
			 const std::vector<ActivityStatusAttribute>&,
			 const time_t,
			 std::string*);

	static char *ACTIVITYSTATUS_STRING[];

	static char* ACTIVITYSTATUSATTRS_STRING[];

	ActivityStatusState getStatusNum( ) const { return Status; }
	std::string         getStatusString( ) const { return ACTIVITYSTATUS_STRING[Status]; }

	void getStatusAttributes( std::vector<ActivityStatusAttribute>& ) const;
	void getStatusAttributesString( std::vector<std::string>& ) const;

	std::string toString( const bool tabbed = false ) const;

	static ActivityStatusState getStatusNumber( const std::string& ) ;
	std::string getTimestampString( ) const;

      private:
	static std::map<std::string, ActivityStatusState> *s_StatusStringToNum;
	static boost::recursive_mutex  s_mutex;

	void set( const WActivityStatus& );
	void free( );

      public:
	WActivityStatus& operator=(const WActivityStatus& src )
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
