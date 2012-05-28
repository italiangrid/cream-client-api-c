#include "glite/ce/es-client-api-c/CreateActivityCall.h"
#include "glite/ce/es-client-api-c/CreateActivitiesResponse.h"

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
CreateActivityCall::CreateActivityCall( const string& endpoint,
					CreateActivities* req )
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
CreateActivityCall::execute( string& error, enum SOAP_CALL_ERROR_CODES& soap_error_code )
{

//  cout << "CREATEACTIVITYCALL: endpoint=[" << m_endpoint << "]" << endl;
  if(SOAP_OK != CREATEACTIVITYCALL(m_SOAP, 
				   m_endpoint.c_str(), 
				   "http://www.eu-emi.eu/es/2010/12/creation/CreateActivityService/CreateActivityRequest",
				   m_request, 
				   &m_response) ) 
    {
      this->process_error( error, soap_error_code );
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
CreateActivityCall::getResponse( vector<ActivityCreationResponse>& tgt ) const
{
  ((CreateActivitiesResponse*)&m_response)->getActivityCreationResponse( tgt );
}
