
#include "glite/ce/es-client-api-c/ManageActivityCall.h"

#include <utility>

using namespace std;
using namespace emi_es::client::comm;
using namespace emi_es::client::wrapper;

/**
 *
 *
 *
 *
 *
 *
 *
 */
ManageActivityCall::ManageActivityCall( const string& endpoint, 
					const vector<string>& ids )
  : AbstractCall( endpoint ), m_IDs( ids )
{
}

/**
 *
 *
 *
 *
 *
 *
 *
 */
void
ManageActivityCall::process_response( const vector<ResponseItemType*>& items )
{
  vector<ResponseItemType*>::const_iterator it;
  it = items.begin();
  for( ; it != items.end( ); ++it )
    {

      if( (*it)->__union_ResponseItem == Union_ResponseItem_EstimatedTime )
	{
	  long long int val = ( (*it)->union_ResponseItem.EstimatedTime ? *((*it)->union_ResponseItem.EstimatedTime) : -1);
	  m_successful.insert( make_pair( (*it)->ActivityIDField, val ) );
	  continue;
	}

      if( (*it)->__union_ResponseItem == Union_ResponseItem_InternalBaseFault ) 
	{
	  InternalBaseFault ibf( *((InternalBaseFault*)(*it)->union_ResponseItem.InternalBaseFaultField));
	  m_failed.insert( make_pair( (*it)->ActivityIDField, ibf ) );
	  continue;
	}

    }
}
