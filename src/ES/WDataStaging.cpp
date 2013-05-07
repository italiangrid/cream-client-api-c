#include "glite/ce/es-client-api-c/WDataStaging.h"
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
wr::WDataStaging::WDataStaging( const bool _ClientDataPush,
	  	      	        const vector<WInputFile>& _InputFiles,
		      	        const vector<WOutputFile>& _OutputFiles) : DataStaging( )
{
  ClientDataPush = new bool;
  *ClientDataPush = _ClientDataPush;
  
  vector<WInputFile>::const_iterator iit = _InputFiles.begin( );
  for( ; iit != _InputFiles.end(); ++iit )
    {
      WInputFile* IF = new WInputFile( *iit );
      InputFileField.push_back( IF );
    }
  
  vector<WOutputFile>::const_iterator oit = _OutputFiles.begin( );
  for( ; oit != _OutputFiles.end(); ++oit )
    {
      WOutputFile* OF = new WOutputFile( *oit );
      OutputFileField.push_back( OF );
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
wr::WDataStaging::WDataStaging( const WDataStaging& src )
  : DataStaging( )
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
wr::WDataStaging::set( const WDataStaging& src )
{
  ClientDataPush = 0;

  if( src.ClientDataPush ) {
    ClientDataPush = new bool;
    *(ClientDataPush) = *src.ClientDataPush;
  }
  
  vector<InputFile*>::const_iterator iit = src.InputFileField.begin( );
  for( ; iit != src.InputFileField.end(); ++iit )
    {
      WInputFile* current = (WInputFile*)*iit;
      WInputFile* IF = new WInputFile( *current );
      InputFileField.push_back( IF );
    }
  
  vector<OutputFile*>::const_iterator oit = src.OutputFileField.begin( );
  for( ; oit != src.OutputFileField.end(); ++oit )
    {
      WOutputFile *current = (WOutputFile*)*oit;
      WOutputFile* OF = new WOutputFile( *current );
      OutputFileField.push_back( OF );
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
wr::WDataStaging::free( )
{
  if (ClientDataPush)
    delete ClientDataPush;
  {
    vector<InputFile*>::const_iterator it = InputFileField.begin( );
    for( ; it != InputFileField.end( ); ++it )
      {
	WInputFile* current = (WInputFile*)*it;
	delete current;
      }
  }

  InputFileField.clear();

  {
    vector<OutputFile*>::const_iterator it = OutputFileField.begin( );
    for( ; it != OutputFileField.end(); ++it )
    {
      WOutputFile *current = (WOutputFile*)*it;
      delete current;
    }
  }
  OutputFileField.clear();

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
wr::WDataStaging::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += "DataStaging: ";
  out += tab + "  ClientDataPush=";
  out += (ClientDataPush ? boost::lexical_cast<string>( *ClientDataPush ) : "N/A");
  {
    vector<InputFile*>::const_iterator it = InputFileField.begin( );
    for( ; it != InputFileField.end( ); ++it )
      {
	WInputFile* current = (WInputFile*)*it;
	out += current->toString( );
      }
  }
  
  {
    vector<OutputFile*>::const_iterator it = OutputFileField.begin( );
    for( ; it != OutputFileField.end(); ++it )
      {
	WOutputFile *current = (WOutputFile*)*it;
	out += current->toString( );
      }
  }

  return out;
}
