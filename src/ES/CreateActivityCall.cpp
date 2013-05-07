#include "glite/ce/es-client-api-c/CreateActivityCall.h"
//#include "glite/ce/es-client-api-c/CreateActivityResponse.h"

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
					WCreateActivity* req )
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
CreateActivityCall::execute( string& error )//, enum SOAP_CALL_ERROR_CODES& soap_error_code )
{

//  cout << "CREATEACTIVITYCALL: endpoint=[" << m_endpoint << "]" << endl;
  if(SOAP_OK != CREATEACTIVITYCALL(m_SOAP, 
				   m_endpoint.c_str(), 
				   "http://www.eu-emi.eu/es/2010/12/creation/CreateActivityService/CreateActivityRequest",
				   m_request, 
				   &m_response) ) 
    {
      this->process_error( error );//, soap_error_code );
      return false;
    }

//   char* BUF[m_SOAP->buflen+1];
//   memset((void*)BUF, 0, m_SOAP->buflen+1);
//   memcpy((void*)BUF, &m_SOAP->buf, m_SOAP->buflen);
//
//   

//   string BUF = m_SOAP->buf;
//   cout << endl<<"*** SOAP_BUF=[" << BUF << "]" << endl<<endl;
//  this->save_soap_buffer();
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
CreateActivityCall::getResponse( vector<WActivityCreationResponse>& tgt ) const
{
  //((CreateActivitiesResponse*)&m_response)->getActivityCreationResponse( tgt );
  vector<ActivityCreationResponse*>::const_iterator it = m_response.ActivityCreationResponseField.begin( );
  for( ; it!= m_response.ActivityCreationResponseField.end( ); ++it ) {
    WActivityCreationResponse *act = (WActivityCreationResponse*)*it;
    tgt.push_back( WActivityCreationResponse( *act ) );
  }
}
