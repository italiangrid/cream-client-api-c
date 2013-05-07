#include "glite/ce/es-client-api-c/DeserializeInputFileSource.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"
#include "glite/ce/es-client-api-c/WSource.h"

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
wrapper::WSource*
xml::DeserializeInputFileSource::get( XMLDoc* doc, const int adPos, const int ifPos, const int index )
{ 
  
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > classad_safe_ptr( buf );
  string URI, *_uri;
  string *DID = 0;
  /**
   * Get a index-th Source
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/InputFile[%d]/Source[%d]/URI", adPos, ifPos, index );
  _uri = XMLGetNodeContent::get( doc, buf );
  if(!_uri) return 0;
  else {
    URI = *_uri;
    delete _uri;
  }

  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/InputFile[%d]/Source[%d]/DelegationID", adPos, ifPos, index );
  DID = XMLGetNodeContent::get( doc, buf );
    
  vector<OptionType> options;
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/InputFile[%d]/Source[%d]/Option", adPos, ifPos, index );
  int count = XMLGetNodeCount::get( doc, buf );
  
  for(int k = 1; k <= count; ++k ) {
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/DataStaging/InputFile[%d]/Source[%d]/Option[%d]/Name", adPos,ifPos,index,k );
    string *name = XMLGetNodeContent::get( doc, buf );
    if(!name) continue;
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/DataStaging/InputFile[%d]/Source[%d]/Option[%d]/Value", adPos,ifPos,index,k );
    string *value = XMLGetNodeContent::get( doc, buf );
    if(!value) value = new string("");
    OptionType opt;
    opt.Name = *name;
    opt.Value = *value ;
    options.push_back( opt );
    delete name;
    delete value;
  }

  wrapper::WSource *SRC;
  SRC = new wrapper::WSource(URI, DID, options);
  delete DID;
  return SRC;
}
