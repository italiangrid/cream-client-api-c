#include "glite/ce/es-client-api-c/CoprocessorType.h"
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
wr::CoprocessorType::CoprocessorType( const  int _item,
                         	      const bool _optional ) : CoprocessorClassType()
{
  __item = (CoprocessorEnumeration)_item;
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
void
wr::CoprocessorType::set( const CoprocessorType& cop )
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
 wr::CoprocessorType::CoprocessorType( const CoprocessorType& src ) 
   : CoprocessorClassType()
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
wr::CoprocessorType&
wr::CoprocessorType::operator=( const CoprocessorType& src )
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
wr::CoprocessorType::free( ) 
{
  if(getenv("ES_CLIENT_DEBUG_DTOR") )
    cerr << "CoprocessorType::free EXECUTED" << endl;
    
  if(optional) delete optional;
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
wr::CoprocessorType::toString( const bool tabbed ) const
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
