#include "glite/ce/es-client-api-c/DeserializeApplicationEnvironment.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"

#include <boost/scoped_ptr.hpp>

using namespace std;
namespace xml = emi_es::client::xml;
//namespace wrapper = emi_es::client::wrapper;


/**
 *
 *
 *
 *
 *
 *
 */
void
xml::DeserializeApplicationEnvironment::get( XMLDoc* doc, vector<OptionType>& target, const int adIndex )
{

  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );

  /**
   * check for num of Environment tags
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/Environment", adIndex );
  int envCount = XMLGetNodeCount::get( doc, buf );
  if(!envCount) {
    return;
  }

  /**
   * Load all Environments tags
   */
  for( int k = 1; k <= envCount; ++k ) {

    string *Name=0, *Value=0;
    
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/Environment[%d]/Name", adIndex, k );
    Name = XMLGetNodeContent::get( doc, buf );
    if(!Name) continue;
    boost::scoped_ptr< string > name_safe_ptr( Name );
    
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Application[1]/Environment[%d]/Value", adIndex, k );
    Value = XMLGetNodeContent::get( doc, buf );
    if(!Value) Value = new string("");
    boost::scoped_ptr< string > value_safe_ptr( Value );

    OptionType opt;
    opt.Name = *Name;
    opt.Value = *Value;
    target.push_back( opt );
  }
}
