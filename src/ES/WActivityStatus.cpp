#include "glite/ce/es-client-api-c/WActivityStatus.h"
#include <boost/lexical_cast.hpp>
#include "glite/ce/es-client-api-c/util.h"

using namespace std;

namespace wr = emi_es::client::wrapper;
namespace util = emi_es::client::util;

map<string, ActivityStatusState> *wr::WActivityStatus::s_StatusStringToNum = 0;
boost::recursive_mutex wr::WActivityStatus::s_mutex;

char* wr::WActivityStatus::ACTIVITYSTATUS_STRING[] = {
  "ACCEPTED", 
  "PREPROCESSING",
  "PROCESSING",
  "PROCESSING_ACCEPTING",
  "PROCESSING_QUEUED",
  "PROCESSING_RUNNING",
  "POSTPROCESSING",
  "TERMINAL"
};

char *wr::WActivityStatus::ACTIVITYSTATUSATTRS_STRING[] = {
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
  "APP_FAILURE",
  "EXPIRED"
};

/**
 *
 *
 *
 *
 *
 *
 */
ActivityStatusState
wr::WActivityStatus::getStatusNumber( const string& status ) {
  {
    boost::recursive_mutex::scoped_lock L( s_mutex );
    if(!s_StatusStringToNum) {
      s_StatusStringToNum = new map<string, ActivityStatusState>();
      s_StatusStringToNum->insert( make_pair("ACCEPTED", ACCEPTED));
      s_StatusStringToNum->insert( make_pair("PREPROCESSING", PREPROCESSING));
      s_StatusStringToNum->insert( make_pair("PROCESSING", PROCESSING));
      s_StatusStringToNum->insert( make_pair("PROCESSING_ACCEPTING", PROCESSING_ACCEPTING));
      s_StatusStringToNum->insert( make_pair("PROCESSING_QUEUED", PROCESSING_QUEUED));
      s_StatusStringToNum->insert( make_pair("PROCESSING_RUNNING", PROCESSING_RUNNING));
      s_StatusStringToNum->insert( make_pair("POSTPROCESSING", POSTPROCESSING));
      s_StatusStringToNum->insert( make_pair("TERMINAL", TERMINAL));
    }
  }

  map<string, ActivityStatusState>::const_iterator it = s_StatusStringToNum->find(status);
  if(it == s_StatusStringToNum->end( ) )
    return (ActivityStatusState)UNKNOWN;
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
wr::WActivityStatus::WActivityStatus( const ActivityStatusState status,
				      const vector<ActivityStatusAttribute>& attrs,
				      const time_t timestamp,
				      string* desc) : ActivityStatus( )
{
  Status      = status;
  Attribute   = attrs;
  Timestamp   = timestamp;
  Description = 0;
  if( desc )
    Description = new string( *desc );
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
wr::WActivityStatus::set( const WActivityStatus& src )
{
  Status    = src.Status;
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
wr::WActivityStatus::WActivityStatus( const WActivityStatus& src )
  :  ActivityStatus()
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
wr::WActivityStatus::free( void )
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
wr::WActivityStatus::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "ActivityStatus:";
  out += tab + "  Status=" + boost::lexical_cast<string>( Status );
  out += tab + "  Attribute={" + util::join( Attribute, ", " ) + "}";
  out += tab + "  Timestamp=" + boost::lexical_cast<string>(Timestamp);
  out += tab + "  Description=" + (Description ? *Description : "N/A");

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
wr::WActivityStatus::getStatusAttributes( std::vector<ActivityStatusAttribute>& target) const
{
  std::vector<ActivityStatusAttribute >::const_iterator it;
  for( it = Attribute.begin( ); it != Attribute.end( ); ++ it ) 
    {
      target.push_back( *it );
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
wr::WActivityStatus::getStatusAttributesString( std::vector<std::string>& target) const
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
string 
wr::WActivityStatus::getTimestampString( ) const
{
  return util::time_to_string( Timestamp );
}
