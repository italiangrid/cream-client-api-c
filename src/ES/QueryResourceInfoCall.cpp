#include "glite/ce/es-client-api-c/QueryResourceInfoCall.h" 
#include "glite/ce/es-client-api-c/typedefs.h"

using namespace std;
using namespace emi_es::client::comm;
using namespace emi_es::client::wrapper;

void traverse_dom_element( const soap_dom_element& );
void traverse_dom_element_childs( const soap_dom_element& );
void traverse_dom_attribute( const soap_dom_attribute& );

/**
 *
 *
 *
 *
 *
 *
 *
 */
QueryResourceInfoCall::QueryResourceInfoCall( const string& endpoint,
					      const string& dialect,
					      const string& query )
  : AbstractCall( endpoint ), m_dialect(dialect), m_query(query)
{
}

/**
 *
 *
 *
 *
 *
 *
 *
 */
bool
QueryResourceInfoCall::execute( string& error, 
				enum SOAP_CALL_ERROR_CODES& code )
{
  _ESRESOURCEINFOTYPES__QueryResourceInfo req;
  req.QueryDialect = m_dialect;
  req.QueryExpression = m_query;

  QUERYRESOURCEINFORESPONSE resp;

  if(SOAP_OK != QUERYRESOURCEINFOCALL(m_SOAP, 
				      m_endpoint.c_str(), 
				      0, 
				      &req, 
				      &resp) ) 
    {
      this->process_error( error, code );
      return false;
    }
  
  vector<_ESRESOURCEINFOTYPES__QueryResourceInfoItem*>::const_iterator it = resp.ESRESOURCEINFOTYPES__QueryResourceInfoItem.begin();
  int i = 0;
  for( ; it != resp.ESRESOURCEINFOTYPES__QueryResourceInfoItem.end( ); ++it ) {

    //cout << endl << "****** QueryResourceInfoItem.__any #" << i <<endl;
    traverse_dom_element( (*it)->__any );
  
    //cout << endl << "****** QueryResourceInfoItem.__any.elts #" << i <<endl;
    traverse_dom_element_childs( *((*it)->__any.elts) );

    //cout << endl << "****** QueryResourceInfoItem.__anyAttribute #" << i++ <<endl;
    traverse_dom_attribute( (*it)->__anyAttribute );
    
  }
  
  return true;
}

/**
 *
 *
 *
 *
 *
 */
void traverse_dom_element( const soap_dom_element& _dom_) {
  const soap_dom_element* cursor = &_dom_;
  while( cursor ) {
    if(cursor->name && cursor->data) {
      printf("%s=%s\n", cursor->name, cursor->data);
    }
    cursor = cursor->next;
  }
}

/**
 *
 *
 *
 *
 *
 */
void traverse_dom_element_childs( const soap_dom_element& _dom_) {
  const soap_dom_element* cursor = &_dom_;
  while( cursor ) {
    if(cursor->name && cursor->wide) {
      printf("%s=%s\n", cursor->name, soap_wchar2s(_dom_.soap, cursor->wide));
    }
    cursor = cursor->next;
  }
}

/**
 *
 *
 *
 *
 *
 */
void traverse_dom_attribute( const soap_dom_attribute& _attr_) {
  const soap_dom_attribute* cursor = &_attr_;
  while( cursor ) {
    if(cursor->name && cursor->data) {
      printf("%s=%s\n", cursor->name, cursor->data);
    }
    cursor = cursor->next;
  }
}
