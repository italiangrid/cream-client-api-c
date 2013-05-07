#include "glite/ce/es-client-api-c/WSource.h"
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
 wr::WSource::WSource( const WSource& src ) 
   : Source()
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
 wr::WSource&
 wr::WSource::operator=( const WSource& src )
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
wr::WSource::set( const WSource& src )
{
  DelegationID = 0;

  URI = src.URI;
  
  if( src.DelegationID )
    DelegationID = new string( *src.DelegationID );

  vector<OptionType*>::const_iterator it = src.OptionField.begin( );
  for( ; it != src.OptionField.end( ); ++it ) {
    OptionType* opt = new OptionType();
    opt->Name = (*it)->Name;
    opt->Value = (*it)->Value;
    OptionField.push_back( opt );
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
wr::WSource::free( )
{  
  delete DelegationID;
  
  vector<OptionType*>::const_iterator it = OptionField.begin();
  for( ; it != OptionField.end( ); ++it ) {
    delete( *it );
  }
  OptionField.clear( );
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::WSource::WSource( const string& uri,  string* delegationid, const vector<OptionType>& option )
{
  URI = uri;
  DelegationID = 0;
  if( delegationid )
    DelegationID = new string( *delegationid );
  
  vector<OptionType>::const_iterator it = option.begin( );
  for( ; it != option.end( ); ++it )
  {
    OptionType* opt = new OptionType( );
    opt->Name = it->Name;
    opt->Value = it->Value;
    OptionField.push_back( opt );
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
string
wr::WSource::toString( const bool tabbed ) const 
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
   
  out = "Source: ";
  out += tab + "  URI=";
  out += URI;
  out += tab + "  DelegationID=" + (DelegationID ? *DelegationID : "N/A" );
  
  vector<OptionType*>::const_iterator it = OptionField.begin( );
  int counter = 0;
  for( ; it != OptionField.end( ); ++it )
  {
    out += tab + "  Option[" + boost::lexical_cast<string>( counter ) + "]=";
    out += (*it)->Name + " -> " + (*it)->Value;
    counter++;
  }
  return out;
}
