
#include "glite/ce/es-client-api-c/GetActivityStatusResponse.h"

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
wr::GetActivityStatusResponse::getActivityStatus( map<string, ActivityStatus>& states,
						  map<string, InternalBaseFault>& faults) const
{
  vector<ActivityStatusItemType*>::const_iterator it;
  it = ActivityStatusItemField.begin();
  for( ; it != ActivityStatusItemField.end(); ++it )
  {
    if((*it)->__union_ActivityStatusItem == Union_ActivityStatusItem_ActivityStatus_Number)
      {
	ActivityStatusType* thisStatus 
	  = (*it)->union_ActivityStatusItem.ActivityStatusField;
	ActivityStatus thisActStat( *((ActivityStatus*)thisStatus) );
	states[(*it)->ActivityIDField] = thisActStat;
	continue;
      }

    if((*it)->__union_ActivityStatusItem == Union_ActivityStatusItem_InternalBaseFault_Number)
      {
	InternalBaseFaultType *fault 
	  = (*it)->union_ActivityStatusItem.InternalBaseFaultField;
	InternalBaseFault ibf(*((InternalBaseFault*)fault));
	faults[(*it)->ActivityIDField] = ibf;//.push_back( ibf );
	continue;
      }
  }
}
