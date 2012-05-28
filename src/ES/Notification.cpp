#include "glite/ce/es-client-api-c/Notification.h"
#include <boost/lexical_cast.hpp>
#include "glite/ce/es-client-api-c/util.h"

using namespace std;

namespace wr = emi_es::client::wrapper;
namespace util = emi_es::client::util;

/**
 *
 *
 *
 *
 *
 *
 */
wr::Notification::Notification( const int protocol,
		      		const vector<string>& recipient,
		      		const vector<ActivityStatus::ACTIVITYSTATUS> onstate,
		      		const bool _optional )
{
  Protocol = (ProtocolTypeEnumeration)protocol;
  Recipient = recipient;
  vector<ActivityStatus::ACTIVITYSTATUS>::const_iterator it = onstate.begin( );
  for( ; it != onstate.end(); ++it )
    {
      OnState.push_back( (PrimaryActivityStatus)*it );
    }

  optional = new bool(_optional);
  //  *optional = *optional;
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
wr::Notification::set( const Notification& src )
{
  optional = 0;
  Protocol  = src.Protocol;
  Recipient = src.Recipient;
  OnState   = src.OnState;
  if(src.optional) {
    optional  = new bool(*src.optional);
    //    *optional = *src.optional;
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
wr::Notification::Notification( const Notification& src )
  : NotificationType( )
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
wr::Notification::free( )
{
  if(getenv("ES_CLIENT_DEBUG_DTOR") )
    cerr << "Notification::free EXECUTED" << endl;

  //  if(optional) 
  delete optional;
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
wr::Notification::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "Protocol=";
  out += boost::lexical_cast<string>(Protocol);
  out += tab + "optional=";
  out += (optional ? boost::lexical_cast<string>(*optional) : "N/A");
  out += tab + "Recipient={";
  out += util::join( Recipient, ", " ) + "}";
  out += tab + "OnState={";
  out += util::join( OnState, ", " ) + "}";
  return out;
}
