#include "glite/ce/es-client-api-c/Source.h"
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
 wr::Source::Source( const Source& src ) 
   : SourceType()
 {
   if(getenv("ES_CLIENT_DEBUG_CTOR") )
     cerr << "Source::Source EXECUTED" << endl;
   
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
 wr::Source&
 wr::Source::operator=( const Source& src )
 {
   if(getenv("ES_CLIENT_DEBUG_CTOR") )
     cerr << "Source::operator= EXECUTED" << endl;
   
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
wr::Source::set( const Source& src )
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
wr::Source::free( )
{  

  if(getenv("ES_CLIENT_DEBUG_DTOR") )
    cerr << "Source::free EXECUTED" << endl;
  
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
wr::Source::Source( const string& uri, const string& delegationid, const vector<OptionType>& option )
{
  URI = uri;
  DelegationID = new string( delegationid );
  
  vector<OptionType>::const_iterator it = option.begin( );
  for( ; it != option.end( ); ++it )
  {
    OptionType* opt = new OptionType( );
    opt->Name = it->Name;
    opt->Value = it->Value;
    OptionField.push_back( opt );
  }
}

wr::Source::Source( const string& uri, const vector<OptionType>& option )
{
  URI = uri;
  DelegationID = 0;

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
wr::Source::toString( const bool tabbed ) const 
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out = tab + "URI=";
  out += URI;
  out += tab + "DelegationID=";
  if(DelegationID)
    out += *DelegationID;
  else
    out += "N/A";
  
  vector<OptionType*>::const_iterator it = OptionField.begin( );
  int counter = 0;
  for( ; it != OptionField.end( ); ++it )
  {
    out += tab + "Option[" + boost::lexical_cast<string>( counter ) + "]=";
    out += (*it)->Name + " -> " + (*it)->Value;
    counter++;
  }
  return out;
}
