#include "glite/ce/es-client-api-c/GetActivityStatusCall.h"

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
GetActivityStatusCall::GetActivityStatusCall( const string& endpoint,
					      const vector<string>& ids )
  : AbstractCall( endpoint )
{
  m_request.ActivityIDField = ids;
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
GetActivityStatusCall::execute( string& error, enum SOAP_CALL_ERROR_CODES& code)
{
  if(SOAP_OK != GETACTIVITYSTATUSCALL(m_SOAP, 
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
