#include "glite/ce/es-client-api-c/CreateActivities.h"

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
wr::CreateActivities::CreateActivities( const vector<ActivityDescription>& acts )
{
  vector<ActivityDescription>::const_iterator it = acts.begin( );
  for( ; it != acts.end( ); ++it ) {
    
    ActivityDescriptionType *act = new ActivityDescription( *it );
    
    ActivityDescriptionField.push_back( act );
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
wr::CreateActivities::set( const CreateActivities& src )
{
  vector<ActivityDescriptionType *>::const_iterator it 
    = src.ActivityDescriptionField.begin( );

  for( ; it != src.ActivityDescriptionField.end( ); ++it ) 
    {
      ActivityDescriptionType *act 
	= new ActivityDescription( *((ActivityDescription*)*it) );
      ActivityDescriptionField.push_back( act );
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
wr::CreateActivities::CreateActivities( const CreateActivities& src )
  : CreateActivitiesType()
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
wr::CreateActivities::free( )
{
  vector<ActivityDescriptionType *>::const_iterator it 
    = ActivityDescriptionField.begin( );

  for( ; it != ActivityDescriptionField.end( ); ++it ) 
    {
      ActivityDescription *current = (ActivityDescription *)*it;
      delete current;
    }
  ActivityDescriptionField.clear();
}
