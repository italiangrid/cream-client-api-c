#include "glite/ce/es-client-api-c/OutputFile.h"

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
wr::OutputFile::OutputFile( const std::string& _name,
		            const std::vector<wr::Target>& _Targets )
{
  Name = _name;
  
  vector<wr::Target>::const_iterator it = _Targets.begin();
  for( ; it != _Targets.end( ); ++it ) {
    Target *tgt = new Target( *it );
    TargetField.push_back( tgt );
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
wr::OutputFile::set( const OutputFile& src )
{
  Name = src.Name;
  vector<TargetType*>::const_iterator it = src.TargetField.begin();
  for( ; it != src.TargetField.end( ); ++it ) {
    Target* current = (Target*)*it;
    Target *tgt = new Target( *current );
    TargetField.push_back( tgt );
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
wr::OutputFile::OutputFile( const OutputFile& src )
  : OutputFileType( )
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
wr::OutputFile::free( )
{
  vector<TargetType*>::const_iterator it = TargetField.begin();
  for( ; it != TargetField.end( ); ++it ) {
    Target* current = (Target*)*it;
    delete current;
  }
  TargetField.clear();
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
wr::OutputFile::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "Name=";
  out += Name;

  vector<TargetType *>::const_iterator it = TargetField.begin( );
  for( ; it != TargetField.end( ); ++it )
    {
      Target* current = (Target*)*it;
      out += current->toString( );
    }

  return out;
}
