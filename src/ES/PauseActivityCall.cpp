#include "glite/ce/es-client-api-c/PauseActivityCall.h"

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
PauseActivityCall::PauseActivityCall( const string& endpoint, 
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
PauseActivityCall::execute( string& error, enum SOAP_CALL_ERROR_CODES& code)
{
  PauseActivityType req;
  PauseActivityResponseType resp;
  req.ActivityIDField = m_IDs;

  if(SOAP_OK != PAUSEACTIVITYCALL(m_SOAP, 
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
