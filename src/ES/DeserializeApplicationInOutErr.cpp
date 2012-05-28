#include "glite/ce/es-client-api-c/DeserializeApplicationInOutErr.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"

#include <boost/scoped_ptr.hpp>
#include <cstring>

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
boost::tuple<string*, string*, string*>
xml::DeserializeApplicationInOutErr::get( XMLDoc* doc, const int adIndex )
{ 
  
  string *in = 0, *out = 0, *err = 0;

  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > classad_safe_ptr( buf );
  
  /**
   * check for Input
   */
  ::memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/Input", adIndex );
  in=XMLGetNodeContent::get( doc, buf );

  /**
   * check for Output
   */
  ::memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/Output", adIndex );
  out=XMLGetNodeContent::get( doc, buf );

  /**
   * check for Error
   */
  ::memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/Error", adIndex );
  err = XMLGetNodeContent::get( doc, buf );

  return boost::make_tuple( in, out, err );
}
