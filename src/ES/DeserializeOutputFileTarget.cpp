#include "glite/ce/es-client-api-c/DeserializeOutputFileTarget.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"
#include "glite/ce/es-client-api-c/WTarget.h"

#include <boost/scoped_ptr.hpp>
#include <boost/algorithm/string.hpp>

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
wrapper::WTarget*
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

  CreationFlagEnumeration *creationFlag = 0;
  if(CreationFlag) {
    creationFlag = new CreationFlagEnumeration( );
    if(boost::iequals(*CreationFlag, "OVERWRITE"));
      *creationFlag = CreationFlagEnumeration__overwrite;
    if(boost::iequals(*CreationFlag, "APPEND"));
      *creationFlag = CreationFlagEnumeration__append;
    if(boost::iequals(*CreationFlag, "DONTOVERWRITE"));
      *creationFlag = CreationFlagEnumeration__dontOverwrite;  
  }

  bool *useiffail = 0;
  if(UseIfFailure) {
    useiffail = new bool;
    if(boost::iequals(*UseIfFailure, "true"))
      *useiffail = true;
    else
      *useiffail = false;
  }
  
  bool *useifcancel = 0;
  if(UseIfCancel) {
    useifcancel = new bool;
    if(boost::iequals(*UseIfCancel, "true"))
      *useifcancel = true;
    else
      *useifcancel = false;
  }
  
  bool *useifsuccess = 0;
  if(UseIfSuccess) {
    useifsuccess = new bool;
    if(boost::iequals(*UseIfSuccess, "true"))
      *useifsuccess = true;
    else
      *useifsuccess = false;
  }

  bool* mandatory = 0;
  if(Mandatory)
    {
      mandatory = new bool;
      if(boost::iequals(*Mandatory, "true"))
        *mandatory = true;
      else
        *mandatory = false;
    }

  delete Mandatory;
  delete CreationFlag;
  delete UseIfFailure;
  delete UseIfCancel;
  delete UseIfSuccess;
  
  wrapper::WTarget *T = new wrapper::WTarget( URI, 
					      DID, 
					      options, 
					      mandatory, 
					      creationFlag, 
					      useiffail, 
					      useifcancel, 
					      useifsuccess );
  delete DID;
  delete useiffail,
  delete useifcancel;
  delete useifsuccess;
  delete mandatory;
  return T;
}
