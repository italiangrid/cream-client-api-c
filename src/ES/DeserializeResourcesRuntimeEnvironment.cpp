#include "glite/ce/es-client-api-c/DeserializeResourcesRuntimeEnvironment.h"

#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"

#include <boost/scoped_ptr.hpp>

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
void
xml::DeserializeResourcesRuntimeEnvironment::get( XMLDoc* doc, 
						  vector<wrapper::WRuntimeEnvironment>& target,
						  const int adIndex )
{
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );
  
  /**
   *
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/RuntimeEnvironment", adIndex );
  int opCount = XMLGetNodeCount::get( doc, buf );
  if( !opCount ) 
    return;

  for( int k = 1; k <= opCount; k++ ) {
   
    /**
     * Get Name tag
     */
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Resources[1]/RuntimeEnvironment[%d]/Name", adIndex, k );
    string* Name = XMLGetNodeContent::get( doc, buf );
    if(!Name) continue;
    boost::scoped_ptr< string > name_safe_ptr( Name );
    
    /**
     * Get Version tag
     */
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Resources[1]/RuntimeEnvironment[%d]/Version", adIndex, k );
    string* Version = XMLGetNodeContent::get( doc, buf );
    boost::scoped_ptr< string > ver_safe_ptr( Version );

    /**
     * Get Options (vector<string>)
     */
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Resources[1]/RuntimeEnvironment[%d]/Option", adIndex, k );
    int optCount = XMLGetNodeCount::get( doc, buf );
    vector<string> Options;
    for( int jj = 1; jj <= optCount; ++jj ) {
      memset( (void*)buf, 0, 1024 );
      sprintf( buf, "//ActivityDescription[%d]/Resources[1]/RuntimeEnvironment[%d]/Option[%d]", adIndex, k,jj );
      string* opt = XMLGetNodeContent::get( doc, buf );
      boost::scoped_ptr< string > opt_safe_ptr( opt );
      if(opt)
	Options.push_back( *opt );
    }

    /**
     * Get optional attribute
     */
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Resources[1]/RuntimeEnvironment[%d]/@optional", adIndex, k );
    bool optional = false;
    string* _opt = XMLGetNodeContent::get( doc, buf );
    if(_opt) {
      if((*_opt)=="true")
	optional = true;//boost::lexical_cast<bool>(*_opt);
      delete _opt;
    }

    wrapper::WRuntimeEnvironment env(*Name, Version, Options, optional);
    target.push_back(env);
  }
}
