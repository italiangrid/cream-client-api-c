#include "glite/ce/es-client-api-c/DeserializeResourcesSlotRequirement.h"

#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"
#include "glite/ce/es-client-api-c/SlotRequirement.h"

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
wrapper::SlotRequirement*
xml::DeserializeResourcesSlotRequirement::get( XMLDoc* doc,
					       const int adIndex )
{
  SlotsPerHostType* sl = 0;
  bool *excl = 0;
  string *use = 0;
  wrapper::SlotRequirement *SL = 0;
  
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );
  
  /**
   *
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Resources[1]/SlotRequirement", adIndex );
  if( !XMLGetNodeCount::get( doc, buf ) ) 
    return 0;
   
    /**
     * Get NumberOfSlots tag
     */
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Resources[1]/SlotRequirement[1]/NumberOfSlots", adIndex );
    string* NumberOfSlots = XMLGetNodeContent::get( doc, buf );
    if(!NumberOfSlots) return 0;
    boost::scoped_ptr< string > numofslots_safe_ptr( NumberOfSlots );
    
    /**
     * Get ExclusiveExecution tag
     */
     
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Resources[1]/SlotRequirement[1]/ExclusiveExecution", adIndex );
    string* ExclusiveExecution = XMLGetNodeContent::get( doc, buf );
    boost::scoped_ptr< string > excl_safe_ptr( ExclusiveExecution );
    if(ExclusiveExecution) {
      if((*ExclusiveExecution)=="true")
        excl = new bool(true);
      else
        excl = new bool(false);
      
    }
    boost::scoped_ptr< bool > exclbool_safe_ptr( excl );
    
    /**
     * Get SlotsPerHost tag
     */    
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/Resources[1]/SlotRequirement[1]/SlotsPerHost", adIndex);
    string *number = XMLGetNodeContent::get( doc, buf );
    boost::scoped_ptr< string > num_safe_ptr( number );    
    if( number ) 
    {
      memset( (void*)buf, 0, 1024 );
      sprintf( buf, "//ActivityDescription[%d]/Resources[1]/SlotRequirement[1]/SlotsPerHost/@useNumberOfSlots", adIndex);
      use = XMLGetNodeContent::get( doc, buf );
      
    }
    boost::scoped_ptr< string > use_safe_ptr( use );
    
    
    if(number)
    {
      sl = new SlotsPerHostType();
      sl->__item = atoll(number->c_str());
      if(use)
        sl->useNumberOfSlots = ((*use)=="true") ? true : false;

    }
    
    SL = new wrapper::SlotRequirement( atoll(NumberOfSlots->c_str() ), sl, excl );
    delete sl;
    return SL;
}
