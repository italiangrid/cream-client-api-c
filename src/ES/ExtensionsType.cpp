#include "glite/ce/es-client-api-c/ExtensionsType.h"
#include "glite/ce/es-client-api-c/typedefs.h"
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
// wr::ExtensionsType::ExtensionsType( const vector<wr::Extension>& src ) {
  
//   vector<wr::Extension>::const_iterator it = src.begin( );
  
//   for( ; it != src.end( ); ++it ) {
//     wr::Extension *ext = new wr::Extension( it->LocalID,
// 					    it->Key,
// 					    it->Value,
// 					    it->__any );

//     this->Extension.push_back( ext );
//   }
// }

/**
 *
 *
 *
 *
 *
 *
 */
// void
// wr::ExtensionsType::set( const ExtensionsType& src ) {
  
//   vector<ns1__Extension_USCOREt*>::const_iterator it = src.Extension.begin( );
  
//   for( ; it != src.Extension.end( ); ++it ) {
//     wr::Extension *ext = new wr::Extension( (*it)->LocalID,
// 					    (*it)->Key,
// 					    (*it)->Value,
// 					    (*it)->__any );
//     //ns1__Extension_USCOREt *ext = new ns1__Extension_USCOREt( );
//     //ext->LocalID = (*it)->LocalID;
//     //ext->Key = (*it)->Key;
//     //ext->Value = (*it)->Value;
//     this->Extension.push_back( ext );
//   }

// }

/**
 *
 *
 *
 *
 *
 *
 */
// void
// wr::ExtensionsType::free( )
// {
//   vector<ns1__Extension_USCOREt*>::const_iterator it = this->Extension.begin( );
  
//   for( ; it != this->Extension.end( ); ++it ) {
//     wr::Extension *thisExt = (wr::Extension*)*it;
//     delete thisExt;
//   }
  
//   this->Extension.clear();
// }

/**
 *
 *
 *
 *
 *
 *
 */
string
wr::ExtensionsType::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
  
  string out;
  
  vector<ns1__Extension_USCOREt*>::const_iterator it = Extension.begin( );
  int counter = 0;
  for( ; it != Extension.end( ); ++it )
    {
      out += tab + "***** Extension #" + boost::lexical_cast<string>(counter) + ":";
      out += tab + "      LocalID=" + (*it)->LocalID;
      out += tab + "      Key=" + (*it)->Key;
      out += tab + "      Value=" + (*it)->Value;
      counter++;
    }

  return out;
}
