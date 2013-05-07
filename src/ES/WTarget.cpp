#include "glite/ce/es-client-api-c/WTarget.h"
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
wr::WTarget::WTarget( const string& uri,
		      string* delegationid,
		      const vector<OptionType>& option,
		      bool* mandatory,
		      CreationFlagEnumeration*   creationflag,
		      bool *useiffailure,
		      bool *useifcancel,
		      bool *useifsuccess )
{

  DelegationID = 0;
  Mandatory    = 0;
  CreationFlag = 0;
  UseIfCancel  = 0;
  UseIfSuccess = 0;
  UseIfFailure = 0;
  
  URI = uri;
  if(delegationid)
    DelegationID = new string( *delegationid );
    
  vector<OptionType>::const_iterator it = option.begin( );
  for( ; it != option.end( ); ++it )
  {
    OptionType* opt = new OptionType( );
    opt->Name = it->Name;
    opt->Value = it->Value;
    OptionField.push_back( opt );
  }
  if(mandatory)
    Mandatory = new bool( *mandatory );

  if( creationflag ) {
    CreationFlag = new CreationFlagEnumeration();
    (*CreationFlag) = *creationflag;
  } 
  
  if( useiffailure )
    UseIfFailure = new bool( *useiffailure );

  if( useifcancel )
    UseIfCancel = new bool( *useifcancel );

  if( useifsuccess )
    UseIfSuccess = new bool( *useifsuccess );
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::WTarget::WTarget( const WTarget& src ) : Target()
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
wr::WTarget& 
wr::WTarget::operator=(const WTarget& src )
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
void wr::WTarget::set( const WTarget& src )
{
  DelegationID = 0;
  Mandatory    = 0;
  CreationFlag = 0;
  UseIfCancel  = 0;
  UseIfSuccess = 0;
  UseIfFailure = 0;
  
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
  
  if( src.Mandatory )
    Mandatory = new bool( *src.Mandatory );
  
  if( src.CreationFlag ) {
    CreationFlag = new CreationFlagEnumeration;
    (*CreationFlag) = *src.CreationFlag;
  }
  
  if( src.UseIfFailure )
    UseIfFailure = new bool( *src.UseIfFailure );
  
  if( src.UseIfCancel )
    UseIfCancel = new bool(*src.UseIfCancel);
  
  if( src.UseIfSuccess )
    UseIfSuccess = new bool( *src.UseIfSuccess );
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
wr::WTarget::free( )
{
  delete DelegationID;
  delete Mandatory;
  delete CreationFlag;
  delete UseIfFailure;
  delete UseIfCancel;
  delete UseIfSuccess;
  
  // Option is a typedef for _ES_USCOREADL__Option 
  vector<OptionType*>::const_iterator it = OptionField.begin();
  for( ; it != OptionField.end( ); ++it ) {
    delete( *it );
  }
  OptionField.clear();
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
wr::WTarget::toString( const bool tabbed ) const
{

  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += "Target:";
  out = tab + "  URI=";
  out += URI;
  out += tab + "  DelegationID=";
  if(DelegationID)
    out += *DelegationID;
  else
    out += "N/A";
  out += tab + "  Mandatory=";
  out += boost::lexical_cast<string>( *Mandatory );
  out += tab + "  CreationFlag=";
  out += boost::lexical_cast<string>( *CreationFlag );
  out += tab + "  UseIfFailure=";
  out += boost::lexical_cast<string>( *UseIfFailure );
  out += tab + "  UseIfCancel=";
  out += boost::lexical_cast<string>( *UseIfCancel );
  out += tab + "  UseIfSuccess=";
  out += boost::lexical_cast<string>( *UseIfSuccess );
  
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
