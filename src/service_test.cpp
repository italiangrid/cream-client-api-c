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

  This is a stand-alone test service; it is conceived
  only to debug communication between a CREAM gSOAP client
  and a service.

  It is not linked to the build system, so to compile it issue the command (after a regula ant stage):
  
  g++ -g -o service_test -I../interface/glite/ce/cream-client-api-c -I./ -I ../../repository/externals/gsoap/2.7.6b/slc4_ia32_gcc346/include/ -I../build/src/autogen -I../../stage/include -I ../../repository/externals/globus/4.0.3-VDT-1.6.0/slc4_ia32_gcc346/include/gcc32dbgpthr/ service_test.cpp ../../repository/externals/gsoap/2.7.6b/slc4_ia32_gcc346/src/stdsoap2.cpp ../build/src/autogen/CREAM_CLIENTServer.cpp ../build/src/autogen/CREAM_CLIENTC.cpp -L../../stage/lib

  for AUTHN:
  g++ -g -o service_test -I../interface/glite/ce/cream-client-api-c -I./ -I../../repository/externals/gsoap/2.7.6b/slc4_ia32_gcc346/include/ -I../build/src/autogen -I../../stage/include -I../../repository/vdt/globus/4.0.3-VDT-1.6.0/slc4_ia32_gcc346/include/gcc32dbgpthr service_test.cpp ../../repository/externals/gsoap/2.7.6b/slc4_ia32_gcc346/src/stdsoap2.cpp ../build/src/autogen/CREAM_CLIENTServer.cpp ../build/src/autogen/CREAM_CLIENTC.cpp -L../../stage/lib -L../../stage/lib -lglite_security_gsoap_plugin_276b_gcc32dbgpthr  

  for AUTHN+CLASSAD:
  g++ -g -O0 -o service_test -I../../repository/externals/classads/0.9.8/slc4_ia32_gcc346/include -I../interface/glite/ce/cream-client-api-c -I./ -I../../repository/externals/gsoap/2.7.6b/slc4_ia32_gcc346/include/ -I../build/src/autogen -I../../stage/include -I../../repository/vdt/globus/4.0.3-VDT-1.6.0/slc4_ia32_gcc346/include/gcc32dbgpthr service_test.cpp ../../repository/externals/gsoap/2.7.6b/slc4_ia32_gcc346/src/stdsoap2.cpp ../build/src/autogen/CREAM_CLIENTServer.cpp ../build/src/autogen/CREAM_CLIENTC.cpp -L../../stage/lib -L../../stage/lib -lglite_security_gsoap_plugin_276b_gcc32dbgpthr -DWANT_NAMESPACES -L../../repository/externals/classads/0.9.8/slc4_ia32_gcc346/lib -lclassad
*/
#include "CREAM_CLIENTH.h"
#include "CREAM_CLIENTStub.h"
#include "CREAM_CLIENT.nsmap"

#include "JobPropertyWrapper.h"
#include "JobIdWrapper.h"
#include "JobStatusWrapper.h"
#include "JobCommandWrapper.h"
#include "JobInfoWrapper.h"

#include <string>
#include <iostream>

#include "classad_distribution.h"

#include <netdb.h>

using namespace std;
using namespace glite::ce::cream_client_api::soap_proxy;

SOAP_NMAC struct Namespace namespaces[] = {};

extern "C" {
#undef IOV_MAX // this is very ugly, but the only way to silent a warning concerning
               // the redefinition of IOV_MAX
#include "glite/security/glite_gsplugin.h"      
}

static map<string, string> jobMap;

void handleFault(struct soap* soap, const string& F) throw();

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6
__CREAM__JobRegister(struct soap* soap, 
		     _CREAMTYPES__JobRegisterRequest *Request,
		     _CREAMTYPES__JobRegisterResponse *Response)
{
  static int i;
  
  cout << "CALLED JobRegister"<<endl;
  i++;
  
  
  vector<CREAMTYPES__JobDescription*>::const_iterator it;
  it = Request->jobDescriptionList.begin();

  char CREAMJOBID[16];
  memset((void*) CREAMJOBID, 0, 16);

  sprintf(CREAMJOBID, "%015d", i);

  string JDL = (*it)->JDL;
  classad::ClassAdParser parser;
  classad::ClassAd *rootAD = parser.ParseClassAd( JDL );
  string gridJobId;
  if ( rootAD->EvaluateAttrString( "edg_jobid", gridJobId ) ) {
    
    cout << "Putting CREAMJOBID["
	 <<CREAMJOBID
	 <<"] -> [" 
	 << gridJobId 
	 <<"] in the jobMap cache"<<endl;
    jobMap[CREAMJOBID] = gridJobId;
    
  }
  delete rootAD;

  //  cout << "jobDescriptionID = [" << *(*it)->jobDescriptionId << "]" << endl;
  
  CREAMTYPES__JobRegisterResult *R = new CREAMTYPES__JobRegisterResult(); 
  CREAMTYPES__JobId *jobId = new CREAMTYPES__JobId();

//   char buf[1024];
//   memset((void*)buf, 0, 1024);
//   sprintf(buf, "%d", time(NULL));

  jobId->id = CREAMJOBID;//buf;//"Alvise ID";
  

  jobId->creamURL = "https://vm-ice-01.pd.infn.it:8443/ce-cream/services/CREAM2";//a;
  R->jobDescriptionId = new string(*(*it)->jobDescriptionId);
  R->__union_3 = SOAP_UNION_CREAMTYPES__union_3_jobId;
  R->union_3.jobId = jobId;
  Response->result.push_back( R );
    
  return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__JobCancel(struct soap* S, 
		   CREAMTYPES__JobFilter *cancel, 
		   CREAMTYPES__CommandResult *resp)
{
   cout << "CALLED JobCancel"<<endl;
   return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__getServiceInfo(struct soap*, 
			int CREAMTYPES__ServiceInfoRequest, 
			CREAMTYPES__ServiceInfo *CREAMTYPES__ServiceInfoResponse)
{
  cout << "CALLED getServiceInfo"<<endl;
  return SOAP_OK; 
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__setLease(struct soap*, 
		  CREAMTYPES__Lease *CREAMTYPES__setLeaseRequest, 
		  CREAMTYPES__Lease *CREAMTYPES__setLeaseResponse)
{
  cout << "CALLED setLease"<<endl;

  CREAMTYPES__setLeaseResponse->leaseId = CREAMTYPES__setLeaseRequest->leaseId;
  CREAMTYPES__setLeaseResponse->leaseTime = time(NULL)+7200;

  return SOAP_OK; 
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__getLease(struct soap*, 
		  string CREAMTYPES__getLeaseRequest, 
		  CREAMTYPES__Lease *CREAMTYPES__getLeaseResponse)
{
  cout << "CALLED getLease"<<endl;

  return SOAP_OK; 
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__getLeaseList(struct soap*, 
		      _CREAMTYPES__getLeaseListResponse *CREAMTYPES__getLeaseListResponse)
{
  cout << "CALLED getLeaseList"<<endl;
  return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__deleteLease(struct soap*, 
		     string CREAMTYPES__deleteLeaseRequest, 
		     struct __CREAM__deleteLeaseResponse &_param_2)
{
  cout << "CALLED deleteLeaseId"<<endl;
  return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__JobSetLeaseId(soap* soap, _CREAMTYPES__JobSetLeaseIdRequest* uno, CREAMTYPES__CommandResult* due)
{
  cout << "CALLED JobSetLeaseId"<<endl;
  return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__JobSuspend(struct soap*, 
		    CREAMTYPES__JobFilter *CREAMTYPES__JobSuspendRequest, 
		    CREAMTYPES__CommandResult *CREAMTYPES__JobSuspendResponse)
{
   cout << "CALLED JobSuspend"<<endl;
   return SOAP_FAULT;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__JobResume(struct soap*, 
		   CREAMTYPES__JobFilter *CREAMTYPES__JobResumeRequest, 
		   CREAMTYPES__CommandResult *CREAMTYPES__JobResumeResponse)
{
   cout << "CALLED JobResume"<<endl;
   return SOAP_FAULT;
}


//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__JobLease(struct soap*, 
		  CREAMTYPES__Lease *CREAMTYPES__JobLeaseRequest, 
		  CREAMTYPES__Lease *CREAMTYPES__JobLeaseResponse)
{
   cout << "CALLED JobLease"<<endl;

   CREAMTYPES__JobLeaseResponse = new CREAMTYPES__Lease();

   CREAMTYPES__JobLeaseResponse->leaseId = "Lease 123";
   CREAMTYPES__JobLeaseResponse->leaseTime = time(NULL);

   return SOAP_OK;

}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__JobList(struct soap*, 
		 _CREAMTYPES__JobListResponse *CREAMTYPES__JobListResponse)
{
   cout << "CALLED JobList"<<endl;
   return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__JobStart(struct soap*, 
		  CREAMTYPES__JobFilter *CREAMTYPES__JobStartRequest, 
		  CREAMTYPES__CommandResult *CREAMTYPES__JobStartResponse)
{
  cout << "CALLED JobStart"<<endl;

  return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__JobPurge(struct soap* s, 
		  CREAMTYPES__JobFilter *CREAMTYPES__JobPurgeRequest, 
		  CREAMTYPES__CommandResult *CREAMTYPES__JobPurgeResponse)
{
   cout << "CALLED JobPurge"<<endl;
   return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__JobInfo(struct soap* s, 
		 CREAMTYPES__JobFilter *req, 
		 _CREAMTYPES__JobInfoResponse *resp)
{
  /*
    class SOAP_CMAC _CREAMTYPES__JobInfoResponse
    {
    public:
    std::vector<CREAMTYPES__JobInfoResult * >result;   
    ...
    ...
  */

  /*
    class SOAP_CMAC CREAMTYPES__JobInfoResult
    {
    public:
    int __union_2;  /* union discriminant (of union defined below) 
    union CREAMTYPES__union_2 union_2; // required
    std::string *jobDescriptionId;     // optional attribute 
  */

  /*
    union CREAMTYPES__union_2
    {
    #define SOAP_UNION_CREAMTYPES__union_2_jobInfo  (1)
    CREAMTYPES__JobInfo *jobInfo;
    #define SOAP_UNION_CREAMTYPES__union_2_JobUnknownFault  (2)
    _CREAMTYPES__JobUnknownFault *JobUnknownFault;
    #define SOAP_UNION_CREAMTYPES__union_2_JobStatusInvalidFault    (3)
    _CREAMTYPES__JobStatusInvalidFault *JobStatusInvalidFault;
    #define SOAP_UNION_CREAMTYPES__union_2_DelegationIdMismatchFault        (4)
    _CREAMTYPES__DelegationIdMismatchFault *DelegationIdMismatchFault;
    #define SOAP_UNION_CREAMTYPES__union_2_DateMismatchFault        (5)
    _CREAMTYPES__DateMismatchFault *DateMismatchFault;
    #define SOAP_UNION_CREAMTYPES__union_2_LeaseIdMismatchFault     (6)
    _CREAMTYPES__LeaseIdMismatchFault *LeaseIdMismatchFault;
    #define SOAP_UNION_CREAMTYPES__union_2_GenericFault     (7)
    _CREAMTYPES__GenericFault *GenericFault;
    };
  */

  cout << "CALLED JobInfo"<<endl;
  
  if(req->jobId.empty()) {
    
    
  } else {
    
    vector<CREAMTYPES__JobId*>::const_iterator it=req->jobId.begin();
    for(; it!=req->jobId.end(); ++it )
      {

	CREAMTYPES__JobId* job1, *job2, *job3, *job4, *job5, *job6;
	job1 = new CREAMTYPES__JobId();
	job2 = new CREAMTYPES__JobId();
	job3 = new CREAMTYPES__JobId();
	job4 = new CREAMTYPES__JobId();
	job5 = new CREAMTYPES__JobId();
	job6 = new CREAMTYPES__JobId();

	CREAMTYPES__Status *status1 = new CREAMTYPES__Status();
	status1->jobId = job2;
	status1->name = "IDLE";
	status1->timestamp = time(NULL)+5;
	status1->exitCode = new string("0");
	status1->failureReason = 0;
	status1->description = 0;

	
	CREAMTYPES__Status *status2 = new CREAMTYPES__Status();
	status2->jobId = job3;
	status2->name = "PENDING";
	status2->timestamp = time(NULL)+6;
	status2->exitCode = new string("0");
	status2->failureReason = 0;
	status2->description = 0;

	CREAMTYPES__Status *status3 = new CREAMTYPES__Status();
	status3->jobId = job4;
	status3->name = "RUNNING";
	status3->timestamp = time(NULL)+7;
	status3->exitCode = new string("0");
	status3->failureReason = 0;
	status3->description = 0;

	CREAMTYPES__Status *status4 = new CREAMTYPES__Status();
	status4->jobId = job5;
	status4->name = "REALLY-RUNNING";
	status4->timestamp = time(NULL)+8;
	status4->exitCode = new string("0");
	status4->failureReason = 0;
	status4->description = 0;

	CREAMTYPES__Status *status5 = new CREAMTYPES__Status();
	status5->jobId = job6;
	status5->name = "DONE-OK";
	status5->timestamp = time(NULL)+9;
	status5->exitCode = new string("0");
	status5->failureReason = 0;
	status5->description = 0;

	job1->id = (*it)->id;
	job1->creamURL = "https://vm-ice-01.pd.infn.it:8443/ce-cream/services/CREAM2";

	job2->id = (*it)->id;
	job2->creamURL = "https://vm-ice-01.pd.infn.it:8443/ce-cream/services/CREAM2";

	job3->id = (*it)->id;
	job3->creamURL = "https://vm-ice-01.pd.infn.it:8443/ce-cream/services/CREAM2";

	job4->id = (*it)->id;
	job4->creamURL = "https://vm-ice-01.pd.infn.it:8443/ce-cream/services/CREAM2";

	job5->id = (*it)->id;
	job5->creamURL = "https://vm-ice-01.pd.infn.it:8443/ce-cream/services/CREAM2";

	job6->id = (*it)->id;
	job6->creamURL = "https://vm-ice-01.pd.infn.it:8443/ce-cream/services/CREAM2";

	CREAMTYPES__JobInfoResult* R = new CREAMTYPES__JobInfoResult();

	R->__union_2 = SOAP_UNION_CREAMTYPES__union_2_jobInfo;
	R->union_2.jobInfo = new CREAMTYPES__JobInfo();

	R->jobDescriptionId = new string( (*it)->id );

	R->union_2.jobInfo->jobId = job1;
	R->union_2.jobInfo->fatherJobId = 0;
	if(jobMap.find( (*it)->id ) != jobMap.end() )
	  R->union_2.jobInfo->GridJobId = jobMap[ (*it)->id ];
	else
	  R->union_2.jobInfo->GridJobId = "";

	R->union_2.jobInfo->workerNode = "wn.pd.infn.it";
	R->union_2.jobInfo->JDL = new string("");
	R->union_2.jobInfo->lease = new CREAMTYPES__Lease();
	R->union_2.jobInfo->lease->leaseId = "pippo";
	R->union_2.jobInfo->lease->leaseTime = time(NULL) + 7200;

 	R->union_2.jobInfo->status.push_back(status1);
	R->union_2.jobInfo->status.push_back(status2);
	R->union_2.jobInfo->status.push_back(status3);
	R->union_2.jobInfo->status.push_back(status4);
	R->union_2.jobInfo->status.push_back(status5);

	
	resp->result.push_back( R );

      }
    
  }
  
  return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__JobStatus(struct soap*, 
		   CREAMTYPES__JobFilter *req, 
		   _CREAMTYPES__JobStatusResponse *resp)
{
   cout << "CALLED JobStatus"<<endl;

   return SOAP_OK;

}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
delegation2__getProxyReq(struct soap*, 
			 std::string _delegationID, 
			 struct delegation2__getProxyReqResponse &_param_6)
{
  cout << "CALLED DoesAccept"<<endl;
  return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
delegation2__getNewProxyReq(struct soap*, 
			    struct delegation2__getNewProxyReqResponse &_param_7)
{
   cout << "CALLED getProxyReq"<<endl;
   return SOAP_FAULT;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
delegation2__renewProxyReq(struct soap*, 
			   std::string _delegationID, 
			   struct delegation2__renewProxyReqResponse &_param_8)
{
   cout << "CALLED renewProxyReq"<<endl;
   return SOAP_FAULT;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
delegation2__putProxy(struct soap*, 
		      std::string _delegationID, 
		      std::string _proxy, 
		      struct delegation2__putProxyResponse &_param_9)
{
   cout << "CALLED putProxy"<<endl;
   return SOAP_FAULT;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6  
delegation2__getTerminationTime(struct soap*, 
				string _delegationID, 
				struct delegation2__getTerminationTimeResponse &_param_10)
{
   cout << "CALLED getTerminationTime"<<endl;
   return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6  
delegation2__destroy(struct soap*, 
		     std::string _delegationID, 
		     struct delegation2__destroyResponse &_param_11)
{
   cout << "CALLED destroy"<<endl;
   return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
__CREAM__acceptNewJobSubmissions(struct soap*, 
				 bool CREAMTYPES__acceptNewJobSubmissions, 
				 struct __CREAM__acceptNewJobSubmissionsResponse &_param_1)
{
  cout << "CALLED acceptNewJobSubmissions" << endl;
  return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
delegation2__getVersion(struct soap*, 
			struct delegation2__getVersionResponse &_param_3)
{
  cout << "CALLED getVersion" << endl;
  return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6 
delegation2__getInterfaceVersion(struct soap*, 
				 struct delegation2__getInterfaceVersionResponse &_param_4)
{
  cout << "CALLED getInterfaceVersion" << endl;
  return SOAP_OK;
}

//________________________________________________________________________________
SOAP_FMAC5 int SOAP_FMAC6  
delegation2__getServiceMetadata(struct soap*, 
				string _key, 
				struct delegation2__getServiceMetadataResponse &_param_5)
{
  cout << "CALLED getServiceMetadata" << endl;
  return SOAP_OK;
}

//________________________________________________________________________________
string resolveName(const string& address) {
//   struct in_addr addr;

//   // must use inet_pton instead
//   struct in6_addr addr;//serveraddr;

//   inet_aton(AF_INET6, address.c_str(), &addr);

//   struct hostent* H = gethostbyaddr(&addr, sizeof(addr), AF_INET);
//   if(H)
//     return H->h_name;
//   else {
//     return "UnresolvedHost";
//   }
  

  struct addrinfo * result;
  struct addrinfo * res;
  int error;
  
  /* resolve the domain name into a list of addresses */
  error = getaddrinfo(address.c_str(), NULL, NULL, &result);
  
  if (0 != error)
    {   
      perror("error in getaddrinfo: ");
      return "UnresolvedHost";
    }   
  
  if (result == NULL)
    {   
      perror("getaddrinfo found no results\n");
      return "UnresolvedHost";
    }   
  
  for (res = result; res != NULL; res = res->ai_next)
    {   
      char hostname[NI_MAXHOST] = "";
      
      error = getnameinfo(res->ai_addr, res->ai_addrlen, hostname, NI_MAXHOST, NULL, 0, 0); 
      
      if (0 != error)
        {
	  fprintf(stderr, "error in getnameinfo: %s\n", gai_strerror(error));
	  continue;
        }
      
      if (*hostname)
        {
	  printf("hostname: %s\n", hostname);
        }
      
    }   
  
  freeaddrinfo(result);

}

//_________________________________________________________________________________
void handleFault(struct soap* soap, const string& F) throw()
{
     if(F == "FAULT1") {
       _CREAMTYPES__GenericFault *fault = new _CREAMTYPES__GenericFault();
       fault->MethodName = "JobRegister";
       fault->ErrorCode = new string("GenericFault");
       fault->Description = new string("You requested this job to fail");
       fault->FaultCause = new string("Triggered by client");
       fault->Timestamp = time(NULL);
       soap_receiver_fault(soap, "Stack dump", NULL);
       if (soap->version == 2) // SOAP 1.2 is used
       {
         soap->fault->SOAP_ENV__Detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->SOAP_ENV__Detail->__type = SOAP_TYPE__CREAMTYPES__GenericFault; // stack type
         soap->fault->SOAP_ENV__Detail->fault = fault; // point to stack
         soap->fault->SOAP_ENV__Detail->__any = NULL; // no other XML data
       }
       else 
       {
         soap->fault->detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->detail->__type = SOAP_TYPE__CREAMTYPES__GenericFault; // stack type
         soap->fault->detail->fault = fault; // point to stack
         soap->fault->detail->__any = NULL; // no other XML data
       }
       //return SOAP_FAULT;
     }
     if(F == "FAULT2") {
       _CREAMTYPES__AuthorizationFault *fault = new _CREAMTYPES__AuthorizationFault();
       fault->MethodName = "JobRegister";
       fault->ErrorCode = new string("AuthorizationFault");
       fault->Description = new string("You requested this job to fail");
       fault->FaultCause = new string("Triggered by client");
       fault->Timestamp = time(NULL);
       soap_receiver_fault(soap, "Stack dump", NULL);
       if (soap->version == 2) // SOAP 1.2 is used
       {
         soap->fault->SOAP_ENV__Detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->SOAP_ENV__Detail->__type = SOAP_TYPE__CREAMTYPES__AuthorizationFault; // stack type
         soap->fault->SOAP_ENV__Detail->fault = fault; // point to stack
         soap->fault->SOAP_ENV__Detail->__any = NULL; // no other XML data
       }
       else 
       {
         soap->fault->detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->detail->__type = SOAP_TYPE__CREAMTYPES__AuthorizationFault; // stack type
         soap->fault->detail->fault = fault; // point to stack
         soap->fault->detail->__any = NULL; // no other XML data
       }             
       //return SOAP_FAULT;
     }
     if(F == "FAULT3") {
       _CREAMTYPES__JobUnknownFault *fault = new _CREAMTYPES__JobUnknownFault();
       fault->MethodName = "JobRegister";
       fault->ErrorCode = new string("JobUnknownFault");
       fault->Description = new string("You requested this job to fail");
       fault->FaultCause = new string("Triggered by client"); 
       fault->Timestamp = time(NULL);
       soap_receiver_fault(soap, "Stack dump", NULL);
       if (soap->version == 2) // SOAP 1.2 is used
       {
         soap->fault->SOAP_ENV__Detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->SOAP_ENV__Detail->__type = SOAP_TYPE__CREAMTYPES__JobUnknownFault; // stack type
         soap->fault->SOAP_ENV__Detail->fault = fault; // point to stack
         soap->fault->SOAP_ENV__Detail->__any = NULL; // no other XML data
       }
       else 
       {
         soap->fault->detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->detail->__type = SOAP_TYPE__CREAMTYPES__JobUnknownFault; // stack type
         soap->fault->detail->fault = fault; // point to stack
         soap->fault->detail->__any = NULL; // no other XML data
       }             
       //return SOAP_FAULT;
     }
     if(F == "FAULT4") {
       _CREAMTYPES__InvalidArgumentFault *fault = new _CREAMTYPES__InvalidArgumentFault();
       fault->MethodName = "JobRegister";
       fault->ErrorCode = new string("InvalidArgumentFault");
       fault->Description = new string("You requested this job to fail");
       fault->FaultCause = new string("Triggered by client"); 
       fault->Timestamp = time(NULL);
       soap_receiver_fault(soap, "Stack dump", NULL);
       if (soap->version == 2) // SOAP 1.2 is used
       {
         soap->fault->SOAP_ENV__Detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->SOAP_ENV__Detail->__type = SOAP_TYPE__CREAMTYPES__InvalidArgumentFault; // stack type
         soap->fault->SOAP_ENV__Detail->fault = fault; // point to stack
         soap->fault->SOAP_ENV__Detail->__any = NULL; // no other XML data
       }
       else 
       {
         soap->fault->detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->detail->__type = SOAP_TYPE__CREAMTYPES__InvalidArgumentFault; // stack type
         soap->fault->detail->fault = fault; // point to stack
         soap->fault->detail->__any = NULL; // no other XML data
       }             
       //return SOAP_FAULT;
     }
     if(F == "FAULT5") {
       _CREAMTYPES__OperationNotSupportedFault *fault = new _CREAMTYPES__OperationNotSupportedFault();
       fault->MethodName = "JobRegister";
       fault->ErrorCode = new string("OperationNotSupportedFault");
       fault->Description = new string("You requested this job to fail");
       fault->FaultCause = new string("Triggered by client");
       fault->Timestamp = time(NULL);
       soap_receiver_fault(soap, "Stack dump", NULL);
       if (soap->version == 2) // SOAP 1.2 is used
       {
         soap->fault->SOAP_ENV__Detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->SOAP_ENV__Detail->__type = SOAP_TYPE__CREAMTYPES__OperationNotSupportedFault; // stack type
         soap->fault->SOAP_ENV__Detail->fault = fault; // point to stack
         soap->fault->SOAP_ENV__Detail->__any = NULL; // no other XML data
       }
       else 
       {
         soap->fault->detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->detail->__type = SOAP_TYPE__CREAMTYPES__OperationNotSupportedFault; // stack type
         soap->fault->detail->fault = fault; // point to stack
         soap->fault->detail->__any = NULL; // no other XML data
       }    
       //return SOAP_FAULT;
     }
     if(F == "FAULT6") {
       _CREAMTYPES__NoSuitableResourcesFault *fault = new _CREAMTYPES__NoSuitableResourcesFault();
       fault->MethodName = "JobRegister";
       fault->ErrorCode = new string("NoSuitableResourcesFault");
       fault->Description = new string("You requested this job to fail");
       fault->FaultCause = new string("Triggered by client");
       fault->Timestamp = time(NULL);
       soap_receiver_fault(soap, "Stack dump", NULL);
       if (soap->version == 2) // SOAP 1.2 is used
       {
         soap->fault->SOAP_ENV__Detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->SOAP_ENV__Detail->__type = SOAP_TYPE__CREAMTYPES__NoSuitableResourcesFault; // stack type
         soap->fault->SOAP_ENV__Detail->fault = fault; // point to stack
         soap->fault->SOAP_ENV__Detail->__any = NULL; // no other XML data
       }
       else 
       {
         soap->fault->detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->detail->__type = SOAP_TYPE__CREAMTYPES__NoSuitableResourcesFault; // stack type
         soap->fault->detail->fault = fault; // point to stack
         soap->fault->detail->__any = NULL; // no other XML data
       }   
       //return SOAP_FAULT;
     }
     if(F == "FAULT7") {
       _CREAMTYPES__JobStatusInvalidFault *fault = new _CREAMTYPES__JobStatusInvalidFault();
       fault->MethodName = "JobRegister";
       fault->ErrorCode = new string("JobStatusInvalidFault");
       fault->Description = new string("You requested this job to fail");
       fault->FaultCause = new string("Triggered by client"); 
       fault->Timestamp = time(NULL);
       soap_receiver_fault(soap, "Stack dump", NULL);
       if (soap->version == 2) // SOAP 1.2 is used
       {
         soap->fault->SOAP_ENV__Detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->SOAP_ENV__Detail->__type = SOAP_TYPE__CREAMTYPES__JobStatusInvalidFault; // stack type
         soap->fault->SOAP_ENV__Detail->fault = fault; // point to stack
         soap->fault->SOAP_ENV__Detail->__any = NULL; // no other XML data
       }
       else 
       {
         soap->fault->detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->detail->__type = SOAP_TYPE__CREAMTYPES__JobStatusInvalidFault; // stack type
         soap->fault->detail->fault = fault; // point to stack
         soap->fault->detail->__any = NULL; // no other XML data
       }      
       //return SOAP_FAULT;
     }
     if(F == "FAULT8") {
       _CREAMTYPES__JobSubmissionDisabledFault *fault = new _CREAMTYPES__JobSubmissionDisabledFault();
       fault->MethodName = "JobRegister";
       fault->ErrorCode = new string("JobSubmissionDisabled");
       fault->Description = new string("You requested this job to fail");
       fault->FaultCause = new string("Triggered by client");
       fault->Timestamp = time(NULL);
       soap_receiver_fault(soap, "Stack dump", NULL);
       if (soap->version == 2) // SOAP 1.2 is used
       {
         soap->fault->SOAP_ENV__Detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->SOAP_ENV__Detail->__type = SOAP_TYPE__CREAMTYPES__JobSubmissionDisabledFault; // stack type
         soap->fault->SOAP_ENV__Detail->fault = fault; // point to stack
         soap->fault->SOAP_ENV__Detail->__any = NULL; // no other XML data
       }
       else 
       {
         soap->fault->detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail));
         soap->fault->detail->__type = SOAP_TYPE__CREAMTYPES__JobSubmissionDisabledFault; // stack type
         soap->fault->detail->fault = fault; // point to stack
         soap->fault->detail->__any = NULL; // no other XML data
       }
     }   
}


//________________________________________________________________________________
int main( int argc, char* argv[] )
{
  if(argc<2) return 0;
  
  struct soap *soap;
  int m, s; // master and slave sockets
//   char *cert = "/tmp/x509up_u501";
//   char *key  = "/tmp/x509up_u501";

  char *cert = 0;//argv[2];
  char *key  = 0;//argv[3];

  if(argc > 3) {
    cert = argv[2];
    key  = argv[3];
  }

  glite_gsplugin_Context        ctx;

  if ( cert || key ) {
    if ( glite_gsplugin_init_context(&ctx) ) {
      perror("init context"); 
      exit(1); 
    }
    ::unsetenv("X509_USER_CERT");
    ::unsetenv("X509_USER_KEY");
    ::setenv("X509_USER_CERT", cert, 0);
    ::setenv("X509_USER_KEY", key, 0);
    if (glite_gsplugin_set_credential(ctx, cert, key)) {
      fprintf (stderr, "Failed to set credentials. Maybe you need to remove the passphrase from the key pem file.\n");
      exit(1);
    }
  }
  
  soap = soap_new();
  if(!soap) {
    fprintf(stderr, "Couldn't create SOAP structure. STOP!");
    exit(1);
  }

  if(cert && key ) {
    if ( soap_register_plugin_arg(soap, glite_gsplugin, ctx? : NULL) ) {
      fprintf(stderr, "Can't register plugin\n");
      exit(1);
    }
  }



  //soap_init(&soap);
  //  soap_set_namespaces(&soap, CREAM_CLIENT_namespaces);
  soap_set_namespaces(soap, CREAM_CLIENT_namespaces);
  
  //m = soap_bind(&soap, NULL, atoi(argv[1]), 100);
  m = soap_bind(soap, NULL, atoi(argv[1]), 100);

  if (m < 0)
    soap_print_fault(soap, stderr);
  else
    {
      //fprintf(stderr, "Socket connection successful: master socket = %d\n", m);
      for (int i = 1; ; i++)
	{
	  s = soap_accept(soap);
	  if (s < 0)
	    {
	      soap_print_fault(soap, stderr);
	      break;
            }
	  char buf[1024];
	  sprintf(buf, "%d.%d.%d.%d", 
		  (soap->ip >> 24)&0xFF, 
		  (soap->ip >> 16)&0xFF, 
		  (soap->ip >> 8)&0xFF, 
		  soap->ip&0xFF);
	  
	  fprintf(stderr, 
		  "%d: accepted connection from IP=%s (%s) socket=%d\n",
		  i,
		  buf,
		  resolveName(buf).c_str(),
		  s);
	  
	  if(CREAM_CLIENT_serve(soap) != SOAP_OK) // process RPC request
	    {
	      soap_print_fault(soap, stderr); // print error
	      //fprintf(stderr, "plugin err: %s", glite_gsplugin_errdesc(&soap));
	    }
	  else
	    fprintf(stderr, "\nrequest served\n");
	  
	  soap_destroy(soap); // clean up class instances
	  soap_end(soap); // clean up everything and close socket
	}
    }
  soap_done(soap); // close master socket and detach environment 
}
