#ifndef EMIES_CLIENTLIB_WRAPPERS_COMPACT_H
#define EMIES_CLIENTLIB_WRAPPERS_COMPACT_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/ComputingActivityAssociations.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
        
      class ExtensionsType;

      class ComputingActivity : public ComputingActivityType
      {
      private:
	ComputingActivity() : ns1__ComputingActivity_USCOREt() {}
	  
      public:

	

	enum ComputingActivityType {
	  COLLECTION_ELEMENT = ns1__ComputingActivityType_USCOREt__collectionelement,
	  PARALLEL_ELEMENT   = ns1__ComputingActivityType_USCOREt__collectionelement,
	  SINGLE             = ns1__ComputingActivityType_USCOREt__single,
	  WORKFLOW_NODE      = ns1__ComputingActivityType_USCOREt__workflownode
	};

	static std::string ComputingActivityTypeStrings[];// = {std::string("COLLECTION_ELEMENT"), 
	// std::string("PARALLEL_ELEMENT"), 
	//				      std::string("SINGLE"), 
	//				      std::string("WORKFLOW_NODE")};

	ComputingActivity( const std::string& _ID,
			   std::string* _Name,
			   const std::vector<std::string>& _OtherInfo,
			   time_t* _CreationTime,
			   ULONG64* _Validity,
			   ExtensionsType* ext,
			   const std::string& _BaseType,
			   const ComputingActivityType Type,
			   const std::string& IDFromEndpoint,
			   const std::string& LocalIDFromManager,
			   const std::string& JobDescription,
			   const std::vector<std::string >& State,
			   const std::vector<std::string >& RestartState,
			   const int ExitCode,
			   const std::string& ComputingManagerExitCode,
			   const std::vector<std::string >& Error,
			   const unsigned int WaitingPosition,
			   const std::string& UserDomain,
			   const std::string& Owner,
			   const std::string& LocalOwner,
			   const ULONG64 RequestedTotalWallTime,
			   const ULONG64 RequestedTotalCPUTime,
			   const unsigned int RequestedSlots,
			   const std::vector<std::string >& RequestedApplicationEnvironment,
			   const std::string& StdIn,
			   const std::string& StdOut,
			   const std::string& StdErr,
			   const std::string& LogDir,
			   const std::vector<std::string >& ExecutionNode,
			   const std::string& Queue,
			   const ULONG64 UsedTotalWallTime,
			   const ULONG64 UsedTotalCPUTime,
			   const ULONG64 UsedMainMemory,
			   const time_t SubmissionTime,
			   const time_t ComputingManagerSubmissionTime,
			   const time_t StartTime,
			   const time_t ComputingManagerEndTime,
			   const time_t EndTime,
			   const time_t WorkingAreaEraseTime,
			   const time_t ProxyExpirationTime,
			   const std::string& SubmissionHost,
			   const std::string& SubmissionClientName,
			   const std::vector<std::string >& OtherMessages,
			   const ComputingActivityAssociations& Associations );
	
	ComputingActivity( const ComputingActivity& src ) { this->set( src ); }
	virtual ~ComputingActivity( ) { this->free( ); }
	std::string toString( const bool tabbed = false ) const;

      private:
	void set( const ComputingActivity& );
	void free( );
	ComputingActivity& operator=(const ComputingActivity& ) { return *this; }

      };
    }
  }
}

#endif
