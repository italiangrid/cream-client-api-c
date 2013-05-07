#include "glite/ce/es-client-api-c/DeserializeResourcesParallelEnvironment.h"
#include "glite/ce/es-client-api-c/WParallelEnvironment.h"

#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"

#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
namespace xml = emi_es::client::xml;

/**
 *
 *
 *
 *
 *
 *
 */
emi_es::client::wrapper::WParallelEnvironment*
xml::DeserializeResourcesParallelEnvironment::get( XMLDoc* doc, 
						   const int adIndex )
{
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );
  
  /**
   *
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/ParallelEnvironment", adIndex );
  int opCount = XMLGetNodeCount::get( doc, buf );
  if( !opCount ) 
    return 0;

  
  
  /**
   * Get Type tag
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/ParallelEnvironment/Type", adIndex );
  string* Type = XMLGetNodeContent::get( doc, buf );
  if(!Type) return 0;//continue;
  boost::scoped_ptr< string > name_safe_ptr( Type );

  /**
   * Get Version tag
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/ParallelEnvironment/Version", adIndex );
  string* Version = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > fam_safe_ptr( Version );
  
  /**
   * Get Option tag
   */
  
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/ParallelEnvironment/Option", adIndex );
  opCount = XMLGetNodeCount::get( doc, buf );
  vector<OptionType> opts;
  for(int k = 1; k <= opCount; ++k ) 
    {
      memset( (void*)buf, 0, 1024 );
      sprintf( buf, "//ActivityDescription[%d]/Resources[1]/ParallelEnvironment/Option[%d]/Name", adIndex, k );
      string* name = XMLGetNodeContent::get( doc, buf );
      if(!name)
	continue;
	
      memset( (void*)buf, 0, 1024 );
      sprintf( buf, "//ActivityDescription[%d]/Resources[1]/ParallelEnvironment/Option[%d]/Value", adIndex, k );
      string* value = XMLGetNodeContent::get( doc, buf );
      
      OptionType opt;
      opt.Name = *name;
      delete name;
      if(value) {
        opt.Value = *value;
        delete value;
      }
      opts.push_back( opt );
    }
  
    
  /**
   * Get ProcessesPeHost tag
   */
  
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/ParallelEnvironment/ProcessesPerHost", adIndex);
  string* number = XMLGetNodeContent::get( doc, buf );
  ProcessesPerHost *pphost = 0;
  if(number) {
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Resources[1]/ParallelEnvironment/ProcessesPerHost/@useSlotsPerHost", adIndex);
    string* opt = XMLGetNodeContent::get( doc, buf );
    bool optional = false;
    if(opt) {
      if((*opt)=="true")
	 optional = true;//boost::lexical_cast<bool>(*opt);

      delete opt;
    }
    
    pphost = new ProcessesPerHost();
    pphost->useSlotsPerHost = optional;
    pphost->__item = boost::lexical_cast<unsigned long long>(*number);
    delete number;
  }
  
    
  /**
   * Get ThreadsPerProcess tag
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/ParallelEnvironment/ThreadsPerProcess", adIndex);
  number = XMLGetNodeContent::get( doc, buf );
  ThreadsPerProcess *tphost = 0;
  if(number) {
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Resources[1]/ParallelEnvironment/ThreadsPerProcess/@useSlotsPerHost", adIndex);
    string* opt = XMLGetNodeContent::get( doc, buf );
    bool optional = false;
    if(opt) {
      if((*opt)=="true")
	optional = true;//boost::lexical_cast<bool>(*opt);
      delete opt;
    }
    
    tphost = new ThreadsPerProcess();
    tphost->useSlotsPerHost = optional;
    tphost->__item = boost::lexical_cast<unsigned long long>(*number);
    delete number;
  }
  
  emi_es::client::wrapper::WParallelEnvironment *PE = new emi_es::client::wrapper::WParallelEnvironment( *Type, Version, pphost, tphost, opts );
  delete pphost;
  delete tphost;
  return PE;//new emi_es::client::wrapper::ParallelEnvironment( *Type, Version, pphost, tphost, opts );
}
