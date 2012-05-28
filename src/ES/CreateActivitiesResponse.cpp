
#include "glite/ce/es-client-api-c/CreateActivitiesResponse.h"

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
void
wr::CreateActivitiesResponse::getActivityCreationResponse( vector<ActivityCreationResponse>& target ) const
{
  vector<ActivityCreationResponseType *>::const_iterator it, it_end;
  it = ActivityCreationResponseField.begin( );
  it_end = ActivityCreationResponseField.end( );
  for( ; it != it_end; ++it )
    {
      ActivityCreationResponse* current = (ActivityCreationResponse*)*it;
      ActivityCreationResponse act( *current );
      target.push_back( act );
    }
}
