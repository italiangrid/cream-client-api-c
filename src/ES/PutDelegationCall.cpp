#include "glite/ce/es-client-api-c/PutDelegationCall.h"

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
PutDelegationCall::PutDelegationCall( const string& endpoint,
				      const string& ID,
				      const string& cred )
  : AbstractCall( endpoint )
{

  m_request = new PutDelegationType();
  m_request->DelegationID = ID;
  m_request->Credential = cred;

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
PutDelegationCall::execute( string& error, enum SOAP_CALL_ERROR_CODES& soap_error_code )
{
  if(SOAP_OK != PUTDELEGATIONCALL(m_SOAP, 
				  m_endpoint.c_str(), 
				  0, 
				  m_request, 
				  m_response) ) 
    {
      this->process_error( error, soap_error_code );
      return false;
    }
  return true;
}

