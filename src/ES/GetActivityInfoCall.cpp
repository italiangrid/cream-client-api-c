#include "glite/ce/es-client-api-c/GetActivityInfoCall.h"

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
GetActivityInfoCall::GetActivityInfoCall( const string& endpoint,
					  const vector<string>& ids,
					  const vector<string>& attrs)
  : AbstractCall( endpoint )
{
  m_request.ActivityIDField = ids;
  m_request.AttributeName = attrs;
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
GetActivityInfoCall::execute( string& error, enum SOAP_CALL_ERROR_CODES& code)
{
  if(SOAP_OK != GETACTIVITYINFOCALL(m_SOAP, 
				    m_endpoint.c_str(), 
				    0, 
				    &m_request, 
				    &m_response) ) 
    {
      this->process_error( error, code );
      return false;
    }
  return true;
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
void
GetActivityInfoCall::getResponse( map<string, ComputingActivity>& good, 
				  map<string, InternalBaseFault>& bad) const
{
  vector<ActivityInfoItemType*>::const_iterator it = m_response.ActivityInfoItemField.begin();
  for( ; it != m_response.ActivityInfoItemField.end( ); ++it )
    {
      if( (*it)->__union_ActivityInfoItem == Union_ActivityInfoItem_ActivityInfo_Number) {
	ComputingActivity tmp = *((ComputingActivity*)(*it)->union_ActivityInfoItem.ActivityInfoField);
	good.insert( make_pair( (*it)->ActivityIDField, tmp ) );
	continue;
      }
      
      if( (*it)->__union_ActivityInfoItem == Union_ActivityInfoItem_InternalBaseFault_Number) {
	InternalBaseFault ibf = *((InternalBaseFault*)(*it)->union_ActivityInfoItem.InternalBaseFaultField);
	bad.insert( make_pair((*it)->ActivityIDField, ibf) );
	continue;
      }
    }
}
