#include "glite/ce/es-client-api-c/AbstractCall.h"
#include "glite/ce/es-client-api-c/CreateActivityCall.h"
#include "glite/ce/es-client-api-c/WInternalBaseFault.h"

#include <stdsoap2.h>
#include "autogen/ES_CLIENT.nsmap"

#include <boost/lexical_cast.hpp>

#include <cstring>

using namespace std;

namespace comm = emi_es::client::comm;
namespace wrapper = emi_es::client::wrapper;

char* comm::AbstractCall::s_global_buf = 0;//("");

//extern "C" {
  //extern static size_t glite_gsplugin_recv(struct soap*, char*, size_t );
// #undef IOV_MAX
// #include "glite/security/glite_gsplugin.h"
// //#include "glite/security/glite_gsplugin-int.h"
// //#include "glite/security/glite_gsplugin.h"
//};
/*
size_t
pre_gsplugin_recv(struct soap *S, char *B, size_t bufsz) {
  //int bufsz = 0;
  //memset((void*)B, 0, bufsz);
  size_t len = glite_gsplugin_recv( S, B, bufsz );
  cout << endl << "SOAP->BUF=[" << S->buf << "]" <<endl<<endl;
  if(comm::AbstractCall::s_global_buf!=0)
    free(comm::AbstractCall::s_global_buf);
  comm::AbstractCall::s_global_buf = (char*)malloc(len+1);
  memset((void*)comm::AbstractCall::s_global_buf, 0, len+1);
  memcpy((void*)comm::AbstractCall::s_global_buf, B, len);
//  comm::AbstractCall::s_global_buf = string(_B);
  return len;
}
*/
/*
 *
 *
 *
 *
 *
 *
 *
 */
void
get_string_error( string& error, wrapper::WInternalBaseFault* );

/**
 *
 *
 *
 *
 *
 *
 *
 */
comm::AbstractCall::AbstractCall( const string& endpoint )
  : m_gsoap_plugin_context( 0 ),
    m_soap_timeout( 30 ),
    m_SOAP(0),
    m_endpoint(endpoint)
{
}

/*
 *
 *
 *
 *
 *
 *
 *
 */
bool
comm::AbstractCall::init_credentials( const string& cert,
				      const string& key,
				      string& error ) 
{
  if(!m_SOAP) {
    error = "SOAP runtime environment not initialized; init_soap must be called first";
    return false;
  }

  if(cert.empty() && key.empty() ) {
    m_SOAP->send_timeout = m_soap_timeout;
    m_SOAP->recv_timeout = m_soap_timeout;
    return true;
  }

  m_certificate_file = cert;
  if(key.empty())
    m_key_file = cert;
  else
    m_key_file = key;

  int retcode = 0;

  if(::getenv("NOAUTH"))
    return true;
  
  retcode = ::glite_gsplugin_init_context( &m_gsoap_plugin_context );
  if( retcode ) 
    {
      m_gsoap_plugin_context = 0;
      error = string("glite_gsplugin_init_context has failed initialization: ") 
	+ strerror( retcode );
      return false;
    }

  if( soap_register_plugin_arg(m_SOAP, glite_gsplugin, m_gsoap_plugin_context) ) {
    error = "Can't register gsoap plugin";
    return false;
  }

  if (glite_gsplugin_set_credential( m_gsoap_plugin_context, 
				     m_certificate_file.c_str(), 
				     m_key_file.c_str() )) 
    {
      error = string("glite_gsplugin_set_credential has failed: ") + glite_gsplugin_errdesc(m_SOAP);
      glite_gsplugin_free_context( m_gsoap_plugin_context );
      m_gsoap_plugin_context = 0;
      return false;
    }

  struct timeval T;
  T.tv_sec = (time_t)m_soap_timeout;
  T.tv_usec = 0;
  
  glite_gsplugin_set_timeout( m_gsoap_plugin_context, &T );

//   char *B;
//   glite_gsplugin_recv( m_SOAP, B, 0 );

  //m_SOAP->frecv = pre_gsplugin_recv;

  return true;
}

/*
 *
 *
 *
 *
 *
 *
 *
 */
bool
comm::AbstractCall::init_soap( string& error ) 
{
  m_SOAP = soap_new( );
  if(!m_SOAP) {
    error = "soap_new failed to allocate memory for SOAP runtime environment";
    return false;
  }
  
  m_SOAP->header = NULL;
    
  m_SOAP->socket_flags = MSG_NOSIGNAL; // this setting will NOT generate a sigpipe

  soap_set_namespaces(m_SOAP, ES_CLIENT_namespaces /*namespaces*/);
  return true;
}

/*
 *
 *
 *
 *
 *
 *
 *
 */
bool
comm::AbstractCall::init( const string& cert,
			  const string& key,
			  string& error )
{
  bool ok;
  ok = this->init_soap( error );
  if(!ok) return false;
  
  ok = this->init_credentials( cert, key, error );
  if(!ok) return false;
  
  return true;
}

/*
 *
 *
 *
 *
 *
 *
 *
 */
comm::AbstractCall::~AbstractCall( ) throw()
{
  if(m_SOAP) {
    soap_destroy(m_SOAP);
    soap_end(m_SOAP);
    soap_done(m_SOAP);
    
    if(m_gsoap_plugin_context) {
      glite_gsplugin_free_context( m_gsoap_plugin_context );
      m_gsoap_plugin_context = 0;
    }
    free( m_SOAP );
    m_SOAP = 0;
  }
  if(s_global_buf!=0)
    free(s_global_buf);
}

/*
 *
 *
 *
 *
 *
 *
 *
 */
void
comm::AbstractCall::process_error( string& error )//, enum comm::AbstractCall::SOAP_CALL_ERROR_CODES& code )
{
  int soaperr = m_SOAP->error;

  /**
   *
   * There're 2 types of timeout:
   * One generate a m_SOAP->error = 28 (SOAP_TCP_ERROR) and the faultstring/faultdetails
   * description about tcp_connect that timed out. This usually occurs when at server
   * side there is a machine that has the network off
   * Another one is when the service responded to the connection (soap_accept ok) but
   * the service is slow to send back the response to the client (e.g. overload of 
   * the service).
   * The second one is handled by the following piece of code (SOAP_EOF), the first one
   * is handled by the subsequent code.
   *
   */
  if(soaperr == SOAP_EOF) {
    error = "SOAP connection timeout or peer closed socket connection prematurely";
    //code = SOAP_CALL_ERROR_TIMEOUT;
    return;
  }

  soap_set_fault( m_SOAP );

  //cout << "m_SOAP->error=" << soaperr << endl;
  
  /**
   *
   * In this case no actual soap fault has been generated by the service's logic. 
   * Some other kind of error occurred (like a wrong TCP port number tried, or
   * a non-existing hostname had been contacted).
   *
   */
  if( (soaperr != SOAP_FAULT) && (soaperr != SOAP_CLI_FAULT) && (soaperr != SOAP_SVR_FAULT ) )
    {
      error = string("Connection error to endpoint [") + m_endpoint + "]: ";
      char **faultstring =  (char**)soap_faultstring(m_SOAP);
      char **faultcode = (char**)soap_faultcode(m_SOAP);
      char **faultsubcode = (char**)soap_faultsubcode(m_SOAP);
      char **faultdetail = (char**)soap_faultdetail(m_SOAP);
      
      if (*faultstring)
        error += string(" FaultString=[")+*faultstring+"]";
      else
	error += " FaultString=[]";
      
      if (*faultcode)
        error += string(" FaultCode=[")+*faultcode+"]";
      else
	error += " FaultCode=[]";
      
      if (*faultsubcode)
        error += string(" FaultSubCode=[")+*faultsubcode+"]";
      else
	error += " FaultSubCode=[]";
      
       if (*faultdetail)
         error += string(" FaultDetail=[")+*faultdetail+"]";
       else
	 error += " FaultDetail=[]";

      //code  = SOAP_CALL_ERROR_CONNECT;
      return;
    }


  /**
   *
   * In this case an actual fault (filled with information generated by the service's logic)
   * has been received, and must be parsed by the client.
   *
   */
  int type=-1;
  void* fault=0;

  if (m_SOAP->version == 2) {
    if(m_SOAP->fault && m_SOAP->fault->SOAP_ENV__Detail) {
      fault = m_SOAP->fault->SOAP_ENV__Detail->fault;
      type = m_SOAP->fault->SOAP_ENV__Detail->__type;
    }
  }
  else {
    if(m_SOAP->fault)
      if(m_SOAP->fault->detail) {
        fault = m_SOAP->fault->detail->fault;
        type = m_SOAP->fault->detail->__type;
	//cout << "\n\n__type=" << m_SOAP->fault->detail->__type << endl;
      }
  }
  
  /**
   * In this case the service wanted to send back a fault to the client
   * (return SOAP_CLI_FAULT/SOAP_FAULT/SOAP_SVR_FAULT) but it actualy didn't set anything
   * in the SOAP->fault structure that has been left to NULL
   *
   */
  if(!fault) {

    if(check_sub_fault(m_SOAP, error)) {
      return;
    }

    error = string("Received NULL fault; the error is due to another cause: ");
    char **faultstring =  (char**)soap_faultstring(m_SOAP);
    char **faultcode = (char**)soap_faultcode(m_SOAP);
    char **faultsubcode = (char**)soap_faultsubcode(m_SOAP);
    char **faultdetail = (char**)soap_faultdetail(m_SOAP);

    if (*faultstring)
      error += string(" FaultString=[")+*faultstring+"]";
    else
      error += " FaultString=[]";

    if (*faultcode)
      error += string(" FaultCode=[")+*faultcode+"]";
    else
      error += " FaultCode=[]";

    if (*faultsubcode)
      error += string(" FaultSubCode=[")+*faultsubcode+"]";
    else
      error += " FaultSubCode=[]";

    if (*faultdetail)
      error += string(" FaultDetail=[")+*faultdetail+"]";
    else
      error += " FaultDetail=[]";

    //code = SOAP_CALL_ERROR_UNKNOWNFAULT;
    return;
  }

  /**
   *
   * The service returned a correct FAULT SOAP code and did set the SOAP->fault structure
   * too, that can be matched against all the faults defined in the stubs
   *
   */
  

  if( type == VECTORLIMITEXCEEDED ) {
    //code = SOAP_CALL_ERROR_VECTORLIMITEXCEEDED;
    get_string_error( error, (InternalBaseFault*)fault );
    error += string(" ServerLimit=[") 
      + boost::lexical_cast<string>(((VectorLimitExceededFault*)fault)->ServerLimit) 
      + "]";
    return;
  }
  if(type==INTERNALBASE) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (InternalBaseFault*)fault );
    return;
  }
  if(type==UNSUPPORTEDCAPABILITY) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (UnsupportedCapabilityFault*)fault );
    return;
  }
  if(type==INVALIDACTIVITYDESCRIPTIONSEMANTIC) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (InvalidActivityDescriptionSemanticFault*)fault );
    return;
  }
  if(type==INVALIDACTIVITYDESCRIPTION) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (InvalidActivityDescriptionFault*)fault );
    return;
  }
//   if(type==VECTORLIMITEXCEEDED) {
//     //code = (SOAP_CALL_ERROR_CODES)type;
//     get_string_error( error, (VectorLimitExceededFaultType*)fault );
//     return;
//   }
  if(type==ACCESSCONTROL) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (AccessControlFault*)fault );
    return;
  }
  if(type==INVALIDACTIVITYID) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (InvalidActivityIDFault*)fault );
    return;
  }
  if(type==UNKNOWNACTIVITYID) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (UnknownActivityIDFault*)fault );
    return;
  }
  if(type==UNABLETORETRIEVESTATUS) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (UnableToRetrieveStatusFault*)fault );
    return;
  }
//   if(type==UNKNOWNGLUE2ACTIVITYATTR) {
//     //code = (SOAP_CALL_ERROR_CODES)type;
//     get_string_error( error, (UnknownGlue2ActivityAttributeFault*)fault );
//     return;
//   }
  if(type==OPERATIONNOTALLOWED) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (OperationNotAllowedFault*)fault );
    return;
  }
  if(type==ACTIVITYNOTFOUND) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (ActivityNotFoundFault*)fault );
    return;
  }
  if(type==INTERNALNOTIFICATION) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (InternalNotificationFault*)fault );
    return;
  }
  if(type==OPERATIONNOTPOSSIBLE) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (OperationNotPossibleFault*)fault );
    return;
  }
  if(type==INVALIDACTIVITYSTATE) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (InvalidActivityStateFault*)fault );
    return;
  }
  if(type==ACTIVITYNOTINTERMINALSTATE) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (ActivityNotInTerminalStateFault*)fault );
    return;
  }
  if(type==INVALIDACTIVITYLIMIT) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (InvalidActivityLimitFault*)fault );
    return;
  }
  if(type==INVALIDPARAMETER) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (InvalidParameterFault*)fault );
    return;
  }
  if(type==UNKNOWNDELEGATION) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (UnknownDelegationIDFault*)fault );
    return;
  }
  if(type==INTERNALSERVICEDELEGATION) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (InternalServiceDelegationFault*)fault );
    return;
  }
  if(type==NOTSUPPORTEDQUERYDIALECT) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (NotSupportedQueryDialectFault*)fault );
    return;
  }
  if(type==NOTVALIDQUERYSTATEMENT) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (NotValidQueryStatementFault*)fault );
    return;
  }
  if(type==UNKNOWNQUERY) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (UnknownQueryFault*)fault );
    return;
  }
  if(type==INTERNALRESOURCEINFO) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (InternalResourceInfoFault*)fault );
    return;
  }
  if(type==RESOURCEINFONOTFOUND) {
    //code = (SOAP_CALL_ERROR_CODES)type;
    get_string_error( error, (ResourceInfoNotFoundFault*)fault );
    return;
  }
  
  //code = SOAP_CALL_ERROR_UNKNOWNTYPE;
  
  char *pluginerr = glite_gsplugin_errdesc(m_SOAP);
  
  if(pluginerr)
    error = string("The fault is unknown or due to another cause; gsoap-plugin error: ") 
      + pluginerr;
  else
    error = string("Unknown failure cause...");
}

/*
 *
 *
 *
 *
 *
 *
 *
 */
void
comm::AbstractCall::get_string_error( string& error, InternalBaseFault* fault )
{
  if(!fault)
    return;

  error = string(" Message=[") + fault->Message + "]";
  if(fault->Timestamp)
    error += string(" Timestamp=[") + boost::lexical_cast<string>(*fault->Timestamp) + "]";
  if(fault->Description)
    error += string(" Description=[") + *fault->Description + "]";
  if(fault->FailureCode)
    error += string(" FailureCode=[") + boost::lexical_cast<string>(*fault->FailureCode) + "]";
}

/*
 *
 *
 *
 *
 *
 *
 *
 */
void
comm::AbstractCall::get_string_error( string& error, const wrapper::WInternalBaseFault& fault )
{
  get_string_error( error, (InternalBaseFault*)&fault );
}

/*
 *
 *
 *
 *
 *
 *
 *
 */
bool
comm::AbstractCall::check_sub_fault( soap* S, string& error ) {
  if(S->fault) {
    if(S->fault->detail) {
      ESTYPES__InternalBaseFault_USCOREType* F = 0;
      if(S->fault->detail->ESTYPES__AccessControlFault) 
	F = S->fault->detail->ESTYPES__AccessControlFault;
      if(S->fault->detail->ESTYPES__InternalBaseFault)
	F = S->fault->detail->ESTYPES__InternalBaseFault;
//       if(S->fault->detail->ESACTIVITYTYPES__UnknownGlue2ActivityAttributeFault)
// 	F = S->fault->detail->ESACTIVITYTYPES__UnknownGlue2ActivityAttributeFault;
//       if(S->fault->detail->ESTYPES__VectorLimitExceededFault)
// 	F = S->fault->detail->ESTYPES__VectorLimitExceededFault;
      if(S->fault->detail->ESACTIVITYTYPES__InvalidParameterFault)
	F = S->fault->detail->ESACTIVITYTYPES__InvalidParameterFault;
      if(S->fault->detail->ESDELEGATIONTYPES__InternalServiceDelegationFault)
	F = S->fault->detail->ESDELEGATIONTYPES__InternalServiceDelegationFault;
      if(S->fault->detail->ESDELEGATIONTYPES__UnknownDelegationIDFault)
	F = S->fault->detail->ESDELEGATIONTYPES__UnknownDelegationIDFault;
      if(S->fault->detail->ESRESOURCEINFOTYPES__InternalResourceInfoFault)
	F = S->fault->detail->ESRESOURCEINFOTYPES__InternalResourceInfoFault;
      if(S->fault->detail->ESRESOURCEINFOTYPES__NotSupportedQueryDialectFault)
	F = S->fault->detail->ESRESOURCEINFOTYPES__NotSupportedQueryDialectFault;
      if(S->fault->detail->ESRESOURCEINFOTYPES__NotValidQueryStatementFault)
	F = S->fault->detail->ESRESOURCEINFOTYPES__NotValidQueryStatementFault;
      if(S->fault->detail->ESRESOURCEINFOTYPES__ResourceInfoNotFoundFault)
	F = S->fault->detail->ESRESOURCEINFOTYPES__ResourceInfoNotFoundFault;
      if(S->fault->detail->ESRESOURCEINFOTYPES__UnknownQueryFault)
	F = S->fault->detail->ESRESOURCEINFOTYPES__UnknownQueryFault;
     
      if(!F)
	return false;

      get_string_error( error, F );
      return true;
    } else return false;
  } else return false;
}

/*
 *
 *
 *
 *
 *
 *
 *
 */
void
comm::AbstractCall::save_soap_buffer( ) {
  if(m_SOAP)
    m_soap_buffer = m_SOAP->buf;
}
