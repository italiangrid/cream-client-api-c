#include "glite/ce/es-client-api-c/WNetworkInfoType.h"
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
wr::WNetworkInfoType::WNetworkInfoType( const int _item,
                         	        bool* _optional ) 
  : NetworkInfoType()
{
  __item = (NetworkInfoEnumeration)_item;
  optional = 0;
  if(_optional) {
    optional = new bool;
    (*optional) = *_optional;
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
wr::WNetworkInfoType::WNetworkInfoType( const WNetworkInfoType& src ) 
  : NetworkInfoType()
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
wr::WNetworkInfoType&
wr::WNetworkInfoType::operator=( const WNetworkInfoType& src )
{
  this->free( );
  this->set( src );
  return *this;
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
wr::WNetworkInfoType::set(const WNetworkInfoType& src )
{
  optional = 0;
  
  __item = src.__item;
  
  if(src.optional) {
    optional = new bool;
    (*optional) = *src.optional;
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
wr::WNetworkInfoType::free( ) 
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
wr::WNetworkInfoType::toString( const bool tabbed ) const
{

  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "NetworkInfoType:";
  out += tab + "  item=";
  out += boost::lexical_cast<string>( __item );
  out += tab + "  optional=";
  out += (optional ? boost::lexical_cast<string>( *optional ) : "N/A");
  return out;
}
