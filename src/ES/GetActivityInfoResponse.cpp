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
						   map<string, pair<int, InternalBaseFault*> >& failed) const
{
  vector< ActivityInfoItemType* >::const_iterator it;
  it = ActivityInfoItemField.begin( );
  for( ; it != ActivityInfoItemField.end( ); ++it )
    {
      InternalBaseFault *IBF = 0;
      switch( (*it)->__union_ActivityInfoItem ) {
      case ActivityInfoDocumentNumber:
        break;
      case AttributeInfoItemNumber:
        break;
      case ActivityInfoInternalBaseFaultNumber:
        IBF = new InternalBaseFault( *((InternalBaseFault*)(*it)->union_ActivityInfoItem.InternalBaseFaultField) );
	failed[ (*it)->ActivityIDField ] = make_pair( (*it)->union_ActivityInfoItem.InternalBaseFaultField->soap_type( ), IBF );
	break;
      case ActivityInfoAccessControlFaultNumber:
        IBF = new InternalBaseFault( *((InternalBaseFault*)(*it)->union_ActivityInfoItem.AccessControlFaultField) );
	failed[ (*it)->ActivityIDField ] = make_pair( (*it)->union_ActivityInfoItem.AccessControlFaultField->soap_type( ), IBF );
	break;
      case ActivityInfoUnknownActivityIDFaultNumber:
        IBF = new InternalBaseFault( *((InternalBaseFault*)(*it)->union_ActivityInfoItem.ActivityInfoUnknownActivityIDFaultField) );
	failed[ (*it)->ActivityIDField ] = make_pair( (*it)->union_ActivityInfoItem.ActivityInfoUnknownActivityIDFaultField->soap_type( ), IBF );
	break;
      case ActivityInfoUnknownAttributeFaultNumber:
        IBF = new InternalBaseFault( *((InternalBaseFault*)(*it)->union_ActivityInfoItem.ActivityInfoUnknownAttributeFaultField) );
	failed[ (*it)->ActivityIDField ] = make_pair( (*it)->union_ActivityInfoItem.ActivityInfoUnknownAttributeFaultField->soap_type( ), IBF );
	break;
      default:
        break;
      }
    
//       if( (*it)->__union_ActivityInfoItem == Union_ActivityInfoItem_ActivityInfo_Number){
// 	ComputingActivity *compAct = new ComputingActivity( *((ComputingActivity* )(*it)->union_ActivityInfoItem.ActivityInfoField) );
// 	sucessful[ (*it)->ActivityIDField ] = compAct;
// 	continue;
//       }

//       if( (*it)->__union_ActivityInfoItem == Union_ActivityInfoItem_InternalBaseFault_Number){
// 	InternalBaseFault *IBF = new InternalBaseFault( *((InternalBaseFault*)(*it)->union_ActivityInfoItem.InternalBaseFaultField) );
// 	failed[ (*it)->ActivityIDField ] = IBF;
// 	continue;
//       }
    }
}
