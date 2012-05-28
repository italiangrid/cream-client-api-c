#include "glite/ce/es-client-api-c/GetDelegationInfoCall.h"

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
GetDelegationInfoCall::GetDelegationInfoCall( const string& endpoint,
					      const string& ID)
  : AbstractCall( endpoint )
{
  
  //m_request = new _ES_USCOREDELEGATION__GetDelegationInfo();
  m_request.DelegationID = ID;

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
GetDelegationInfoCall::execute( string& error, enum SOAP_CALL_ERROR_CODES& soap_error_code )
{
  if(SOAP_OK != GETDELEGATIONINFOCALL(m_SOAP, 
				      m_endpoint.c_str(), 
				      0, 
				      &m_request, 
				      &m_response) ) 
    {
      this->process_error( error, soap_error_code );
      return false;
    }
  return true;
}

