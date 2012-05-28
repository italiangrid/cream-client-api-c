#include "glite/ce/es-client-api-c/NotifyServiceCall.h"

using namespace std;
using namespace emi_es::client::comm;
using namespace emi_es::client::wrapper;

/**
 *
 *
 *
 *
 *
 *
 *
 */
NotifyServiceCall::NotifyServiceCall(const string& endpoint,
				     const vector< pair<string, AbstractCall::NOTIFYMESSAGE> >& attrs)
  : AbstractCall( endpoint ), m_request( attrs )
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
NotifyServiceCall::execute( std::string& error, enum SOAP_CALL_ERROR_CODES& code )
{
  NotifyServiceType request;
  NotifyServiceResponseType response;
  {
    vector<pair<string, AbstractCall::NOTIFYMESSAGE> >::const_iterator it = m_request.begin();
    for( ; it != m_request.end( ); ++it )
      {
	NotifyRequestItemType* nreq = new NotifyRequestItemType( );
	nreq->ActivityIDField = it->first;
	nreq->NotifyMessage              = (NotifyMessageType)it->second;
	request.NotifyRequestItemField.push_back( nreq );
      }
  }
  
  if(SOAP_OK != NOTIFYSERVICECALL(m_SOAP, 
				  m_endpoint.c_str(), 
				  0, 
				  &request, 
				  &response) ) 
    {
      this->process_error( error, code );
      return false;
    }

  
  vector<NotifyResponseItemType*>::const_iterator it;
  it = response.NotifyResponseItemField.begin();
  for( ; it != response.NotifyResponseItemField.end( ); ++it )
    {
      if((*it)->InternalBaseFaultField) {
	InternalBaseFault ibf( *((InternalBaseFault*)(*it)->InternalBaseFaultField) );
	m_response.push_back( make_pair( (*it)->ActivityIDField, ibf ));
      }
    }
  
  vector<NotifyRequestItemType*>::iterator iit;
  iit = request.NotifyRequestItemField.begin();
  for( ; iit != request.NotifyRequestItemField.end( ); ++iit )
    delete *iit;
  request.NotifyRequestItemField.clear();

  return true;
}
