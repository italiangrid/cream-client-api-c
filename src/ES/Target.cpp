#include "glite/ce/es-client-api-c/Target.h"
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
wr::Target::Target( const string& uri,
		    string* delegationid,
		    const vector<OptionType>& option,
		    bool* mandatory,
		    int   creationflag,
		    bool useiffailure,
		    bool useifcancel,
		    bool useifsuccess )
{
  URI = uri;
  if(delegationid)
    DelegationID = new string( *delegationid );
  else
    DelegationID = 0;
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
  else
    Mandatory = 0;


  CreationFlag = new CreationFlagEnumeration();
  (*CreationFlag) = (CreationFlagEnumeration)creationflag;

  UseIfFailure = new bool( useiffailure );

  UseIfCancel = new bool( useifcancel );

  UseIfSuccess = new bool( useifsuccess );

}

/**
 *
 *
 *
 *
 *
 *
 */
wr::Target::Target( const Target& src ) : TargetType()
{
  if(getenv("ES_CLIENT_DEBUG_CTOR") )
    cerr << "Target::Target EXECUTED" << endl;
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
wr::Target& 
wr::Target::operator=(const Target& src )
{
  if(getenv("ES_CLIENT_DEBUG_CTOR") )
    cerr << "Target::operator= EXECUTED" << endl;

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
void wr::Target::set( const Target& src )

{
  if(getenv("ES_CLIENT_DEBUG_CTOR") )
    cerr << "Target::set EXECUTED" << endl;


  DelegationID = 0;
  Mandatory = 0;
  CreationFlag = 0;
  UseIfCancel = 0;
  UseIfSuccess = 0;

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
wr::Target::free( )
{
  if(getenv("ES_CLIENT_DEBUG_DTOR") )
    cerr << "Target::free EXECUTED for Object [" <<URI <<"]"<< endl;
  
  if(DelegationID) delete DelegationID;
  if(Mandatory) delete Mandatory;
  if(CreationFlag) delete CreationFlag;
  if(UseIfFailure) delete UseIfFailure;
  if(UseIfCancel) delete UseIfCancel;
  if(UseIfSuccess) delete UseIfSuccess;
  
  // Option is a typedef for _ES_USCOREADL__Option 
  vector<OptionType*>::const_iterator it = OptionField.begin();
  for( ; it != OptionField.end( ); ++it ) {
    delete( *it );
  }
  OptionField.clear();

  if(getenv("ES_CLIENT_DEBUG_DTOR") )
    cerr << "Target::free EXECUTED for Object [" <<URI <<"]. DONE!"<< endl;
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
wr::Target::toString( const bool tabbed ) const
{

  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out = tab + "URI=";
  out += URI;
  out += tab + "DelegationID=";
  if(DelegationID)
    out += *DelegationID;
  else
    out += "N/A";
  out += tab + "Mandatory=";
  out += boost::lexical_cast<string>( *Mandatory );
  out += tab + "CreationFlag=";
  out += boost::lexical_cast<string>( *CreationFlag );
  out += tab + "UseIfFailure=";
  out += boost::lexical_cast<string>( *UseIfFailure );
  out += tab + "UseIfCancel=";
  out += boost::lexical_cast<string>( *UseIfCancel );
  out += tab + "UseIfSuccess=";
  out += boost::lexical_cast<string>( *UseIfSuccess );
  
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
