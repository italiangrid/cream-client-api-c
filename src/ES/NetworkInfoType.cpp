#include "glite/ce/es-client-api-c/NetworkInfoType.h"
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
wr::NetworkInfoType::NetworkInfoType( const int _item,
                         	      const bool _optional ) 
  : NetworkInfoClassType()
{
  __item = (NetworkInfoEnumeration)_item;
  optional = new bool;
  (*optional) = _optional;
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::NetworkInfoType::NetworkInfoType( const NetworkInfoType& src ) 
  : NetworkInfoClassType()
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
wr::NetworkInfoType&
wr::NetworkInfoType::operator=( const NetworkInfoType& src )
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
wr::NetworkInfoType::set(const NetworkInfoType& src )
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
wr::NetworkInfoType::free( ) 
{
  if(getenv("ES_CLIENT_DEBUG_DTOR") )
    cerr << "NetworkInfoType::free EXECUTED" << endl;
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
wr::NetworkInfoType::toString( const bool tabbed ) const
{

  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "item=";
  out += boost::lexical_cast<string>( __item );
  out += tab + "optional=";
  out += (optional ? boost::lexical_cast<string>( *optional ) : "N/A");
  return out;
}
