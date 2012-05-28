#include "glite/ce/es-client-api-c/RemoteLoggingWrapper.h"
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
wr::RemoteLoggingWrapper::RemoteLoggingWrapper( const string& servicetype,
				  string* url,
				  const bool _optional )
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
wr::RemoteLoggingWrapper::set( const RemoteLoggingWrapper& src )

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
wr::RemoteLoggingWrapper::RemoteLoggingWrapper( const RemoteLoggingWrapper& src )
  : RemoteLoggingType( )
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
wr::RemoteLoggingWrapper::free( )
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
wr::RemoteLoggingWrapper::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "ServiceType=";
  out += ServiceType;
  out += tab + "URL=";
  out += (URL ? *URL : "NULL") ;
  out += tab + "optional=";
  out += boost::lexical_cast<string>( optional );

  return out;
}
