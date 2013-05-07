#include "glite/ce/es-client-api-c/DeserializeApplicationRemoteLogging.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"

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
void
xml::DeserializeApplicationRemoteLogging::get( XMLDoc* doc, vector<wrapper::WRemoteLogging>& target, const int adIndex )
{

  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );

  /**
   * check for num of Environment tags
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/RemoteLogging", adIndex );
  int rlCount = XMLGetNodeCount::get( doc, buf );
  if(!rlCount) {
    return;
  }

  /**
   * Load all Environments tags
   */
  for( int k = 1; k <= rlCount; ++k ) {

    string *ServiceType=0, *URL=0, *opt=0;
    
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/RemoteLogging[%d]/ServiceType", adIndex, k );
    ServiceType = XMLGetNodeContent::get( doc, buf );
    if(!ServiceType) continue;
    boost::scoped_ptr< string > st_safe_ptr( ServiceType );
    
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/RemoteLogging[%d]/URL", adIndex, k );
    URL = XMLGetNodeContent::get( doc, buf );
    boost::scoped_ptr< string > url_safe_ptr( URL );

    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/RemoteLogging[%d]/@optional", adIndex, k );
    opt = XMLGetNodeContent::get( doc, buf );
    boost::scoped_ptr< string > opt_safe_ptr( opt );

    bool _opt = false;
    if(opt) 
      if(*opt == "true")
	_opt = true;

    wrapper::WRemoteLogging RL( *ServiceType, URL, _opt );
    target.push_back( RL );
  }
}
