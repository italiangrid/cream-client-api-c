#ifndef EMIES_CLIENTLIB_COMM_CALLFACT_H
#define EMIES_CLIENTLIB_COMM_CALLFACT_H

#include "glite/ce/es-client-api-c/AbstractCall.h"
// #include "CallFactory.h"
// #include "CancelActivityCall.h"
// #include "CreateActivityCall.h"
// #include "GetActivityInfoCall.h"
// #include "GetActivityStatusCall.h"
// #include "GetDelegationInfoCall.h"
// #include "InitDelegationCall.h"
// #include "ListActivityCall.h"
// #include "ManageActivityCall.h"
// #include "PauseActivityCall.h"
// #include "PutDelegationCall.h"
// #include "RestartActivityCall.h"
// #include "ResumeActivityCall.h"
// #include "WipeActivityCall.h"

//#include "wrappers/CreateActivities.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {

    namespace wrapper {
      class InitDelegation;
      class ListActivities;
      class CreateActivities;
    };

    namespace comm {
      
      class CallFactory {

      public:	
	/**
	 * resume,restart,pause,wipe,cancel, status
	 */
	static AbstractCall *makeCall( const std::string&,
				       const std::vector<std::string>&,
				       const AbstractCall::ACTIVITYMANAGEMENTCALLS );
	
	/**
	 * CreateActivity
	 */
	static AbstractCall *makeCall( const std::string&,
				       wrapper::CreateActivities* );
	
	/**
	 * GetActivityInfo
	 */
	static AbstractCall *makeCall( const std::string&,
				       const std::vector<std::string>&,
				       const std::vector<std::string>& ); // 

	/**
	 * GetDelegationInfo
	 */
	static AbstractCall *makeCall( const std::string&,
				       const std::string& );
	
	/**
	 * InitDelegation
	 */
	static AbstractCall *makeCall( const std::string&,
				       wrapper::InitDelegation* );
	
	/**
	 * ListActivities
	 */
	static AbstractCall *makeCall( const std::string&,
				       wrapper::ListActivities* );
	
	/**
	 * PutDelegation
	 */
	static AbstractCall *makeCall( const std::string&,
				       const std::string&,
				       const std::string& );

        /**
         * NotifyService
         */
        static AbstractCall *makeCall( const std::string&,
				       const std::vector<std::pair<std::string, AbstractCall::NOTIFYMESSAGE> >& );

      };

    }
  }
}

#endif
