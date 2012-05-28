#include "glite/ce/es-client-api-c/ComputingActivity.h"
#include "glite/ce/es-client-api-c/ExtensionsType.h"
#include "glite/ce/es-client-api-c/util.h"
#include <boost/lexical_cast.hpp>

using namespace std;

namespace wr = emi_es::client::wrapper;

std::string wr::ComputingActivity::ComputingActivityTypeStrings[] 
= {std::string("COLLECTION_ELEMENT"), 
   std::string("PARALLEL_ELEMENT"), 
   std::string("SINGLE"), 
   std::string("WORKFLOW_NODE")};
/**
 *
 *
 *
 *
 *
 *
 */
wr::ComputingActivity::ComputingActivity( const string& _ID,
					  string* _Name,
					  const vector<string>& _OtherInfo,
					  time_t* _CreationTime,
					  ULONG64* _Validity,
					  ExtensionsType* ext,
					  const string& _BaseType,
					  const ComputingActivityType _Type,
					  const string& _IDFromEndpoint,
					  const string& _LocalIDFromManager,
					  const string& _JobDescription,
					  const vector<string >& _State,
					  const vector<string >& _RestartState,
					  const int _ExitCode,
					  const string& _ComputingManagerExitCode,
					  const vector<string >& _Error,
					  const unsigned int _WaitingPosition,
					  const string& _UserDomain,
					  const string& _Owner,
					  const string& _LocalOwner,
					  const ULONG64 _RequestedTotalWallTime,
					  const ULONG64 _RequestedTotalCPUTime,
					  const unsigned int _RequestedSlots,
					  const vector<string >& _RequestedApplicationEnvironment,
					  const string& _StdIn,
					  const string& _StdOut,
					  const string& _StdErr,
					  const string& _LogDir,
					  const vector<string >& _ExecutionNode,
					  const string& _Queue,
					  const ULONG64 _UsedTotalWallTime,
					  const ULONG64 _UsedTotalCPUTime,
					  const ULONG64 _UsedMainMemory,
					  const time_t _SubmissionTime,
					  const time_t _ComputingManagerSubmissionTime,
					  const time_t _StartTime,
					  const time_t _ComputingManagerEndTime,
					  const time_t _EndTime,
					  const time_t _WorkingAreaEraseTime,
					  const time_t _ProxyExpirationTime,
					  const string& _SubmissionHost,
					  const string& _SubmissionClientName,
					  const vector<string >& _OtherMessages,
					  const ComputingActivityAssociations& _Associations ) 
{
  ID = _ID;
  Name = (_Name ? new string(*_Name) : 0 );
  OtherInfo = _OtherInfo;
  CreationTime = _CreationTime ? new time_t(*_CreationTime) : 0;
  Validity = (_Validity ? new ULONG64(*_Validity) : 0);
  if(ext)
    Extensions = new ExtensionsType( *ext );
  else
    Extensions = 0;

  BaseType = _BaseType;
  Type = new ns1__ComputingActivityType_USCOREt;//string( _Type );
  (*Type) = (ns1__ComputingActivityType_USCOREt)_Type;
  
  IDFromEndpoint = new string( _IDFromEndpoint );
  LocalIDFromManager = new string( _LocalIDFromManager );
  JobDescription = new string( _JobDescription );
  State = _State;
  RestartState = _RestartState;
  ExitCode = new int;
  *ExitCode = _ExitCode;
  ComputingManagerExitCode = new string( _ComputingManagerExitCode );
  Error = _Error;
  WaitingPosition = new unsigned int;
  *WaitingPosition = _WaitingPosition;
  UserDomain = new string( _UserDomain );
  Owner = _Owner;
  LocalOwner = new string( _LocalOwner );
  RequestedTotalWallTime = new ULONG64;
  *RequestedTotalWallTime = _RequestedTotalWallTime;
  RequestedTotalCPUTime = new ULONG64;
  *RequestedTotalCPUTime = _RequestedTotalCPUTime;
  RequestedSlots = new unsigned int;
  *RequestedSlots = _RequestedSlots;
  RequestedApplicationEnvironment = _RequestedApplicationEnvironment;
  StdIn = new string( _StdIn );
  StdOut = new string( _StdOut );
  StdErr = new string( _StdErr );
  LogDir = new string( _LogDir );
  ExecutionNode = _ExecutionNode;
  Queue = new string( _Queue );
  UsedTotalWallTime = new ULONG64;
  *UsedTotalWallTime = _UsedTotalWallTime;
  UsedTotalCPUTime = new ULONG64;
  *UsedTotalCPUTime = _UsedTotalCPUTime;
  UsedMainMemory = new ULONG64;
  *UsedMainMemory = _UsedMainMemory;
  SubmissionTime = new time_t;
  *SubmissionTime = _SubmissionTime;
  ComputingManagerSubmissionTime = new time_t;
  *ComputingManagerSubmissionTime = _ComputingManagerSubmissionTime;
  StartTime = new time_t;
  *StartTime = _StartTime;
  ComputingManagerEndTime = new time_t;
  *ComputingManagerEndTime = _ComputingManagerEndTime;
  EndTime = new time_t;
  *EndTime = _EndTime;
  WorkingAreaEraseTime = new time_t;
  *WorkingAreaEraseTime = _WorkingAreaEraseTime;
  ProxyExpirationTime = new time_t;
  *ProxyExpirationTime = _ProxyExpirationTime;
  SubmissionHost = new string( _SubmissionHost );
  SubmissionClientName = new string( _SubmissionClientName );
  OtherMessages = _OtherMessages;
  Associations = new ComputingActivityAssociations( _Associations );
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
wr::ComputingActivity::set( const ComputingActivity& src )
{
  ID = src.ID;
  if(src.Name)
    Name = new string(*src.Name);
  else
    Name = 0;

  OtherInfo = src.OtherInfo;
  if(src.CreationTime)
    CreationTime = new time_t(*src.CreationTime);
  else
    CreationTime = 0;

  if(src.Validity)
    Validity = new ULONG64(*src.Validity);
  else
    Validity = 0;

  if(src.Extensions) {
    Extensions = new ns1__Extensions_USCOREt( );
    vector<ns1__Extension_USCOREt*>::const_iterator it = src.Extensions->Extension.begin();
    for( ; it != src.Extensions->Extension.end( ); ++it )
      {
	ns1__Extension_USCOREt* tmp = new ns1__Extension_USCOREt();
	tmp->LocalID = (*it)->LocalID;
	tmp->Key = (*it)->Key;
	tmp->Value = (*it)->Value;
	Extensions->Extension.push_back( tmp );
      }
  }


  Type = 0;
  IDFromEndpoint = 0;
  LocalIDFromManager = 0;
  JobDescription = 0;


  ExitCode = 0;
  ComputingManagerExitCode = 0;

  WaitingPosition = 0;
  UserDomain = 0;

  LocalOwner = 0;
  RequestedTotalWallTime = 0;
  RequestedTotalCPUTime = 0;
  RequestedSlots = 0;

  StdIn = 0;
  StdOut = 0;
  StdErr = 0;
  LogDir = 0;

  Queue = 0;
  UsedTotalWallTime = 0;
  UsedTotalCPUTime = 0;
  UsedMainMemory = 0;
  SubmissionTime = 0;
  ComputingManagerSubmissionTime = 0;
  StartTime = 0;
  ComputingManagerEndTime = 0;
  EndTime = 0;
  WorkingAreaEraseTime = 0;
  ProxyExpirationTime = 0;
  SubmissionHost = 0;
  SubmissionClientName = 0;

  Associations = 0;
  
  BaseType = src.BaseType;
  
  if(src.Type) {
    Type = new ns1__ComputingActivityType_USCOREt;//string(*src.Type);
    (*Type) = *src.Type;
  }
  if(src.IDFromEndpoint) {
    IDFromEndpoint = new string(*src.IDFromEndpoint);
  }
  if(src.LocalIDFromManager) {
    LocalIDFromManager = new string(*src.LocalIDFromManager);
  }
  if(src.JobDescription) {
    JobDescription = new string(*src.JobDescription);
  }

  State = src.State;

  RestartState = src.RestartState;
  
  if(src.ExitCode) {
    ExitCode = new int(*src.ExitCode);
  }
  if(src.ComputingManagerExitCode) {
    ComputingManagerExitCode = new string(*src.ComputingManagerExitCode);
  }
  
  Error = src.Error;

  if(src.WaitingPosition) {
    WaitingPosition = new unsigned int(*src.WaitingPosition);
  }
  if(src.UserDomain) {
    UserDomain = new string(*src.UserDomain);
  }
  
  Owner = src.Owner;

  if(src.LocalOwner) {
    LocalOwner = new string(*src.LocalOwner);
  }
  if(src.RequestedTotalWallTime) {
    RequestedTotalWallTime = new ULONG64(*src.RequestedTotalWallTime);
  }
  if(src.RequestedTotalCPUTime) {
    RequestedTotalCPUTime = new ULONG64(*src.RequestedTotalCPUTime);
  }
  if(src.RequestedSlots) {
    RequestedSlots = new unsigned int(*src.RequestedSlots);
  }

  RequestedApplicationEnvironment = src.RequestedApplicationEnvironment;

  if(src.StdIn) {
    StdIn = new string(*src.StdIn);
  }
  if(src.StdOut) {
    StdOut = new string(*src.StdOut);
  }
  if(src.StdErr) {
    StdErr = new string(*src.StdErr);
  }
  if(src.LogDir) {
    LogDir = new string(*src.LogDir);
  }

  ExecutionNode = src.ExecutionNode;

  if(src.Queue) {
    Queue = new string(*src.Queue);
  }
  if(src.UsedTotalWallTime) {
    UsedTotalWallTime = new ULONG64(*src.UsedTotalWallTime);
  }
  if(src.UsedTotalCPUTime) {
    UsedTotalCPUTime = new ULONG64(*src.UsedTotalCPUTime);
  }
  if(src.UsedMainMemory) {
    UsedMainMemory = new ULONG64(*src.UsedMainMemory);
  }
  if(src.SubmissionTime) {
    SubmissionTime = new time_t(*src.SubmissionTime);
  }
  if(src.ComputingManagerSubmissionTime) {
    ComputingManagerSubmissionTime = new time_t(*src.ComputingManagerSubmissionTime);
  }
  if(src.StartTime) {
    StartTime = new time_t(*src.StartTime);
  }
  if(src.ComputingManagerEndTime) {
    ComputingManagerEndTime = new time_t(*src.ComputingManagerEndTime);
  }
  if(src.EndTime) {
    EndTime = new time_t(*src.EndTime);
  }
  if(src.WorkingAreaEraseTime) {
    WorkingAreaEraseTime = new time_t(*src.WorkingAreaEraseTime);
  }
  if(src.ProxyExpirationTime) {
    ProxyExpirationTime = new time_t(*src.ProxyExpirationTime);
  }
  if(src.SubmissionHost) {
    SubmissionHost = new string(*src.SubmissionHost);
  }
  if(src.SubmissionClientName) {
    SubmissionClientName = new string(*src.SubmissionClientName);
  }

  OtherMessages = src.OtherMessages;

  if(src.Associations) {
    Associations = new ComputingActivityAssociations( *((ComputingActivityAssociations*)src.Associations) );
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
wr::ComputingActivity::free( )
{
  delete Name;
  delete CreationTime;
  delete Validity;
  delete Type;
  delete IDFromEndpoint;
  delete LocalIDFromManager;
  delete JobDescription;

  delete ExitCode;
  delete ComputingManagerExitCode;

  delete WaitingPosition;
  delete UserDomain;

  delete LocalOwner;
  delete RequestedTotalWallTime;
  delete RequestedTotalCPUTime;
  delete RequestedSlots;

  delete StdIn;
  delete StdOut;
  delete StdErr;
  delete LogDir;

  delete Queue;
  delete UsedTotalWallTime;
  delete UsedTotalCPUTime;
  delete UsedMainMemory;
  delete SubmissionTime;
  delete ComputingManagerSubmissionTime;
  delete StartTime;
  delete ComputingManagerEndTime;
  delete EndTime;
  delete WorkingAreaEraseTime;
  delete ProxyExpirationTime;
  delete SubmissionHost;
  delete SubmissionClientName;

  delete Associations;

  vector<ns1__Extension_USCOREt*>::const_iterator it = Extensions->Extension.begin();
  for( ; it != Extensions->Extension.end( ); ++it )
    delete *it;
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
wr::ComputingActivity::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
  
  string out;

  out += tab + "ID=" + ID;
  out += tab + "Name=" + (Name ? *Name : "N/A");
  out += tab + "OtherInfo={" + util::join( OtherInfo, ", ") + "}";
  out += tab + "CreationTime=" + (CreationTime ? boost::lexical_cast<string>( *CreationTime ) + " (" + util::time_to_string( *CreationTime ) + ")" : "N/A");
  out += tab + "Validity=" + (Validity ? boost::lexical_cast<string>( *Validity ) : "N/A");

  if(Extensions)
    out += ((ExtensionsType*)Extensions)->toString( );

  out += tab + "BaseType=" + BaseType;
  if( Type )
    out += tab + "Type=" + ComputingActivityTypeStrings[ *Type ];
  else
    out += tab + "Type=N/A";

  if(IDFromEndpoint)
    out += tab + "IDFromEndpoint=" + ( *IDFromEndpoint );
  else
    out += tab + "IDFromEndpoint=N/A";
  
  if(LocalIDFromManager)
    out += tab + "LocalIDFromManager=" + ( *LocalIDFromManager );
  else
    out += tab + "LocalIDFromManager=N/A";

  if(JobDescription)
    out += tab + "JobDescription=" + ( *JobDescription );
  else
    out += tab + "JobDescription=N/A";

  out += tab + "State={" + util::join( State, ", " ) + "}" ;
  out += tab + "RestartState={" + util::join( RestartState, ", " ) + "}";

  if(ExitCode)
    out += tab + "ExitCode=" + boost::lexical_cast<string>( *ExitCode );
  else
    out += tab + "ExitCode=N/A";
  
  if(ComputingManagerExitCode)
    out += tab + "ComputingManagerExitCode=" + ( *ComputingManagerExitCode );
  else
    out += tab + "ComputingManagerExitCode=N/A";
  
  out += tab + "Error={" + util::join( Error, ", " ) + "}";

  if(WaitingPosition)
    out += tab + "WaitingPosition=" + boost::lexical_cast<string>( *WaitingPosition );
  else
    out += tab + "WaitingPosition=N/A";

  if(UserDomain)
    out += tab + "UserDomain=" + ( *UserDomain );
  else
    out += tab + "UserDomain=N/A";

  out += tab + "Owner=" + boost::lexical_cast<string>( Owner );

  if(LocalOwner)
    out += tab + "LocalOwner=" + ( *LocalOwner );
  else
    out += tab + "LocalOwner=N/A";

  if(RequestedTotalWallTime)
    out += tab + "RequestedTotalWallTime=" + boost::lexical_cast<string>( *RequestedTotalWallTime );
  else
    out += tab + "RequestedTotalWallTime=N/A";
  
  if(RequestedTotalCPUTime)
    out += tab + "RequestedTotalCPUTime=" + boost::lexical_cast<string>( *RequestedTotalCPUTime );
  else
    out += tab + "RequestedTotalCPUTime=N/A";

  if(RequestedSlots)
    out += tab + "RequestedSlots=" + boost::lexical_cast<string>( *RequestedSlots );
  else
    out += tab + "RequestedSlots=N/A";

  out += tab + "RequestedApplicationEnvironment={" + util::join( RequestedApplicationEnvironment, ", " ) + "}";

  if(StdIn)
    out += tab + "StdIn=" + ( *StdIn );
  else
    out += tab + "StdIn=N/A";

  if(StdOut)
    out += tab + "StdOut=" + ( *StdOut );
  else
    out += tab + "StdOut=N/A";

  if(StdErr)
    out += tab + "StdErr=" + ( *StdErr );
  else
    out += tab + "StdErr=N/A";

  if(LogDir)
    out += tab + "LogDir=" + ( *LogDir );
  else
    out += tab + "LogDir=N/A";

  
  out += tab + "ExecutionNode=" + util::join( ExecutionNode, ", " );
  
  if(Queue)
    out += tab + "Queue=" + ( *Queue );
  else
    out += tab + "Queue=N/A";
  
  if(UsedTotalWallTime)
    out += tab + "UsedTotalWallTime=" + boost::lexical_cast<string>( *UsedTotalWallTime );
  else
    out += tab + "UsedTotalWallTime=N/A";

  if(UsedTotalCPUTime)
    out += tab + "UsedTotalCPUTime=" + boost::lexical_cast<string>( *UsedTotalCPUTime );
  else

  if(UsedMainMemory)
    out += tab + "UsedMainMemory=" + boost::lexical_cast<string>( *UsedMainMemory );
  else
    out += tab + "UsedMainMemory=N/A";

  if(SubmissionTime)
    out += tab + "SubmissionTime=" + boost::lexical_cast<string>( *SubmissionTime ) + " (" + util::time_to_string( *SubmissionTime ) + ")";
  else
    out += tab + "SubmissionTime=N/A";

  if(ComputingManagerSubmissionTime)
    out += tab + "ComputingManagerSubmissionTime=" + boost::lexical_cast<string>( *ComputingManagerSubmissionTime ) + " (" + util::time_to_string( *ComputingManagerSubmissionTime ) + ")";
  else
    out += tab + "ComputingManagerSubmissionTime=N/A";
    
  if(StartTime)
    out += tab + "StartTime=" + boost::lexical_cast<string>( *StartTime ) + " (" + util::time_to_string(*StartTime) + ")";
  else
    out += tab + "StartTime=N/A";

  if(ComputingManagerEndTime)
    out += tab + "ComputingManagerEndTime=" + boost::lexical_cast<string>( *ComputingManagerEndTime ) + " (" + util::time_to_string( *ComputingManagerEndTime ) + ")";
  else
    out += tab + "ComputingManagerEndTime=N/A";

  if(EndTime)
    out += tab + "EndTime=" + boost::lexical_cast<string>( *EndTime ) + " (" + util::time_to_string( *EndTime ) + ")";
  else
    out += tab + "EndTime=N/A";

  if(WorkingAreaEraseTime)
    out += tab + "WorkingAreaEraseTime=" + boost::lexical_cast<string>( *WorkingAreaEraseTime ) + " (" + util::time_to_string( *WorkingAreaEraseTime ) + ")";
  else
    out += tab + "WorkingAreaEraseTime=N/A";

  if(ProxyExpirationTime)
    out += tab + "ProxyExpirationTime=" + boost::lexical_cast<string>( *ProxyExpirationTime ) + " (" + util::time_to_string( *ProxyExpirationTime ) + ")";
  else
    out += tab + "ProxyExpirationTime=N/A";

  if(SubmissionHost)
    out += tab + "SubmissionHost=" + ( *SubmissionHost );
  else
    out += tab + "SubmissionHost=N/A";

  if(SubmissionClientName)
    out += tab + "SubmissionClientName=" + ( *SubmissionClientName );
  else
    out += tab + "SubmissionClientName=N/A";

  out += tab + "OtherMessages=" + util::join( OtherMessages, ", " );
      
  if(Associations)
    out += tab + ((ComputingActivityAssociations*)Associations)->toString( tabbed );
    
  return out;
}
