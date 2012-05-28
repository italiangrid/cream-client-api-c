#include "glite/ce/es-client-api-c/ListActivityCall.h"
#include "glite/ce/es-client-api-c/ListActivities.h"

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
ListActivityCall::ListActivityCall( const string& endpoint, 
				    ListActivities* req )
  : AbstractCall( endpoint ), m_request( req )
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
ListActivityCall::execute( string& error, enum SOAP_CALL_ERROR_CODES& code)
{
  if(SOAP_OK != LISTACTIVITIESCALL(m_SOAP, 
				 m_endpoint.c_str(), 
				 0, 
				 m_request, 
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
ListActivityCall::getResponse( bool& truncated, std::vector<std::string>& target ) const
{
  truncated = m_response.truncated;
  target    = m_response.ActivityIDField;
}
