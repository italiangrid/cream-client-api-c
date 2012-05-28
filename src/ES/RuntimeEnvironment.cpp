#include "glite/ce/es-client-api-c/RuntimeEnvironment.h"
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
wr::RuntimeEnvironment::RuntimeEnvironment( const string& _Name,
			      		    string* _Version,
			      		    const vector<string>& _Option,
			      		    const bool _optional )
{ 
  if(getenv("ES_CLIENT_DEBUG_CTOR"))
    cerr << "RuntimeEnvironment::CTOR_PARAMS EXECUTED" << endl;
  
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
wr::RuntimeEnvironment::RuntimeEnvironment(const RuntimeEnvironment& src ) 
  : RuntimeEnvironmentType( )
{
  if(getenv("ES_CLIENT_DEBUG_CTOR") )
    cerr << "RuntimeEnvironment::COPYCTOR EXECUTED" << endl;
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
wr::RuntimeEnvironment::set( const RuntimeEnvironment& src )
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
wr::RuntimeEnvironment::free( )
{
  if(getenv("ES_CLIENT_DEBUG_DTOR") )
    cerr << "RuntimeEnvironment::free EXECUTED" << endl;

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
wr::RuntimeEnvironment::toString( const bool tabbed ) const
{

  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  
  out += tab + "Name=";
  out += Name;
  out += tab + "Version=";
  out += *Version;
  
  vector<string>::const_iterator it = Option.begin( );
  int counter = 0;
  for( ; it != Option.end( ); ++it )
  {
    out += tab + "Option[" + boost::lexical_cast<string>( counter ) + "]=";
    out += *it;
    counter++;
  }
  
  out += tab + "optional=";
  out += boost::lexical_cast<string>( optional );
  return out;
}
