#include "glite/ce/es-client-api-c/GetResourceInfoCall.h"

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
GetResourceInfoCall::GetResourceInfoCall( const string& endpoint )
  : AbstractCall( endpoint )
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
GetResourceInfoCall::execute( string& error, enum SOAP_CALL_ERROR_CODES& code)
{
  _ESRESOURCEINFOTYPES__GetResourceInfo req;
  _ESRESOURCEINFOTYPES__GetResourceInfoResponse resp;

  if(SOAP_OK != GETRESOURCEINFOCALL(m_SOAP, 
				    m_endpoint.c_str(), 
				    0, 
				    &req, 
				    &resp) ) 
    {
      this->process_error( error, code );
      return false;
    }
  this->save_soap_buffer( );
  return true;
}
