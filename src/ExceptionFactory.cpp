/* LICENSE:
Copyright (c) Members of the EGEE Collaboration. 2010. 
See http://www.eu-egee.org/partners/ for details on the copyright
holders.  

Licensed under the Apache License, Version 2.0 (the "License"); 
you may not use this file except in compliance with the License. 
You may obtain a copy of the License at 

   http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software 
distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
implied. 
See the License for the specific language governing permissions and 
limitations under the License.

END LICENSE */

/*
  The behaviour of error code is different than that one documented:
  unexistent host -> SOAP_CLI_FAULT (faultstring="Client fault" faultcode="SOAP-ENV:Client")
  wrong tcp port  -> 111            (faultstring="Error 111" faultcode="SOAP-ENV:Client")
  wrong path      -> 404            (faultstring="HTTP error" faultcode="SOAP-ENV:Server")
*/

#include<string>
#include <cstdio>

#include "glite/ce/cream-client-api-c/ExceptionFactory.h"

using namespace std;
namespace soapProxy = glite::ce::cream_client_api::soap_proxy;
namespace ex = glite::ce::cream_client_api::cream_exceptions;


void soapProxy::ExceptionFactory::raiseException(struct soap *SOAP, const bool ignore_tag_mismatch)
  throw(ex::BaseException&,
	ex::JobUnknownException&,
	ex::InvalidArgumentException&,
	ex::OperationNotSupportedException&,
	ex::NoSuitableResourceException&,
	ex::GridProxyDelegationException&,
	ex::JobStatusInvalidException&,
	ex::GenericException&,
	ex::AuthorizationException&,
	ex::DelegationException&,
	ex::InternalException&,
	ex::JobSubmissionDisabledException&,
        ex::ConnectionTimeoutException&)
{

  int type=-1;
  void* fault=0;
  string mn, ec, des, fc;

  if( SOAP->error == SOAP_TAG_MISMATCH ) {
    if(ignore_tag_mismatch)
      return;
    else
      {
	throw ex::InternalException("SOAP TAG mismatch; gSOAP engine failed to parse the service's SOAP message");
      }
  }

  if( SOAP->error == SOAP_EOF )
    {
      throw ex::ConnectionTimeoutException("EOF detected during communication. Probably service closed connection or SOCKET TIMEOUT occurred.");
    }

  if( SOAP->error != SOAP_FAULT  && SOAP->error != SOAP_CLI_FAULT && SOAP->error != SOAP_SVR_FAULT)
    {
      string err;
    
      if( SOAP->endpoint && (string(SOAP->endpoint)!="") )
        err = string("Connection to service [")+SOAP->endpoint+"] failed: ";
      else
        err = string("Connection to service [http(s)://")+SOAP->host+SOAP->path+"] failed: ";

      char *faultstring =  (char*)*soap_faultstring(SOAP);
      char *faultcode = (char*)*soap_faultcode(SOAP);
      char *faultsubcode = (char*)*soap_faultsubcode(SOAP);
      char *faultdetail = (char*)*soap_faultdetail(SOAP);

      if (faultstring)
        err += string("FaultString=[")+faultstring+"]";

      if (faultcode)
        err += string(" - FaultCode=[")+faultcode+"]";

      if (faultsubcode)
        err += string(" - FaultSubCode=[")+faultsubcode+"]";

      if (faultdetail)
        err += string(" - FaultDetail=[")+faultdetail+"]";

      throw ex::InternalException(err);
    }

  if (SOAP->version == 2) {
    if(SOAP->fault && SOAP->fault->SOAP_ENV__Detail) {
      fault = SOAP->fault->SOAP_ENV__Detail->fault;
      type = SOAP->fault->SOAP_ENV__Detail->__type;
    }
  }
  else {
    if(SOAP->fault)
      if(SOAP->fault->detail) {
	fault = SOAP->fault->detail->fault;
	type = SOAP->fault->detail->__type;
      }
  }

  if(!fault && (SOAP->fault && SOAP->fault->detail) ) {

    CREAMTYPES__BaseFaultType* _fault = 0;
    
    if(SOAP->fault->detail->CREAMTYPES__AuthorizationFault)
      _fault = SOAP->fault->detail->CREAMTYPES__AuthorizationFault;
    
    if(SOAP->fault->detail->CREAMTYPES__GenericFault)
      _fault = SOAP->fault->detail->CREAMTYPES__GenericFault;
    
    if(SOAP->fault->detail->CREAMTYPES__InvalidArgumentFault)
      _fault = SOAP->fault->detail->CREAMTYPES__InvalidArgumentFault;
    
    if(SOAP->fault->detail->CREAMTYPES__JobSubmissionDisabledFault)
      _fault = SOAP->fault->detail->CREAMTYPES__JobSubmissionDisabledFault;
    
    if(SOAP->fault->detail->CREAMTYPES__OperationNotSupportedFault)
      _fault = SOAP->fault->detail->CREAMTYPES__OperationNotSupportedFault;

    if(SOAP->fault->detail->delegation2__DelegationException) {
    //  _fault = SOAP->fault->detail->delegation2__DelegationException;    
	// TODO
      if(SOAP->fault->detail->delegation2__DelegationException->msg)
	throw ex::DelegationException( *SOAP->fault->detail->delegation2__DelegationException->msg );
      else
	throw ex::DelegationException( "No message for this fault" );
    }
    
    if(_fault) {
      mn = _fault->MethodName;
      
      if(_fault->ErrorCode)
	ec = *_fault->ErrorCode;
      
      if(_fault->Description)
	des = *_fault->Description;
      
      if(_fault->FaultCause)
	fc = *_fault->FaultCause;
      
      if(SOAP->fault->detail->CREAMTYPES__AuthorizationFault)
	throw ex::AuthorizationException(mn, ec, des, fc, _fault->Timestamp);
      
      if(SOAP->fault->detail->CREAMTYPES__GenericFault)
	throw ex::GenericException(mn, ec, des, fc, _fault->Timestamp);
      
      if(SOAP->fault->detail->CREAMTYPES__InvalidArgumentFault)
	throw ex::InvalidArgumentException(mn, ec, des, fc, _fault->Timestamp);
      
      if(SOAP->fault->detail->CREAMTYPES__JobSubmissionDisabledFault)
	throw ex::JobSubmissionDisabledException(mn, ec, des, fc, _fault->Timestamp);
      
      if(SOAP->fault->detail->CREAMTYPES__OperationNotSupportedFault)
	throw ex::OperationNotSupportedException(mn, ec, des, fc, _fault->Timestamp);
    }
  }
  
  if(!fault) {
    soap_set_fault(SOAP);
    string err = string("Received NULL fault; the error is due to another cause: ");
    char *faultstring =  (char*)*soap_faultstring(SOAP);
    char *faultcode = (char*)*soap_faultcode(SOAP);
    char *faultsubcode = (char*)*soap_faultsubcode(SOAP);
    char *faultdetail = (char*)*soap_faultdetail(SOAP);
    
    if (faultstring)
      err += string("FaultString=[")+faultstring+"]";
    
    if (faultcode)
      err += string(" - FaultCode=[")+faultcode+"]";
    
    if (faultsubcode)
      err += string(" - FaultSubCode=[")+faultsubcode+"]";
    
    if (faultdetail)
      err += string(" - FaultDetail=[")+faultdetail+"]";
    
    throw ex::InternalException(err);
  }

  
  //if((type != s_DelegationFault1Obj.soap_type()) //&&
  if( type != SOAP_TYPE__delegation2__DelegationException )
    {
      mn = ((CREAMTYPES__BaseFaultType*)fault)->MethodName;
      if(((CREAMTYPES__BaseFaultType*)fault)->ErrorCode)
	ec = *((CREAMTYPES__BaseFaultType*)fault)->ErrorCode;
      if(((CREAMTYPES__BaseFaultType*)fault)->Description)
	des = *((CREAMTYPES__BaseFaultType*)fault)->Description;
      if(((CREAMTYPES__BaseFaultType*)fault)->FaultCause)
	fc = *((CREAMTYPES__BaseFaultType*)fault)->FaultCause;
    } else {
    if(((_delegation2__DelegationException*)fault)->msg)
      throw ex::DelegationException( *((_delegation2__DelegationException*)fault)->msg);
    else
      throw ex::DelegationException("No message available for this delegation fault");
    
  }
  
  if(type == SOAP_TYPE_CREAMTYPES__BaseFaultType)
    throw ex::BaseException(mn, ec, des, fc, ((CREAMTYPES__BaseFaultType*)fault)->Timestamp);

  if(type == SOAP_TYPE__CREAMTYPES__JobUnknownFault)
    throw ex::JobUnknownException(mn, ec, des, fc, ((CREAMTYPES__BaseFaultType*)fault)->Timestamp);

  if(type == SOAP_TYPE__CREAMTYPES__InvalidArgumentFault)
    throw ex::InvalidArgumentException(mn, ec, des, fc, ((CREAMTYPES__BaseFaultType*)fault)->Timestamp);

  if(type == SOAP_TYPE__CREAMTYPES__OperationNotSupportedFault)
    throw ex::OperationNotSupportedException(mn, ec, des, fc, ((CREAMTYPES__BaseFaultType*)fault)->Timestamp);

  if(type == SOAP_TYPE__CREAMTYPES__NoSuitableResourcesFault)
    throw ex::NoSuitableResourceException(mn, ec, des, fc, ((CREAMTYPES__BaseFaultType*)fault)->Timestamp);

  if(type == SOAP_TYPE__CREAMTYPES__DelegationIdMismatchFault)
    throw ex::GridProxyDelegationException(mn, ec, des, fc, ((CREAMTYPES__BaseFaultType*)fault)->Timestamp);

  if(type == SOAP_TYPE__CREAMTYPES__JobStatusInvalidFault)
    throw ex::JobStatusInvalidException(mn, ec, des, fc, ((CREAMTYPES__BaseFaultType*)fault)->Timestamp);

  if(type == SOAP_TYPE__CREAMTYPES__GenericFault)
    throw ex::GenericException(mn, ec, des, fc, ((CREAMTYPES__BaseFaultType*)fault)->Timestamp);

  if(type == SOAP_TYPE__CREAMTYPES__AuthorizationFault)
    throw ex::AuthorizationException(mn, ec, des, fc, ((CREAMTYPES__BaseFaultType*)fault)->Timestamp);

  if(type == SOAP_TYPE__CREAMTYPES__JobSubmissionDisabledFault)
    throw ex::JobSubmissionDisabledException(mn, ec, des, fc, ((CREAMTYPES__BaseFaultType*)fault)->Timestamp);

  throw ex::BaseException("Fault type not recognized", "", "", "", (time_t)0);
}

string soapProxy::ExceptionFactory::makeStringFromFault( CREAMTYPES__BaseFaultType* fault ) throw()
{
  string errMex = string("MethodName=[") + fault->MethodName +
    "] Timestamp=[";
  
  struct tm a;
  localtime_r(&(fault->Timestamp), &a);
  char Timestamp[80];
  memset((void *)Timestamp, 0, 80);
  
  if(fault->Timestamp>0)
    strftime(Timestamp, 80, "%a %d %b %Y %T", &a);
  
  errMex += string(Timestamp) + "]";
  
  if(fault->ErrorCode)
    errMex += " ErrorCode=[" + *fault->ErrorCode + "]";
  
  if(fault->Description)
    errMex += " Description=[" + *fault->Description + "]";
  
  if(fault->FaultCause)
    errMex += " FaultCause=[" + *fault->FaultCause + "]";

  return errMex;
}
