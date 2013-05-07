#include "glite/ce/es-client-api-c/WRemoteLogging.h"
#include <boost/lexical_cast.hpp>

using namespace std;

namespace wr = emi_es::client::wrapper;

/**
 *
 *
 *
 *
 *
 *
 */
wr::WRemoteLogging::WRemoteLogging( const string& servicetype,
				    string* url,
				    const bool _optional ) : RemoteLogging( )
{
  ServiceType = servicetype;
  URL = 0;
  if(url)
    URL = new string( *url );
  optional = _optional;
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
wr::WRemoteLogging::set( const WRemoteLogging& src )

{
  URL = 0;
  
  ServiceType = src.ServiceType;

  if(src.URL )
    URL = new string( *src.URL );

  optional = src.optional;
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::WRemoteLogging::WRemoteLogging( const WRemoteLogging& src )
  : RemoteLogging( )
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
wr::WRemoteLogging::free( )
{
  delete URL;
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
wr::WRemoteLogging::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "RemoteLogging:";
  out += tab + "  ServiceType=";
  out += ServiceType;
  out += tab + "  URL=";
  out += (URL ? *URL : "NULL") ;
  out += tab + "  optional=";
  out += boost::lexical_cast<string>( optional );

  return out;
}
