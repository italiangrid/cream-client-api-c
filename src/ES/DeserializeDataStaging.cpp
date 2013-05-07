#include "glite/ce/es-client-api-c/DeserializeDataStaging.h"
#include "glite/ce/es-client-api-c/DeserializeInputFile.h"
#include "glite/ce/es-client-api-c/DeserializeOutputFile.h"
#include "glite/ce/es-client-api-c/WDataStaging.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/WExecutable.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>

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
wrapper::WDataStaging*
xml::DeserializeDataStaging::get( XMLDoc* doc, const int adIndex )
{
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );
  bool clidatapush = false;
  /**
   * First must check that the ApplicationDataStaging tag is there
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging", adIndex );
  if(!XMLGetNodeCount::get( doc, buf ))
    return 0;

  /**
   * Get ClientDataPush tag
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/ClientDataPush", adIndex );
  string* clipush = XMLGetNodeContent::get(doc, buf);
  if(clipush) {
    if(*clipush == "true")
      clidatapush = true;
  }
  delete clipush;

  vector<wrapper::WInputFile> IFs;
  vector<wrapper::WOutputFile> OFs;
  
  DeserializeInputFile::get( doc, IFs, adIndex );
  DeserializeOutputFile::get( doc, OFs, adIndex );

  return new wrapper::WDataStaging( clidatapush, IFs, OFs );
}
