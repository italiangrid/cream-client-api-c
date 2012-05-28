#include "glite/ce/es-client-api-c/RestartActivityCall.h"

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
RestartActivityCall::RestartActivityCall( const string& endpoint, 
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
RestartActivityCall::execute( string& error, enum SOAP_CALL_ERROR_CODES& code)
{
  RestartActivityType req;
  RestartActivityResponseType resp;
  req.ActivityIDField = m_IDs;

  if(SOAP_OK != RESTARTACTIVITYCALL(m_SOAP, 
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
