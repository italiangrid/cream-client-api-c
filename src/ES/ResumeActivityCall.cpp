#include "glite/ce/es-client-api-c/ResumeActivityCall.h"

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
ResumeActivityCall::ResumeActivityCall( const string& endpoint, 
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
ResumeActivityCall::execute( string& error, enum SOAP_CALL_ERROR_CODES& code)
{
  ResumeActivityType req;
  ResumeActivityResponseType resp;
  req.ActivityIDField = m_IDs;
  
  if(SOAP_OK != RESUMEACTIVITYCALL(m_SOAP, 
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
