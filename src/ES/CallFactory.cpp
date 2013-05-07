#include "glite/ce/es-client-api-c/CallFactory.h"
//#include "glite/ce/es-client-api-c/CancelActivityCall.h"
#include "glite/ce/es-client-api-c/CreateActivityCall.h"
//#include "glite/ce/es-client-api-c/GetActivityInfoCall.h"
//#include "glite/ce/es-client-api-c/GetActivityStatusCall.h"
//#include "glite/ce/es-client-api-c/GetDelegationInfoCall.h"
//#include "glite/ce/es-client-api-c/InitDelegationCall.h"
//#include "glite/ce/es-client-api-c/ListActivityCall.h"
//#include "glite/ce/es-client-api-c/ManageActivityCall.h"
//#include "glite/ce/es-client-api-c/PauseActivityCall.h"
//#include "glite/ce/es-client-api-c/PutDelegationCall.h"
//#include "glite/ce/es-client-api-c/RestartActivityCall.h"
//#include "glite/ce/es-client-api-c/ResumeActivityCall.h"
//#include "glite/ce/es-client-api-c/WipeActivityCall.h"
//#include "glite/ce/es-client-api-c/NotifyServiceCall.h"
//#include "glite/ce/es-client-api-c/GetResourceInfoCall.h"
//#include "glite/ce/es-client-api-c/QueryResourceInfoCall.h"


#include "glite/ce/es-client-api-c/CallFactory.h"

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
 *
 */
// AbstractCall*
// CallFactory::makeCall( const string& endpoint,
// 		       const vector<string>& ActIDs,
// 		       const AbstractCall::ACTIVITYMANAGEMENTCALLS calltype)
// {
//   switch(calltype) {
//   case AbstractCall::CANCEL:
//     return new CancelActivityCall( endpoint, ActIDs );
//     break;
//   case AbstractCall::PAUSE:
//     return new PauseActivityCall( endpoint, ActIDs );
//     break;
//   case AbstractCall::WIPE:
//     return new WipeActivityCall( endpoint, ActIDs );
//     break;
//   case AbstractCall::RESUME:
//     return new ResumeActivityCall( endpoint, ActIDs );
//     break;
//   case AbstractCall::RESTART:
//     return new RestartActivityCall( endpoint, ActIDs );
//     break;
//    case AbstractCall::STATUS:
//      return new GetActivityStatusCall( endpoint, ActIDs );
//      break;
//   default:
//     return 0;
//     break;
//   }
// }

/**
 *
 *
 *
 *
 *
 *
 *
 *
 */
AbstractCall*
CallFactory::makeCall( const string& endpoint,
		       wrapper::WCreateActivity* act)
{
  return new CreateActivityCall( endpoint, act );
}

/**
 *
 *
 *
 *
 *
 *
 *
 *
 */
// AbstractCall*
// CallFactory::makeCall( const string& endpoint,
// 		       const vector<string>& IDs,
// 		       const vector<string>& attrs)
// {
//   return new GetActivityInfoCall( endpoint, IDs, attrs );
// }

/**
 *
 *
 *
 *
 *
 *
 *
 *
 */
// AbstractCall*
// CallFactory::makeCall( const string& endpoint,
// 		       const string& ID )
// {
//   return new GetDelegationInfoCall( endpoint, ID );
// }

/**
 *
 *
 *
 *
 *
 *
 *
 *
 */
// AbstractCall*
// CallFactory::makeCall( const string& endpoint,
// 		       wrapper::InitDelegation* init )
// {
//   return new InitDelegationCall( endpoint ,init );
// }

/**
 *
 *
 *
 *
 *
 *
 *
 *
 */
// AbstractCall*
// CallFactory::makeCall( const string& endpoint,
// 		       wrapper::ListActivities* list )
// {
//   return new ListActivityCall( endpoint, list );
// }

/**
 *
 *
 *
 *
 *
 *
 *
 *
 */
// AbstractCall*
// CallFactory::makeCall( const string& endpoint ,
// 		       const string& ID,
// 		       const string& cred)
// {
//   return new PutDelegationCall( endpoint, ID, cred );
// }

/**
 *
 *
 *
 *
 *
 *
 *
 *
 */
// AbstractCall*
// CallFactory::makeCall( const string& endpoint,
//                        const vector<pair<string, AbstractCall::NOTIFYMESSAGE> >& attrs )
// {
//   return new NotifyServiceCall( endpoint , attrs );
// }

/**
 *
 *
 *
 *
 *
 *
 *
 *
 */
// AbstractCall*
// CallFactory::makeCall( const string& endpoint, 
// 		       const int type, 
// 		       const string& dialect, 
// 		       const string& query )
// {
//   if(type==0)
//     return new GetResourceInfoCall( endpoint );
//   else {
//     return new QueryResourceInfoCall( endpoint, dialect, query );
//   }
// }
