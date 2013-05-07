#include "glite/ce/es-client-api-c/WInputFile.h"
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
wr::WInputFile::WInputFile( const std::string& _name,
		            const std::vector<WSource>& _Sources,
		            bool* _IsExecutable )
{
  Name          =  _name;
  IsExecutable  =  0;
  
  if( _IsExecutable );
    IsExecutable = new bool(_IsExecutable);
  
  vector<WSource>::const_iterator it = _Sources.begin();
  for( ; it != _Sources.end( ); ++it ) {
    WSource *src = new WSource( *it );
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
wr::WInputFile::set( const WInputFile& src )
{
  IsExecutable = 0;

  Name = src.Name;

  if(src.IsExecutable)
    IsExecutable = new bool(*src.IsExecutable);
  
  vector<Source *>::const_iterator it = src.SourceField.begin();
  for( ; it != src.SourceField.end( ); ++it ) {
    WSource *current = (WSource*)*it;
    WSource *src = new WSource( *current );
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
wr::WInputFile::WInputFile( const WInputFile& src )
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
wr::WInputFile::getSources( vector<wr::WSource>& target) const {
  vector<Source *>::const_iterator it = SourceField.begin( );
  for( ; it != SourceField.end( ); ++it )
  {
    WSource* current = (WSource*)*it;
    WSource src( *current );
    target.push_back( src );
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
wr::WInputFile::free( )
{
  delete IsExecutable;
  
  vector<Source*>::const_iterator it = SourceField.begin();
  for( ; it != SourceField.end( ); ++it ) {
    WSource *current = (WSource*)*it;
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
wr::WInputFile::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
  
  string out;
  out += "InputFile:";
  
  out += tab +"  Name=";
  out += Name;
  out += tab + "  IsExecutable=";
  out += ( IsExecutable ? ( *IsExecutable ? "true" : "false") : "N/A" );
  
  vector<Source*>::const_iterator it = SourceField.begin();
  for( ; it != SourceField.end( ); ++it )
    {
      WSource* current = (WSource*)*it;
      out += current->toString( tabbed );
    }

  return out;
}
