#include "glite/ce/es-client-api-c/DeserializeResourcesOperatingSystem.h"

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
xml::DeserializeResourcesOperatingSystem::get( XMLDoc* doc, 
					       vector<wrapper::WOperatingSystem>& target,
					       const int adIndex )
{
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );
  
  /**
   *
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/OperatingSystem", adIndex );
  int opCount = XMLGetNodeCount::get( doc, buf );
  if( !opCount ) 
    return;

  for( int k = 1; k <= opCount; k++ ) {
   
    /**
     * Get Name tag
     */
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Resources[1]/OperatingSystem[%d]/Name", adIndex, k );
    string* Name = XMLGetNodeContent::get( doc, buf );
    if(!Name) continue;
    boost::scoped_ptr< string > name_safe_ptr( Name );
    /**
     * Get Family tag
     */
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Resources[1]/OperatingSystem[%d]/Family", adIndex, k );
    string* Family = XMLGetNodeContent::get( doc, buf );
    boost::scoped_ptr< string > fam_safe_ptr( Family );
    /**
     * Get Version tag
     */
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Resources[1]/OperatingSystem[%d]/Version", adIndex, k );
    string* Version = XMLGetNodeContent::get( doc, buf );
    boost::scoped_ptr< string > ver_safe_ptr( Version );

    wrapper::WOperatingSystem op(*Name, Family, Version);
    target.push_back(op);
  }

  
}
