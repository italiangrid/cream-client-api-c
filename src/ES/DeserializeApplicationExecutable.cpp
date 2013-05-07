#include "glite/ce/es-client-api-c/DeserializeApplicationExecutable.h"
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
wrapper::WExecutable*
xml::DeserializeApplicationExecutable::get( XMLDoc* doc, const int adIndex )
{

  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );

  /**
   * check for Executable
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/Executable", adIndex );
  if( 0 == XMLGetNodeCount::get( doc, buf ) )
    return 0;

  /**
   * check for Executable/Path
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/Executable[1]/Path", adIndex );
  string *path = XMLGetNodeContent::get( doc, buf );
  if(!path)
    return 0;
  boost::scoped_ptr< string > path_safe_ptr( path );
  
  /**
   * check for Executable/FailIf...
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/Executable[1]/FailIfExitCodeNotEqualTo", adIndex );
  
  string* failifnoteq = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > fail_safe_ptr( failifnoteq );
  vector<string> args;
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/Executable[1]/Argument", adIndex );
  XMLGetMultipleNodeContent::get( doc, args, buf );

  if(failifnoteq) {
    int f = atoi(failifnoteq->c_str());
    return new wrapper::WExecutable( *path, args, &f );
  }
  else
    return new wrapper::WExecutable( *path, args, 0 );
}
