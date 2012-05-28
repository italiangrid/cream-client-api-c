#include "glite/ce/es-client-api-c/DeserializeOutputFileTarget.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"
#include "glite/ce/es-client-api-c/Target.h"

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
wrapper::Target*
xml::DeserializeOutputFileTarget::get( XMLDoc* doc, const int adPos, const int ofPos, const int index )
{ 
  
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > classad_safe_ptr( buf );
  string URI;
  string *DID = 0;

  /**
   * Get a index-th Target
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/OutputFile[%d]/Target[%d]/URI", 
	   adPos, ofPos, index );
  string *_uri = XMLGetNodeContent::get( doc, buf );
  if(!_uri) return 0;
  else {
    URI = *_uri;
    delete _uri;
  }

  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/OutputFile[%d]/Target[%d]/DelegationID", 
	   adPos, ofPos, index );
  DID = XMLGetNodeContent::get( doc, buf );
    
  vector<OptionType> options;
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/OutputFile[%d]/Target[%d]/Option", 
	   adPos, ofPos, index );
  int count = XMLGetNodeCount::get( doc, buf );
  
  for(int k = 1; k <= count; ++k ) {
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/DataStaging/OutputFile[%d]/Target[%d]/Option[%d]/Name", 
	     adPos,ofPos,index,k );
    string *name = XMLGetNodeContent::get( doc, buf );
    if(!name) continue;
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/DataStaging/OutputFile[%d]/Target[%d]/Option[%d]/Value", 
	     adPos,ofPos,index,k );
    string *value = XMLGetNodeContent::get( doc, buf );
    if(!value) value = new string("");
    OptionType opt;
    opt.Name = *name;
    opt.Value = *value ;
    options.push_back( opt );
    delete name;
    delete value;
  }
  
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/OutputFile[%d]/Target[%d]/CreationFlag", 
	   adPos, ofPos, index );
  string *CreationFlag = XMLGetNodeContent::get( doc, buf );

  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/OutputFile[%d]/Target[%d]/Mandatory", 
	   adPos, ofPos, index );
  string *Mandatory = XMLGetNodeContent::get( doc, buf );

  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/OutputFile[%d]/Target[%d]/UseIfFailure", 
	   adPos, ofPos, index );
  string *UseIfFailure = XMLGetNodeContent::get( doc, buf );

  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/OutputFile[%d]/Target[%d]/UseIfCancel", 
	   adPos, ofPos, index );
  string *UseIfCancel = XMLGetNodeContent::get( doc, buf );

  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/OutputFile[%d]/Target[%d]/UseIfSuccess", 
	   adPos, ofPos, index );
  string *UseIfSuccess = XMLGetNodeContent::get( doc, buf );

  CreationFlagEnumeration creationFlag = ESADL__CreationFlagEnumeration__overwrite;
  if(CreationFlag)
    creationFlag = (CreationFlagEnumeration)atoi(CreationFlag->c_str());
  

  bool* mandatory = 0;
  if(Mandatory) {
    if((*Mandatory)=="true")
      mandatory = new bool(true);
    else
      mandatory = new bool(false);
  }

  bool useiffail = false;
  if(UseIfFailure)
    if((*UseIfFailure) == "true")
      useiffail = true;

  bool useifcancel = false;
  if(UseIfCancel)
    if((*UseIfCancel) == "true")
      useifcancel = true;
  
  bool useifsuccess = true;
  if(UseIfSuccess) {
    if((*UseIfSuccess) == "true")
      useifsuccess = true;
    else
      useifsuccess = false;
  }

  delete Mandatory;
  delete CreationFlag;
  delete UseIfFailure;
  delete UseIfCancel;
  delete UseIfSuccess;
  
  wrapper::Target *T = new wrapper::Target( URI, 
					    DID, 
					    options, 
					    mandatory, 
					    creationFlag, 
					    useiffail, 
					    useifcancel, 
					    useifsuccess );
  delete DID;
  delete mandatory;
  return T;
}
