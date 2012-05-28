#include "glite/ce/es-client-api-c/ActivityStatus.h"
#include <boost/lexical_cast.hpp>
#include "glite/ce/es-client-api-c/util.h"

using namespace std;

namespace wr = emi_es::client::wrapper;
namespace util = emi_es::client::util;

map<string, wr::ActivityStatus::ACTIVITYSTATUS> *wr::ActivityStatus::StatusStringToNum = 0;
boost::recursive_mutex wr::ActivityStatus::s_mutex;

char* wr::ActivityStatus::ACTIVITYSTATUS_STRING[] = {
  "ACCEPTED", 
  "PREPROCESSING",
  "PROCESSING",
  "PROCESSING_ACCEPTING",
  "PROCESSING_QUEUED",
  "PROCESSING_RUNNING",
  "POSTPROCESSING",
  "TERMINAL"
};

char *wr::ActivityStatus::ACTIVITYSTATUSATTRS_STRING[] = {
  "VALIDATING",
  "SERVER_PAUSED", 
  "CLIENT_PAUSED", 
  "CLIENT_STAGEIN_POSSIBLE", 
  "CLIENT_STAGEOUT_POSSIBLE", 
  "PROVISIONING", 
  "DEPROVISIONING",
  "SERVER_STAGEIN", 
  "SERVER_STAGEOUT", 
  "BATCH_SUSPEND", 
  "APP_RUNNING", 
  "PREPROCESSING_CANCEL", 
  "PROCESSING_CANCEL", 
  "POSTPROCESSING_CANCEL", 
  "VALIDATION_FAILURE", 
  "PREPROCESSING_FAILURE", 
  "PROCESSING_FAILURE", 
  "POSTPROCESSING_FAILURE", 
  "APP_FAILURE"
};

/**
 *
 *
 *
 *
 *
 *
 */
wr::ActivityStatus::ACTIVITYSTATUS
wr::ActivityStatus::getStatusNumber( const string& status ) {
  {
    boost::recursive_mutex::scoped_lock L( s_mutex );
    if(!StatusStringToNum) {
      StatusStringToNum = new map<string, ACTIVITYSTATUS>();
      StatusStringToNum->insert( make_pair("ACCEPTED", ACCEPTED));
      StatusStringToNum->insert( make_pair("PREPROCESSING", PREPROCESSING));
      StatusStringToNum->insert( make_pair("PROCESSING", PROCESSING));
      StatusStringToNum->insert( make_pair("PROCESSING_ACCEPTING", PROCESSING_ACCEPTING));
      StatusStringToNum->insert( make_pair("PROCESSING_QUEUED", PROCESSING_QUEUED));
      StatusStringToNum->insert( make_pair("PROCESSING_RUNNING", PROCESSING_RUNNING));
      StatusStringToNum->insert( make_pair("POSTPROCESSING", POSTPROCESSING));
      StatusStringToNum->insert( make_pair("TERMINAL", TERMINAL));
    }
  }

  map<string, ACTIVITYSTATUS>::const_iterator it = StatusStringToNum->find(status);
  if(it == StatusStringToNum->end( ) )
    return NA;
  else
    return it->second;
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::ActivityStatus::ActivityStatus( const int status,
				    const vector<int>& attrs,
				    const time_t timestamp,
				    const string& desc)
{
  Status = (PrimaryActivityStatus)status;
  vector<int>::const_iterator it = attrs.begin();
  for( ; it != attrs.end( ); ++it )
    {
      Attribute.push_back( (ActivityStatusAttribute)*it );
    }
  Timestamp = timestamp;
  Description = new string( desc );
  //ActivityID = ID;
}

/**
 *
 *
 *
 *
 *
 *
 */
void
wr::ActivityStatus::set( const ActivityStatus& src )
{
  //ActivityID = src.ActivityID;
  Status = src.Status;
  Attribute = src.Attribute;
  Timestamp = src.Timestamp;
  
  Description = 0;
  
  if( src.Description )
    Description = new string( *src.Description );
}


/**
 *
 *
 *
 *
 *
 *
 */
wr::ActivityStatus::ActivityStatus( const ActivityStatus& src )
  :  ActivityStatusType()
{
  this->set( src );
}

/**
 *
 *
 *
 *
 *
 *
 */
void
wr::ActivityStatus::free( void )
{
  delete Description;
}

/**
 *
 *
 *
 *
 *
 *
 */
string
wr::ActivityStatus::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "Status=" + boost::lexical_cast<string>( Status );
  out += tab + "Attribute={" + util::join( Attribute, ", " ) + "}";
  out += tab + "Timestamp=" + boost::lexical_cast<string>(Timestamp);
  out += tab + "Description=" + (Description ? *Description : "N/A");

  return out;
}

/**
 *
 *
 *
 *
 *
 *
 */
void
wr::ActivityStatus::getStatusAttributes( std::vector<ACTIVITYSTATUSATTRS>& target) const
{
  std::vector<ActivityStatusAttribute >::const_iterator it;
  for( it = Attribute.begin( ); it != Attribute.end( ); ++ it ) 
    {
      target.push_back( (ACTIVITYSTATUSATTRS)*it );
    }
}

/**
 *
 *
 *
 *
 *
 *
 */
void
wr::ActivityStatus::getStatusAttributesString( std::vector<std::string>& target) const
{
  std::vector<ActivityStatusAttribute >::const_iterator it;
  for( it = Attribute.begin( ); it != Attribute.end( ); ++ it )
    {
      target.push_back( ACTIVITYSTATUSATTRS_STRING[ *it ] );
    }
}

/**
 *
 *
 *
 *
 *
 *
 */
std::string 
wr::ActivityStatus::getTimestampString( ) const
{
  return util::time_to_string( Timestamp );
}
