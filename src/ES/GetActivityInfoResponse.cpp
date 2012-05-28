#include "glite/ce/es-client-api-c/GetActivityInfoResponse.h"
#include "glite/ce/es-client-api-c/ComputingActivity.h"
#include "glite/ce/es-client-api-c/InternalBaseFault.h"
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
void
wr::GetActivityInfoResponse::getActivityInfoItems( map<string, ComputingActivity*>& sucessful, 
						   map<string, InternalBaseFault*>& failed) const
{
  vector< ActivityInfoItemType* >::const_iterator it;
  it = ActivityInfoItemField.begin( );
  for( ; it != ActivityInfoItemField.end( ); ++it )
    {
      if( (*it)->__union_ActivityInfoItem == Union_ActivityInfoItem_ActivityInfo_Number){
	ComputingActivity *compAct = new ComputingActivity( *((ComputingActivity* )(*it)->union_ActivityInfoItem.ActivityInfoField) );
	sucessful[ (*it)->ActivityIDField ] = compAct;
	continue;
      }

      if( (*it)->__union_ActivityInfoItem == Union_ActivityInfoItem_InternalBaseFault_Number){
	InternalBaseFault *IBF = new InternalBaseFault( *((InternalBaseFault*)(*it)->union_ActivityInfoItem.InternalBaseFaultField) );
	failed[ (*it)->ActivityIDField ] = IBF;
	continue;
      }
    }
}
