#include "glite/ce/es-client-api-c/WNotification.h"
#include <boost/lexical_cast.hpp>
#include "glite/ce/es-client-api-c/util.h"

using namespace std;

namespace wr = emi_es::client::wrapper;
namespace util = emi_es::client::util;

map<string, ProtocolTypeEnumeration> *wr::WNotification::s_ProtoStringToNum = 0;
boost::recursive_mutex wr::WNotification::s_mutex;

char* wr::WNotification::PROTOCOLTYPEENUM_STRING[] = {
  "email" 
};


/**
 *
 *
 *
 *
 *
 *
 */
ProtocolTypeEnumeration
wr::WNotification::getProtoNumber( const string& proto ) {
  {
    boost::recursive_mutex::scoped_lock L( s_mutex );
    if(!s_ProtoStringToNum) {
      s_ProtoStringToNum = new map<string, ProtocolTypeEnumeration>();
      s_ProtoStringToNum->insert( make_pair("email", EMAIL));
    }
  }

  map<string, ProtocolTypeEnumeration>::const_iterator it = s_ProtoStringToNum->find(proto);
  if(it == s_ProtoStringToNum->end( ) )
    return (ProtocolTypeEnumeration)UNKNOWN;
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
wr::WNotification::WNotification( const ProtocolTypeEnumeration protocol,
		      		  const vector<string>& recipient,
		      		  const vector<ActivityStatusState> onstate,
		      		  bool *_optional ) : Notification( )
{
  Protocol  = protocol;
  Recipient = recipient;
  OnState   = onstate;
  optional  = 0;
  if(_optional)
    optional = new bool(_optional);
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
wr::WNotification::set( const WNotification& src )
{
  optional  = 0;
  Protocol  = src.Protocol;
  Recipient = src.Recipient;
  OnState   = src.OnState;
  if(src.optional)
    optional  = new bool(*src.optional);
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::WNotification::WNotification( const WNotification& src )
  : Notification( )
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
wr::WNotification::free( )
{
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
wr::WNotification::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "Notification:";
  out += tab + "  Protocol=";
  out += boost::lexical_cast<string>(Protocol);
  out += tab + "  optional=";
  out += (optional ? boost::lexical_cast<string>(*optional) : "N/A");
  out += tab + "  Recipient={";
  out += util::join( Recipient, ", " ) + "}";
  out += tab + "  OnState={";
  out += util::join( OnState, ", " ) + "}";
  return out;
}
