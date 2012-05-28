#include "glite/ce/es-client-api-c/Resources.h"
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
wr::Resources::Resources( const vector<OperatingSystem>& _os, 
	  	          string* platform,
	  	          const vector<RuntimeEnvironment>& runtimes,
		          ParallelEnvironment* pe,
		          CoprocessorType* cop,
		          NetworkInfoType* netinfo,
		          int* nodes,
		          ULONG64* mem,
		          ULONG64* vmem,
		          ULONG64* disk,
		          bool* remotesessionaccess,
	  	          BenchmarkClassType* benchmark,
		          SlotRequirement* slotreq,
		          std::string* queuename,
			  ULONG64* cputime,
			  ULONG64* totcputime,
			  ULONG64* walltime )
{
  
  {
    vector<OperatingSystem>::const_iterator it = _os.begin( );
    for( ; it != _os.end( ); ++it )
    {
      OperatingSystem *os = new OperatingSystem( *it );
      OperatingSystemField.push_back( os );
    }
  }
  Platform = 0;
  if(platform)
    Platform = new string( *platform );
  
  {
    vector<RuntimeEnvironment>::const_iterator it = runtimes.begin( );
    for( ; it != runtimes.end( ); ++it ) 
    {
      RuntimeEnvironment *env = new RuntimeEnvironment( *it );
      RuntimeEnvironmentField.push_back( env );
    }
  }
  
  ParallelEnvironmentField = 0;
  if( pe )
    ParallelEnvironmentField = new ParallelEnvironment( *pe );

  Coprocessor = 0;
  if( cop )
    Coprocessor = new CoprocessorType( *cop );
  
  NetworkInfo = 0;
  if(netinfo)
    NetworkInfo = new NetworkInfoType( *netinfo );

  NodeAccess = 0;
  if(nodes) {
    NodeAccess = new NodeAccessEnumeration;
    *(NodeAccess) = (NodeAccessEnumeration)*nodes;
  }

  IndividualPhysicalMemory = 0;
  if(mem) {
    IndividualPhysicalMemory = new ULONG64;
    *(IndividualPhysicalMemory) = *mem;
  }

  IndividualVirtualMemory = 0;
  if( vmem ){
    IndividualVirtualMemory = new ULONG64;
    *(IndividualVirtualMemory) = *vmem;
  }

  DiskSpaceRequirement = 0;
  if(disk) {
    DiskSpaceRequirement = new ULONG64;
    *(DiskSpaceRequirement) = *disk;
  }

  RemoteSessionAccess = 0;
  if(remotesessionaccess)
    RemoteSessionAccess = new bool(*remotesessionaccess);

  BenchmarkField = 0;
  if(benchmark) {
    BenchmarkField = new BenchmarkClassType();
    BenchmarkField->BenchmarkType = benchmark->BenchmarkType;
    BenchmarkField->BenchmarkValue = benchmark->BenchmarkValue;
    BenchmarkField->optional = benchmark->optional;
  }

  SlotRequirementField = 0;
  if(slotreq)
    SlotRequirementField = new SlotRequirementType( *slotreq );
  
  QueueName = 0;
  if(queuename)
    QueueName = new string( *queuename );

  IndividualCPUTime = 0;
  if(cputime) 
    IndividualCPUTime = new ULONG64( *cputime );

  TotalCPUTime = 0;
  if(totcputime)
    TotalCPUTime      = new ULONG64( *totcputime );

  WallTime = 0;
  if(walltime)
    WallTime          = new ULONG64( *walltime );
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
wr::Resources::set( const Resources& src )
{
  Platform = 0;
  ParallelEnvironmentField = 0;
  Coprocessor = 0 ;
  NetworkInfo = 0;
  NodeAccess = 0;
  IndividualPhysicalMemory = 0;
  IndividualVirtualMemory = 0;
  DiskSpaceRequirement = 0;
  RemoteSessionAccess = 0;
  BenchmarkField = 0;
  SlotRequirementField = 0;
  QueueName = 0;
  IndividualCPUTime = 0 ;
  TotalCPUTime = 0;
  WallTime = 0;

  {
    vector<OperatingSystemType*>::const_iterator it = src.OperatingSystemField.begin( );
  
    for( ; it != src.OperatingSystemField.end( ); ++it )
    {
      OperatingSystemType* os = new OperatingSystem( *((OperatingSystem*)*it) );
							      
      OperatingSystemField.push_back( os );
    }
  }
  
  if( src.Platform )
    Platform = new string( *src.Platform );

  
  {
    vector<RuntimeEnvironmentType*>::const_iterator it = src.RuntimeEnvironmentField.begin( );
    for( ; it != src.RuntimeEnvironmentField.end( ); ++it ) 
    {
      RuntimeEnvironmentType* re = new RuntimeEnvironment( *((RuntimeEnvironment*)*it) );
      RuntimeEnvironmentField.push_back( re );
      
    }
  }
  
  if( src.ParallelEnvironmentField )
    ParallelEnvironmentField = new ParallelEnvironment( *((ParallelEnvironment*)src.ParallelEnvironmentField) );
  
  if(src.Coprocessor)
    Coprocessor = new CoprocessorType( *((CoprocessorType*)src.Coprocessor) );
  
  if( src.NetworkInfo)
    NetworkInfo = new NetworkInfoType( *((NetworkInfoType*)src.NetworkInfo) );
  
  if(src.NodeAccess) {
    NodeAccess = new NodeAccessEnumeration;
    *(NodeAccess) = *src.NodeAccess;
  }

  if(src.IndividualPhysicalMemory) {
    IndividualPhysicalMemory = new ULONG64;
    *(IndividualPhysicalMemory) = *src.IndividualPhysicalMemory;
  }

  if( src.IndividualVirtualMemory ) {
    IndividualVirtualMemory = new ULONG64;
    *(IndividualVirtualMemory) = *src.IndividualVirtualMemory;
  }

  if( src.DiskSpaceRequirement ) {
    DiskSpaceRequirement = new ULONG64;
    *(DiskSpaceRequirement) = *src.DiskSpaceRequirement;
  }

  if( src.RemoteSessionAccess ) {
    RemoteSessionAccess = new bool;
    *(RemoteSessionAccess) = *src.RemoteSessionAccess;
  }

  if(src.BenchmarkField) {
    BenchmarkField = new BenchmarkClassType();
    BenchmarkField->BenchmarkType  = src.BenchmarkField->BenchmarkType;
    BenchmarkField->BenchmarkValue = src.BenchmarkField->BenchmarkValue;
    BenchmarkField->optional       = src.BenchmarkField->optional;
  }
  
  if( src.SlotRequirementField)
    SlotRequirementField = new SlotRequirement( *((SlotRequirement*)src.SlotRequirementField) );
  
  if(src.QueueName)
    QueueName = new string( *src.QueueName );

  if(src.IndividualCPUTime)
    IndividualCPUTime = new ULONG64(*src.IndividualCPUTime);

  if(src.TotalCPUTime)
    TotalCPUTime = new ULONG64(*src.TotalCPUTime);

  if(src.WallTime)
    WallTime = new ULONG64(*src.WallTime);
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::Resources::Resources( const Resources& src ) : ResourcesType()
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
wr::Resources::free( )
{
  {
    vector<OperatingSystemType*>::const_iterator it = OperatingSystemField.begin( );
    for( ; it != OperatingSystemField.end( ); ++ it )
    {
      OperatingSystem *current = (OperatingSystem *)*it;
      delete current;
    }
  }
  OperatingSystemField.clear();
  
  delete Platform;
  
  {
    vector<RuntimeEnvironmentType*>::const_iterator it = RuntimeEnvironmentField.begin( );
    for( ; it != RuntimeEnvironmentField.end( ); ++it ) 
    {
      RuntimeEnvironment* current = (RuntimeEnvironment*)*it;
      delete current;
    }
  }
  RuntimeEnvironmentField.clear();
  
  delete ParallelEnvironmentField;
  delete Coprocessor;
  delete NetworkInfo;
  delete NodeAccess;
  delete IndividualPhysicalMemory;
  delete IndividualVirtualMemory;
  delete DiskSpaceRequirement;
  delete RemoteSessionAccess;
  delete BenchmarkField;
  delete SlotRequirementField;
  delete QueueName;
  delete IndividualCPUTime;
  delete TotalCPUTime;
  delete WallTime;
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
wr::Resources::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
  
  string out;
  out = tab + "Platform=";
  if(Platform)
    out += *Platform;
  else
    out += "N/A";

  {
    vector<OperatingSystemType*>::const_iterator it = OperatingSystemField.begin( );
    int counter = 0;
    out += "\n" + tab + "==============================";
    for( ; it != OperatingSystemField.end( ); ++it )
      {
	out += tab + "OperatingSystem[" + boost::lexical_cast<string>( counter ) + "]";
	out += tab + "-------------------";
	OperatingSystem *current = (OperatingSystem *)*it;
	out += current->toString( tabbed );
	counter++;
      }
    out += "\n" + tab + "==============================";
  }

  {
    vector<RuntimeEnvironmentType*>::const_iterator it = RuntimeEnvironmentField.begin( );
    int counter = 0;
    //out += tab + "======================";
    for( ; it != RuntimeEnvironmentField.end( ); ++it )
      {
	out += tab + "RuntimeEnvironment[" + boost::lexical_cast<string>( counter ) + "]";
	out += tab + "----------------------";
	RuntimeEnvironment *current = (RuntimeEnvironment *)*it;
	out += current->toString( tabbed );
	counter++;
      }
    out += tab + "==============================";
  }

  if(Coprocessor) {
    CoprocessorType* co = (CoprocessorType*)Coprocessor;
    out += co->toString( tabbed );
  }

  if(NetworkInfo) {
    NetworkInfoType* ni = (NetworkInfoType*)NetworkInfo;
    out += ni->toString( tabbed );
  }

  
  out += tab + "NodeAccess=";
  if(NodeAccess)
    out += boost::lexical_cast<string>( *NodeAccess );
  else
    out += "N/A";

  out += tab + "IndividualPhysicalMemory=";
  if(IndividualPhysicalMemory)
    out += boost::lexical_cast<string>( *IndividualPhysicalMemory );
  else
    out += "N/A";

  out += tab + "IndividualVirtualMemory=";
  if(IndividualVirtualMemory)
    out += boost::lexical_cast<string>( *IndividualVirtualMemory );
  else
    out += "N/A";

  out += tab + "DiskSpaceRequirement=";
  if(DiskSpaceRequirement)
    out += boost::lexical_cast<string>( *DiskSpaceRequirement );
  else
    out += "N/A";
  
  out += tab + "RemoteSessionAccess=";
  if(RemoteSessionAccess)
    out += boost::lexical_cast<string>( *RemoteSessionAccess );
  else
    out += "N/A";

  out += tab + "Benchmark.BenchmarkType=";
  out += BenchmarkField->BenchmarkType;
  out += tab + "Benchmark.BenchmarkValue=";
  out += BenchmarkField->BenchmarkValue;
  out += tab + "Benchmark.optional=";
  out += boost::lexical_cast<string>( BenchmarkField->optional );

  if(QueueName)
    out += tab + "QueueName=" + *QueueName;
  else
    out += tab + "QueueName=N/A";

  return out;
}
