#include "glite/ce/es-client-api-c/WRuntimeEnvironment.h"
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
wr::WRuntimeEnvironment::WRuntimeEnvironment( const string& _Name,
			      		      string* _Version,
			      		      const vector<string>& _Option,
			      		      const bool _optional )
{  
  this->Name = _Name;
  if(_Version)
    this->Version = new string(*_Version);
  else
    this->Version = 0;
  this->Option = _Option;
  this->optional = _optional;
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::WRuntimeEnvironment::WRuntimeEnvironment(const WRuntimeEnvironment& src ) 
  : RuntimeEnvironment( )
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
wr::WRuntimeEnvironment::set( const WRuntimeEnvironment& src )
{
  Version = 0;

  Name = src.Name;
  if( src.Version )
    Version = new string( *src.Version );

  Option = src.Option;
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
void
wr::WRuntimeEnvironment::free( )
{
  delete Version;
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
wr::WRuntimeEnvironment::toString( const bool tabbed ) const
{

  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "Resource:";
  out += tab + "  Name=";
  out += Name;
  out += tab + "  Version=";
  out += *Version;
  
  vector<string>::const_iterator it = Option.begin( );
  int counter = 0;
  for( ; it != Option.end( ); ++it )
  {
    out += tab + "  Option[" + boost::lexical_cast<string>( counter ) + "]=";
    out += *it;
    counter++;
  }
  
  out += tab + "  optional=";
  out += boost::lexical_cast<string>( optional );
  return out;
}
