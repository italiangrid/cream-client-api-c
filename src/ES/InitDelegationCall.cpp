#include "glite/ce/es-client-api-c/InitDelegationCall.h"
#include "glite/ce/es-client-api-c/InitDelegation.h"

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
InitDelegationCall::InitDelegationCall( const string& endpoint,
					InitDelegation* req )
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
InitDelegationCall::execute( string& error, enum SOAP_CALL_ERROR_CODES& soap_error_code )
{
  if(SOAP_OK != INITDELEGATIONCALL(m_SOAP, 
				   m_endpoint.c_str(), 
				   0, 
				   m_request, 
				   &m_response) ) 
    {
      this->process_error( error, soap_error_code );
      return false;
    }
  return true;
}

