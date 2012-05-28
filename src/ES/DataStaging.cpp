#include "glite/ce/es-client-api-c/DataStaging.h"
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
wr::DataStaging::DataStaging( const bool _ClientDataPush,
	  	      	      const vector<InputFile>& _InputFiles,
		      	      const vector<OutputFile>& _OutputFiles)
{
  ClientDataPush = new bool;
  *ClientDataPush = _ClientDataPush;
  
  vector<InputFile>::const_iterator iit = _InputFiles.begin( );
  for( ; iit != _InputFiles.end(); ++iit )
    {
      InputFile* IF = new InputFile( *iit );
      InputFileField.push_back( IF );
    }
  
  vector<OutputFile>::const_iterator oit = _OutputFiles.begin( );
  for( ; oit != _OutputFiles.end(); ++oit )
    {
      OutputFile* OF = new OutputFile( *oit );
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
wr::DataStaging::DataStaging( const DataStaging& src )
  : DataStagingType( )
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
wr::DataStaging::set( const DataStaging& src )
{
  ClientDataPush = 0;

  if( src.ClientDataPush ) {
    ClientDataPush = new bool;
    *(ClientDataPush) = *src.ClientDataPush;
  }
  
  vector<InputFileType*>::const_iterator iit = src.InputFileField.begin( );
  for( ; iit != src.InputFileField.end(); ++iit )
    {
      InputFile* current = (InputFile*)*iit;
      InputFile* IF = new InputFile( *current );
      InputFileField.push_back( IF );
    }
  
  vector<OutputFileType*>::const_iterator oit = src.OutputFileField.begin( );
  for( ; oit != src.OutputFileField.end(); ++oit )
    {
      OutputFile *current = (OutputFile*)*oit;
      OutputFile* OF = new OutputFile( *current );
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
wr::DataStaging::free( )
{
  if (ClientDataPush)
    delete ClientDataPush;
  {
    vector<InputFileType*>::const_iterator it = InputFileField.begin( );
    for( ; it != InputFileField.end( ); ++it )
      {
	InputFile* current = (InputFile*)*it;
	delete current;
      }
  }

  InputFileField.clear();

  {
    vector<OutputFileType*>::const_iterator it = OutputFileField.begin( );
    for( ; it != OutputFileField.end(); ++it )
    {
      OutputFile *current = (OutputFile*)*it;
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
wr::DataStaging::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "ClientDataPush=";
  out += (ClientDataPush ? boost::lexical_cast<string>( *ClientDataPush ) : "N/A");
  {
    vector<InputFileType*>::const_iterator it = InputFileField.begin( );
    for( ; it != InputFileField.end( ); ++it )
      {
	InputFile* current = (InputFile*)*it;
	out += current->toString( );
      }
  }
  
  {
    vector<OutputFileType*>::const_iterator it = OutputFileField.begin( );
    for( ; it != OutputFileField.end(); ++it )
      {
	OutputFile *current = (OutputFile*)*it;
	out += current->toString( );
      }
  }

  return out;
}
