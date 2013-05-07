#include "glite/ce/es-client-api-c/DeserializeApplicationPrePostExecutable.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"
#include "glite/ce/es-client-api-c/WExecutable.h"

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
xml::DeserializeApplicationPrePostExecutable::get( XMLDoc* doc, 
						   vector<wrapper::WExecutable>& PRE,
						   vector<wrapper::WExecutable>& POST,
						   const int adIndex )
{
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );

  /**
   * check for PreExecutable
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/PreExecutable", adIndex );
  int num_preexe = XMLGetNodeCount::get( doc, buf );
  for( int k = 1; k <= num_preexe; ++k ) {
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application/PreExecutable[%d]/Path", adIndex, k );
    string* path = XMLGetNodeContent::get( doc, buf );
    if(!path) continue;
    boost::scoped_ptr< string > path_safe_ptr( path );

    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/PreExecutable[%d]/FailIfExitCodeNotEqualTo", adIndex, k );
    string* failifnoteq = XMLGetNodeContent::get( doc, buf );
    boost::scoped_ptr< string > fail_safe_ptr( failifnoteq );

    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/PreExecutable[%d]/Argument", adIndex, k );
    vector<string> args;
    XMLGetMultipleNodeContent::get( doc, args, buf );

    if( failifnoteq ) {
      int f = atoi(failifnoteq->c_str());
      wrapper::WExecutable thisPre(*path, args, &f );
      PRE.push_back( thisPre );
    }
    else {
      wrapper::WExecutable thisPre(*path, args, 0 );
      PRE.push_back( thisPre );
    }
  }

  /**
   * check for PostExecutable
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/PostExecutable", adIndex );
  int num_postexe = XMLGetNodeCount::get( doc, buf );
  for( int k = 1; k <= num_postexe; ++k ) {
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/PostExecutable[%d]/Path", adIndex, k );
    string* path = XMLGetNodeContent::get( doc, buf );
    if(!path) continue;
    boost::scoped_ptr< string > path_safe_ptr( path );

    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/PostExecutable[%d]/FailIfExitCodeNotEqualTo", adIndex, k );
    string* failifnoteq = XMLGetNodeContent::get( doc, buf );
    boost::scoped_ptr< string > fail_safe_ptr( failifnoteq );

    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/PostExecutable[%d]/Argument", adIndex, k );
    vector<string> args;
    XMLGetMultipleNodeContent::get( doc, args, buf );

    if( failifnoteq ) {
      int f = atoi(failifnoteq->c_str());
      wrapper::WExecutable thisPost(*path, args, &f );
      POST.push_back( thisPost );
    } else {
      wrapper::WExecutable thisPost(*path, args, 0 );
      POST.push_back( thisPost );
    }
  }
}
