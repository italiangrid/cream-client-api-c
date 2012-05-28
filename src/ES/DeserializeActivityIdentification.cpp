#include "glite/ce/es-client-api-c/DeserializeActivityIdentification.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"

#include "glite/ce/es-client-api-c/ActivityIdentification.h"

#include <vector>

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
wrapper::ActivityIdentification*
xml::DeserializeActivityIdentification::get( XMLDoc* doc, const int adIndex )
{
  string *Name = 0, *Description = 0, *Type = 0;
  vector<string> Annotation;
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );

  /**
   * Check for <ActivityIdentification> tag
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/ActivityIdentification", adIndex );
  if(!XMLGetNodeCount::get( doc, buf ))
    return 0;
  
  /**
   * check for Name
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/ActivityIdentification/Name", adIndex );
  Name = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > name_safe_ptr( Name );

  /**
   * check for Description
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/ActivityIdentification/Description", adIndex );
  Description = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > desc_safe_ptr( Description );

  /**
   * check for Type
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/ActivityIdentification/Type", adIndex );
  Type = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > type_safe_ptr( Type );

  /**
   * check for Annotation(s)
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/ActivityIdentification/Annotation", adIndex );
  XMLGetMultipleNodeContent::get( doc, Annotation, buf );

  wrapper::ActivityIdentification::ACTIVITYTYPE _type;
  if(Type) {
    if(*Type == "collectionelement" )
      _type = wrapper::ActivityIdentification::ACTIVITYTYPE_COLLECTIONELEMENT;
    
    if(*Type == "parallelelement" )
      _type = wrapper::ActivityIdentification::ACTIVITYTYPE_PARALLELELEMENT;
    
    if(*Type == "single" )
      _type = wrapper::ActivityIdentification::ACTIVITYTYPE_SINGLE;
    
    if(*Type == "workflownode" )
      _type = wrapper::ActivityIdentification::ACTIVITYTYPE_WORKFLOWNODE;
  }
  
  return new wrapper::ActivityIdentification( (Name? *Name : ""), 
					      (Description ? *Description : ""), 
					      _type, 
					      Annotation );
}
