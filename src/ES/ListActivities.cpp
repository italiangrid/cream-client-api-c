#include "glite/ce/es-client-api-c/ListActivities.h"
#include "glite/ce/es-client-api-c/util.h"
#include <boost/lexical_cast.hpp>


using namespace std;

namespace wr  = emi_es::client::wrapper;
namespace util = emi_es::client::util;

/**
 *
 *
 *
 *
 *
 *
 */
wr::ListActivities::ListActivities(  time_t* fromDate,
				     time_t* toDate,
				     int* limit,
				     const vector<ActivityStatus::ACTIVITYSTATUS> states,
				     const vector<ActivityStatus::ACTIVITYSTATUSATTRS> attrs )
{
  FromDate = 0; 
  ToDate   = 0;
  Limit    = 0;

  if(fromDate) {
    FromDate = new time_t;
    *(FromDate) = *fromDate;
  }

  if(toDate) {
    ToDate = new time_t;
    *(ToDate) = *toDate;
  }

  if(limit) {
    Limit = new int;
    *Limit = *limit;//( limit );
  }

  {
    vector<ActivityStatus::ACTIVITYSTATUS>::const_iterator it = states.begin();
    for( ; it != states.end( ); ++it ) {
      Status.push_back( (PrimaryActivityStatus)*it);
    }
  }

  {
    vector<ActivityStatus::ACTIVITYSTATUSATTRS>::const_iterator it = attrs.begin();
    for( ; it != attrs.end( ); ++it ) {
      StatusAttribute.push_back( (ActivityStatusAttribute)*it);
    }
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
wr::ListActivities::set( const ListActivities& src )
{ 
  FromDate = 0;
  ToDate = 0;
  Limit = 0;
  
  if(src.FromDate) {
    FromDate = new time_t;
    *(FromDate) = *src.FromDate;
  }

  if(src.ToDate) {
    ToDate = new time_t;
    *(ToDate) = *src.ToDate;
  }

  if(src.Limit) {
    Limit = new int;//string( *src.Limit );
    *Limit = *src.Limit;//limit;
  }

  Status = src.Status;// it is a vector of enums
  StatusAttribute = src.StatusAttribute; // it is a vector of enums
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::ListActivities::ListActivities( const ListActivities& src )
  : ListActivitiesType( )
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
wr::ListActivities::free( )
{
  delete FromDate;
  delete ToDate;
  delete Limit;
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
wr::ListActivities::toString( const bool tabbed ) const
{ 
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
  string out;
  
  out += "FromDate=" + (FromDate ? boost::lexical_cast<string>( *FromDate ) : "N/A");
  out += "\nToDate=" + (ToDate ? boost::lexical_cast<string>( *ToDate ) : "N/A");
  out += "\nLimit=" + (Limit ? boost::lexical_cast<string>( *Limit ) : "N/A");
  out += "\nStatus={" + util::join(Status, ", " ) +"}";
  out += "\nStatusAttribute={" + util::join(StatusAttribute, ", ") +"}";
  
  return out;
}
