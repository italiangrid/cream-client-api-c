#include "glite/ce/es-client-api-c/DeserializeApplicationNotification.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"
#include "glite/ce/es-client-api-c/WActivityStatus.h"

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
xml::DeserializeApplicationNotification::get( XMLDoc* doc, vector<wrapper::WNotification>& target, const int adIndex )
{

  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );

  /**
   * check for Notification tag
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/Notification", adIndex );
  int notifCount = XMLGetNodeCount::get( doc, buf );
  if( !notifCount )
    return;

  /**
   * Load notifications
   */
  for( int k = 1; k <= notifCount; ++k ) {
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/Notification[%d]/Protocol", adIndex, k );
    string *protocol = XMLGetNodeContent::get( doc, buf );
    if(!protocol) continue;
    boost::scoped_ptr< string > proto_safe_ptr( protocol );
  
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/Notification[%d]/Recipient", adIndex, k ); 
    vector<string> Recipients;
    XMLGetMultipleNodeContent::get( doc, Recipients, buf );
    
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/Notification[%d]/OnState", adIndex, k ); 
    vector<string> OnStates;
    XMLGetMultipleNodeContent::get( doc, OnStates, buf );
   
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/Notification[%d]/@optional", adIndex, k );
    string *opt = XMLGetNodeContent::get( doc, buf );
    boost::scoped_ptr< string > opt_safe_ptr( opt );
      
//     int proto = 0;
//     // here protocol is for sure not NULL because there's a check above (if(!protocol) continue;)
//     if(*protocol == "email")
//       proto = 0;
    
    bool *_opt = 0;//false;
    if(opt) {
      if(*opt == "true") 
	_opt = new bool(true);
      else
        _opt = new bool(false);
    }
    vector<string>::const_iterator it = OnStates.begin();
    vector< ActivityStatusState > onstates;
    for( ; it != OnStates.end( ); ++it ) {
      onstates.push_back( wrapper::WActivityStatus::getStatusNumber( *it ) );
    }

    wrapper::WNotification N( (protocol ? wrapper::WNotification::getProtoNumber( protocol->c_str() ) : (ProtocolTypeEnumeration)UNKNOWN), Recipients, onstates, _opt );
    target.push_back( N );
  }
}
