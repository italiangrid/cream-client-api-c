#include "glite/ce/es-client-api-c/DeserializeActivityIdentification.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"

#include "glite/ce/es-client-api-c/WActivityIdentification.h"

#include <vector>

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
wrapper::WActivityIdentification*
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

  ActivityTypeEnumeration *_type = 0;
  if(Type) {
    _type = new ActivityTypeEnumeration();
    *_type = (ActivityTypeEnumeration)UNKNOWN;
    if( boost::iequals(*Type, "collectionelement") )
      *_type = ACTIVITYTYPE_COLLECTIONELEMENT;
    
    if( boost::iequals(*Type, "parallelelement") )
      *_type = ACTIVITYTYPE_PARALLELELEMENT;
    
    if( boost::iequals(*Type, "single") )
      *_type = ACTIVITYTYPE_SINGLE;
    
    if( boost::iequals(*Type, "workflownode") )
      *_type = ACTIVITYTYPE_WORKFLOWNODE;
  }
  
  wrapper::WActivityIdentification* ai 
       = new wrapper::WActivityIdentification( Name, 
					       Description, 
					       _type, 
					       Annotation );
  delete _type;
  return ai;
					       
}
