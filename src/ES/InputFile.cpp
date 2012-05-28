#include "glite/ce/es-client-api-c/InputFile.h"
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
wr::InputFile::InputFile( const std::string& _name,
		          const std::vector<Source>& _Sources,
		          const bool _IsExecutable )
{
  Name = _name;
  IsExecutable = new bool(_IsExecutable);
  
  vector<Source>::const_iterator it = _Sources.begin();
  for( ; it != _Sources.end( ); ++it ) {
    //Source *src = new Source( it->URI, (const string&)*(it->DelegationID), it->getOptions() );
    Source *src = new Source( *it );
    SourceField.push_back( src );
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
wr::InputFile::set( const InputFile& src )
{
  IsExecutable = 0;

  Name = src.Name;

  if(src.IsExecutable)
    IsExecutable = new bool(*src.IsExecutable);
  
  vector<SourceType *>::const_iterator it = src.SourceField.begin();
  for( ; it != src.SourceField.end( ); ++it ) {
    Source *current = (Source*)*it;
    Source *src = new Source( *current );
    SourceField.push_back( src );
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
wr::InputFile::InputFile( const InputFile& src )
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
vector<wr::Source>
wr::InputFile::getSources( ) const {
  vector<wr::Source> target;
  vector<SourceType *>::const_iterator it = SourceField.begin( );
  for( ; it != SourceField.end( ); ++it )
  {
    Source* current = (Source*)*it;
    Source src( *current );
    target.push_back( src );
  }
  return target;
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
wr::InputFile::free( )
{
  if(IsExecutable) 
    delete IsExecutable;
  
  vector<SourceType*>::const_iterator it = SourceField.begin();
  for( ; it != SourceField.end( ); ++it ) {
    Source *current = (Source*)*it;
    delete current;
  }
  SourceField.clear();
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
wr::InputFile::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
  
  string out;
  out += tab +"Name=";
  out += Name;
  out += tab + "IsExecutable=";
  out += ( IsExecutable ? ( *IsExecutable ? "true" : "false") : "N/A" );
  
  vector<SourceType*>::const_iterator it = SourceField.begin();
  for( ; it != SourceField.end( ); ++it )
    {
      Source* current = (Source*)*it;
      out += current->toString( tabbed );
    }

  return out;
}
