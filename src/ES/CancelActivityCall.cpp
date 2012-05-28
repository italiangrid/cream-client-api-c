#include "glite/ce/es-client-api-c/CancelActivityCall.h"

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
CancelActivityCall::CancelActivityCall( const string& endpoint, 
					const vector<string>& ids )
  : ManageActivityCall( endpoint, ids )
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
CancelActivityCall::execute( string& error, enum SOAP_CALL_ERROR_CODES& code)
{
  CancelActivityType         req;
  CancelActivityResponseType resp;
  req.ActivityIDField = m_IDs;

  if(SOAP_OK != CANCELACTIVITYCALL(m_SOAP, 
				   m_endpoint.c_str(), 
				   0, 
				   &req, 
				   &resp) ) 
    {
      this->process_error( error, code );
      return false;
    }

  process_response( resp.ResponseItemField );
  
  return true;
}
