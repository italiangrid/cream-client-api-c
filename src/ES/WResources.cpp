#include "glite/ce/es-client-api-c/WResources.h"
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
wr::WResources::WResources( const vector<WOperatingSystem>& _os, 
	  	            string* platform,
	  	            const vector<WRuntimeEnvironment>& runtimes,
		            WParallelEnvironment* pe,
		            WCoprocessorType* cop,
		            WNetworkInfoType* netinfo,
		            NodeAccessEnumeration* nodes,
		            ULONG64* mem,
		            ULONG64* vmem,
		            ULONG64* disk,
		            bool* remotesessionaccess,
	  	            Benchmark* benchmark,
		            WSlotRequirement* slotreq,
		            std::string* queuename,
			    ULONG64* cputime,
			    ULONG64* totcputime,
			    ULONG64* walltime )
{
  
  {
    vector<WOperatingSystem>::const_iterator it = _os.begin( );
    for( ; it != _os.end( ); ++it )
    {
      WOperatingSystem *os = new WOperatingSystem( *it );
      OperatingSystemField.push_back( os );
    }
  }
  Platform = 0;
  if(platform)
    Platform = new string( *platform );
  
  {
    vector<WRuntimeEnvironment>::const_iterator it = runtimes.begin( );
    for( ; it != runtimes.end( ); ++it ) 
    {
      WRuntimeEnvironment *env = new WRuntimeEnvironment( *it );
      RuntimeEnvironmentField.push_back( env );
    }
  }
  
  ParallelEnvironmentField = 0;
  if( pe )
    ParallelEnvironmentField = new WParallelEnvironment( *pe );

  Coprocessor = 0;
  if( cop )
    Coprocessor = new WCoprocessorType( *cop );
  
  NetworkInfo = 0;
  if(netinfo)
    NetworkInfo = new WNetworkInfoType( *netinfo );

  NodeAccess = 0;
  if(nodes) {
    NodeAccess = new NodeAccessEnumeration;
    *(NodeAccess) = *nodes;
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
    BenchmarkField = new Benchmark();
    BenchmarkField->BenchmarkType = benchmark->BenchmarkType;
    BenchmarkField->BenchmarkValue = benchmark->BenchmarkValue;
    BenchmarkField->optional = benchmark->optional;
  }

  SlotRequirementField = 0;
  if(slotreq)
    SlotRequirementField = new WSlotRequirement( *slotreq );
  
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
wr::WResources::set( const WResources& src )
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
    vector<OperatingSystem*>::const_iterator it = src.OperatingSystemField.begin( );
  
    for( ; it != src.OperatingSystemField.end( ); ++it )
    {
      WOperatingSystem* os = new WOperatingSystem( *((WOperatingSystem*)*it) );
							      
      OperatingSystemField.push_back( os );
    }
  }
  
  if( src.Platform )
    Platform = new string( *src.Platform );

  
  {
    vector<RuntimeEnvironment*>::const_iterator it = src.RuntimeEnvironmentField.begin( );
    for( ; it != src.RuntimeEnvironmentField.end( ); ++it ) 
    {
      WRuntimeEnvironment* re = new WRuntimeEnvironment( *((WRuntimeEnvironment*)*it) );
      RuntimeEnvironmentField.push_back( re );
      
    }
  }
  
  if( src.ParallelEnvironmentField )
    ParallelEnvironmentField = new WParallelEnvironment( *((WParallelEnvironment*)src.ParallelEnvironmentField) );
  
  if(src.Coprocessor)
    Coprocessor = new WCoprocessorType( *((WCoprocessorType*)src.Coprocessor) );
  
  if( src.NetworkInfo)
    NetworkInfo = new WNetworkInfoType( *((WNetworkInfoType*)src.NetworkInfo) );
  
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
    BenchmarkField = new Benchmark();
    BenchmarkField->BenchmarkType  = src.BenchmarkField->BenchmarkType;
    BenchmarkField->BenchmarkValue = src.BenchmarkField->BenchmarkValue;
    BenchmarkField->optional       = src.BenchmarkField->optional;
  }
  
  if( src.SlotRequirementField)
    SlotRequirementField = new WSlotRequirement( *((WSlotRequirement*)src.SlotRequirementField) );
  
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
wr::WResources::WResources( const WResources& src ) : Resources()
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
wr::WResources::free( )
{
  {
    vector<OperatingSystem*>::const_iterator it = OperatingSystemField.begin( );
    for( ; it != OperatingSystemField.end( ); ++ it )
    {
      WOperatingSystem *current = (WOperatingSystem *)*it;
      delete current;
    }
  }
  OperatingSystemField.clear();
  
  delete Platform;
  
  {
    vector<RuntimeEnvironment*>::const_iterator it = RuntimeEnvironmentField.begin( );
    for( ; it != RuntimeEnvironmentField.end( ); ++it ) 
    {
      WRuntimeEnvironment* current = (WRuntimeEnvironment*)*it;
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
wr::WResources::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
  
  string out;
  out = tab + "Resource:";
  out = tab + "  Platform=";
  if(Platform)
    out += *Platform;
  else
    out += "N/A";

  {
    vector<OperatingSystem*>::const_iterator it = OperatingSystemField.begin( );
    int counter = 0;
    //out += "\n" + tab + "==============================";
    for( ; it != OperatingSystemField.end( ); ++it )
      {
	out += tab + "  OperatingSystem[" + boost::lexical_cast<string>( counter ) + "]";
	out += tab + "  -------------------";
	WOperatingSystem *current = (WOperatingSystem *)*it;
	out += current->toString( tabbed );
	counter++;
      }
    //out += "\n" + tab + "==============================";
  }

  {
    vector<RuntimeEnvironment*>::const_iterator it = RuntimeEnvironmentField.begin( );
    int counter = 0;
    //out += tab + "======================";
    for( ; it != RuntimeEnvironmentField.end( ); ++it )
      {
	out += tab + "  RuntimeEnvironment[" + boost::lexical_cast<string>( counter ) + "]";
	out += tab + "  ----------------------";
	WRuntimeEnvironment *current = (WRuntimeEnvironment *)*it;
	out += current->toString( tabbed );
	counter++;
      }
    //out += tab + "==============================";
  }

  if(Coprocessor) {
    WCoprocessorType* co = (WCoprocessorType*)Coprocessor;
    out += co->toString( tabbed );
  }

  if(NetworkInfo) {
    WNetworkInfoType* ni = (WNetworkInfoType*)NetworkInfo;
    out += ni->toString( tabbed );
  }

  
  out += tab + "  NodeAccess=";
  if(NodeAccess)
    out += boost::lexical_cast<string>( *NodeAccess );
  else
    out += "N/A";

  out += tab + "  IndividualPhysicalMemory=";
  if(IndividualPhysicalMemory)
    out += boost::lexical_cast<string>( *IndividualPhysicalMemory );
  else
    out += "N/A";

  out += tab + "  IndividualVirtualMemory=";
  if(IndividualVirtualMemory)
    out += boost::lexical_cast<string>( *IndividualVirtualMemory );
  else
    out += "N/A";

  out += tab + "  DiskSpaceRequirement=";
  if(DiskSpaceRequirement)
    out += boost::lexical_cast<string>( *DiskSpaceRequirement );
  else
    out += "N/A";
  
  out += tab + "  RemoteSessionAccess=";
  if(RemoteSessionAccess)
    out += boost::lexical_cast<string>( *RemoteSessionAccess );
  else
    out += "N/A";

  out += tab + "  Benchmark.BenchmarkType=";
  out += BenchmarkField->BenchmarkType;
  out += tab + "  Benchmark.BenchmarkValue=";
  out += BenchmarkField->BenchmarkValue;
  out += tab + "  Benchmark.optional=";
  out += boost::lexical_cast<string>( BenchmarkField->optional );

  if(QueueName)
    out += tab + "  QueueName=" + (QueueName ? *QueueName : "N/A");
  return out;
}
