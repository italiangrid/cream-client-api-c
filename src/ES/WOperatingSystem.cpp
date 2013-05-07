#include "glite/ce/es-client-api-c/WOperatingSystem.h"

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
wr::WOperatingSystem::WOperatingSystem( const ::string& _Name,
			 	        std::string* _Family,
			 	        std::string* _Version ) 
  : OperatingSystem( )
{
 
  Family = 0;
  Version= 0;

  Name    = _Name;

  if(_Family)
    Family  = new string( *_Family );
  
  if(_Version)
    Version = new string( *_Version );
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
wr::WOperatingSystem::set( const WOperatingSystem& src )
{
  Family = 0;
  Version = 0;
  Name = src.Name;
  if( src.Family )
    Family = new string( *src.Family );
  if(src.Version)
    Version = new string( *src.Version );
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::WOperatingSystem::WOperatingSystem( const WOperatingSystem& src )
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
wr::WOperatingSystem::free( )
{
  delete Family;
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
wr::WOperatingSystem::toString( const bool tabbed ) const
{

  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "OperatingSystem:";
  out += tab + "  Name=";
  out += Name;
  out += tab + "  Family=";
  out += (Family ? *Family : "N/A");
  out += tab + "  Version=";
  out += (Version ? *Version : "N/A");
  return out;
}
