#include "glite/ce/es-client-api-c/WCreateActivity.h"

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
wr::WCreateActivity::WCreateActivity( const vector<WActivityDescription>& acts )
{
  vector<WActivityDescription>::const_iterator it = acts.begin( );
  for( ; it != acts.end( ); ++it ) {
    
    WActivityDescription *act = new WActivityDescription( *it );
    
    ActivityDescriptionField.push_back( (ActivityDescription*)act );
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
wr::WCreateActivity::set( const WCreateActivity& src )
{
  vector<ActivityDescription *>::const_iterator it 
    = src.ActivityDescriptionField.begin( );

  for( ; it != src.ActivityDescriptionField.end( ); ++it ) 
    {
      WActivityDescription *act 
	= new WActivityDescription( *((WActivityDescription*)*it) );
      ActivityDescriptionField.push_back( (ActivityDescription*)act );
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
wr::WCreateActivity::free( )
{
  vector<ActivityDescription *>::const_iterator it 
    = ActivityDescriptionField.begin( );

  for( ; it != ActivityDescriptionField.end( ); ++it ) 
    {
      WActivityDescription *current = (WActivityDescription *)*it;
      delete current;
    }
  ActivityDescriptionField.clear();
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
wr::WCreateActivity::toString( const bool tabbed ) const {
  string out;
  vector<ActivityDescription*>::const_iterator it = ActivityDescriptionField.begin( );
  for( ; it != ActivityDescriptionField.end( ); ++it ) {
    out += ((WActivityDescription*)*it)->toString( tabbed ) + "\n";
  }
  return out;
}
