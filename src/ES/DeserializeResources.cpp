#include "glite/ce/es-client-api-c/DeserializeResources.h"
#include "glite/ce/es-client-api-c/DeserializeResourcesOperatingSystem.h"
#include "glite/ce/es-client-api-c/DeserializeResourcesRuntimeEnvironment.h"
#include "glite/ce/es-client-api-c/DeserializeResourcesParallelEnvironment.h"
#include "glite/ce/es-client-api-c/DeserializeResourcesSlotRequirement.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"
#include "glite/ce/es-client-api-c/Resources.h"
#include "glite/ce/es-client-api-c/RuntimeEnvironment.h"
#include "glite/ce/es-client-api-c/ParallelEnvironment.h"
#include "glite/ce/es-client-api-c/CoprocessorType.h"
#include "glite/ce/es-client-api-c/NetworkInfoType.h"
#include "glite/ce/es-client-api-c/SlotRequirement.h"

#include <boost/scoped_ptr.hpp>

using namespace std;
namespace xml = emi_es::client::xml;
namespace wrapper = emi_es::client::wrapper;

/**
 *
 *
 *
 *
 *
 *
 */
wrapper::Resources*
xml::DeserializeResources::get( XMLDoc* doc, 
				const int adIndex )
{
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );
  
  /**
   *
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources", adIndex );
  if( !XMLGetNodeCount::get( doc, buf ) ) 
    return 0;

  vector<wrapper::OperatingSystem> OPs;
  DeserializeResourcesOperatingSystem::get( doc, OPs, adIndex );
  vector<wrapper::RuntimeEnvironment> RTs;
  DeserializeResourcesRuntimeEnvironment::get( doc, RTs, adIndex );
  wrapper::ParallelEnvironment *PE = DeserializeResourcesParallelEnvironment::get( doc, adIndex );
  boost::scoped_ptr< wrapper::ParallelEnvironment > PE_safe_ptr( PE );
  wrapper::SlotRequirement *SR = DeserializeResourcesSlotRequirement::get( doc, adIndex );
  boost::scoped_ptr< wrapper::SlotRequirement > SR_safe_ptr( SR );

  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/Platform", adIndex );
  string *Platform = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > plat_safe_ptr( Platform );

  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/Coprocessor", adIndex );
  string *Coprocessor = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > cop_safe_ptr( Coprocessor );

  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/Coprocessor/@optional", adIndex );
  string *CoprocessorOpt = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > copopt_safe_ptr( CoprocessorOpt );
  
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/NetworkInfo", adIndex );
  string *NetworkInfo = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > neti_safe_ptr( NetworkInfo );

  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/NetworkInfo/@optional", adIndex );
  string *NetworkInfoOpt = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > netiopt_safe_ptr( NetworkInfoOpt );  
  
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/IndividualPhysicalMemory", adIndex );
  string* IPM = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > imp_safe_ptr( IPM );  
  
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/IndividualVirtualMemory", adIndex );
  string* IVM = XMLGetNodeContent::get( doc, buf );  
  boost::scoped_ptr< string > ivp_safe_ptr( IVM );  
  
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/DiskSpaceRequirement", adIndex );
  string* DSR = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > dsr_safe_ptr( DSR );
  
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/RemoteSessionAccess", adIndex );
  string* RSA = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > rsa_safe_ptr( RSA );
  
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/QueueName", adIndex );
  string* QN = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > qn_safe_ptr( QN );
  
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/IndividualCPUTime", adIndex );
  string* ICT = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > ict_safe_ptr( ICT ); 
 
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/NodeAccess", adIndex );
  string* NODES = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > nodes_safe_ptr( NODES );  
  
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/TotalCPUTime", adIndex );
  string* TCT = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > tct_safe_ptr( TCT );    
  
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/WallTime", adIndex );
  string* WT = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > wt_safe_ptr( WT );
  
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/Benchmark", adIndex );
  BenchmarkClassType *B = 0;
  if(XMLGetNodeCount::get( doc, buf ))
    {
      memset( (void*)buf, 0, 1024 );
      sprintf( buf, "//ActivityDescription[%d]/Resources[1]/Benchmark/BenchmarkType", adIndex );
      string *type = XMLGetNodeContent::get( doc, buf );
      boost::scoped_ptr< string > type_safe_ptr( type );
      if(type) {
	memset( (void*)buf, 0, 1024 );
	sprintf( buf, "//ActivityDescription[%d]/Resources[1]/Benchmark/BenchmarkValue", adIndex );
	string *value = XMLGetNodeContent::get( doc, buf );
	boost::scoped_ptr< string > value_safe_ptr( value );
	if(value) {
	  memset( (void*)buf, 0, 1024 );
	  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/Benchmark/@optional", adIndex );
	  string *opt = XMLGetNodeContent::get( doc, buf );
	  boost::scoped_ptr< string > opt_safe_ptr( opt );
	  B = new BenchmarkClassType();
	  B->BenchmarkType = BENCHMARKTYPE_BOGOMIPS;
	  if((*type)=="cfp2006")
	    B->BenchmarkType = BENCHMARKTYPE_CFP2006;
	  if((*type)=="cint2006")
	    B->BenchmarkType = BENCHMARKTYPE_CINT2006;
	  if((*type)=="linpack")
	    B->BenchmarkType = BENCHMARKTYPE_LINPACK;
	  if((*type)=="specfp2000")
	    B->BenchmarkType = BENCHMARKTYPE_SPECFP2000;
	  if((*type)=="specint2000")
	    B->BenchmarkType = BENCHMARKTYPE_SPECINT2000;
	  B->BenchmarkValue = atoll( value->c_str() );
	  B->optional = false;
	  if(opt)
	    if((*opt)=="true")
	      B->optional = true;
	}
      }
    }

  wrapper::CoprocessorType *COP = 0;
  wrapper::NetworkInfoType *NETI = 0;
  int *nodes = 0;
  ULONG64 *VMEM = 0, *MEM = 0, *DISK = 0;
  bool *rsa = 0;
  ULONG64 *ict = 0, *tct = 0, *wct = 0;

  if(Coprocessor) {
    bool opt = false;
    if(CoprocessorOpt)
      if((*CoprocessorOpt)=="true")
	opt = true;
    COP = new wrapper::CoprocessorType((CoprocessorEnumeration)atoi(Coprocessor->c_str()), opt);
  }

  if(NetworkInfo) {
    bool opt = false;
    if(NetworkInfoOpt)
      if((*NetworkInfoOpt)=="true")
	opt = true;
    NETI = new wrapper::NetworkInfoType((NetworkInfoEnumeration)atoi(NetworkInfo->c_str()), opt);
  }

  if(NODES)
    nodes = new int(atoi(NODES->c_str()));
  
  if(IPM)
    MEM = new ULONG64(atoll(IPM->c_str()));
  
  if(IVM)
    VMEM = new ULONG64(atoll(IVM->c_str()));

  if(DSR)
    DISK = new ULONG64(atoll(DSR->c_str()));
  
  if(RSA) {
    if((*RSA)=="true")
      rsa = new bool(true);
    else
      rsa = new bool(false);
  }

  if(ICT)
    ict = new ULONG64( atoll(ICT->c_str()) );

  if(TCT)
    tct = new ULONG64( atoll(TCT->c_str()) );

  if(WT)
    wct = new ULONG64( atoll(WT->c_str()) );

  wrapper::Resources *R = new wrapper::Resources(OPs,
						 Platform,
						 RTs,
						 PE,
						 COP,
						 NETI,
						 nodes,
						 MEM,
						 VMEM,
						 DISK,
						 rsa,
						 B,
						 SR,
						 QN,
						 ict,
						 tct,
						 wct );
						 
  delete COP;
  delete NETI;
  delete nodes;
  delete MEM;
  delete VMEM;
  delete DISK;
  delete rsa;
  delete B;
  delete ict;
  delete tct;
  delete wct;

  return R;
}
