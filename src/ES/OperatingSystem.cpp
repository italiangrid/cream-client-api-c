#include "glite/ce/es-client-api-c/OperatingSystem.h"

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
wr::OperatingSystem::OperatingSystem( const ::string& _Name,
			 	      std::string* _Family,
			 	      std::string* _Version ) 
  : OperatingSystemType( )
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
wr::OperatingSystem::set( const OperatingSystem& src )
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
wr::OperatingSystem::OperatingSystem( const OperatingSystem& src )
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
wr::OperatingSystem::free( )
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
wr::OperatingSystem::toString( const bool tabbed ) const
{

  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "Name=";
  out += Name;
  out += tab + "Family=";
  out += (Family ? *Family : "N/A");
  out += tab + "Version=";
  out += (Version ? *Version : "N/A");
  return out;
}
