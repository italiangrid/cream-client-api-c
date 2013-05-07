#include "glite/ce/es-client-api-c/WCoprocessorType.h"
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
wr::WCoprocessorType::WCoprocessorType( const  int _item,
                           	        bool* _optional ) : CoprocessorType()
{
  __item = (CoprocessorEnumeration)_item;
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
void
wr::WCoprocessorType::set( const WCoprocessorType& cop )
{
  optional = 0;

  __item = cop.__item;
  if(cop.optional) {
    optional = new bool;
    (*optional) = *cop.optional;
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
 wr::WCoprocessorType::WCoprocessorType( const WCoprocessorType& src ) 
   : CoprocessorType()
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
wr::WCoprocessorType&
wr::WCoprocessorType::operator=( const WCoprocessorType& src )
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
wr::WCoprocessorType::free( ) 
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
wr::WCoprocessorType::toString( const bool tabbed ) const
{


  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "CoprocessorType=";
  out += tab + "  item=";
  out += boost::lexical_cast<string>( __item );
  out += tab + "  optional=";
  out += (optional ? boost::lexical_cast<string>( *optional ) : "N/A");
  return out;
}
