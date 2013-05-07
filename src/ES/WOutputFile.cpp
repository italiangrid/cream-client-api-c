#include "glite/ce/es-client-api-c/WOutputFile.h"

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
wr::WOutputFile::WOutputFile( const std::string& _name,
		              const std::vector<wr::WTarget>& _Targets )
{
  Name = _name;
  
  vector<wr::WTarget>::const_iterator it = _Targets.begin();
  for( ; it != _Targets.end( ); ++it ) {
    WTarget *tgt = new WTarget( *it );
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
wr::WOutputFile::set( const WOutputFile& src )
{
  Name = src.Name;
  vector<Target*>::const_iterator it = src.TargetField.begin();
  for( ; it != src.TargetField.end( ); ++it ) {
    WTarget* current = (WTarget*)*it;
    WTarget *tgt = new WTarget( *current );
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
wr::WOutputFile::WOutputFile( const WOutputFile& src )
  : OutputFile( )
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
wr::WOutputFile::free( )
{
  vector<Target*>::const_iterator it = TargetField.begin();
  for( ; it != TargetField.end( ); ++it ) {
    WTarget* current = (WTarget*)*it;
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
wr::WOutputFile::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += "Target:";
  out += tab + "  Name=";
  out += Name;

  vector<Target *>::const_iterator it = TargetField.begin( );
  for( ; it != TargetField.end( ); ++it )
    {
      WTarget* current = (WTarget*)*it;
      out += current->toString( );
    }

  return out;
}
