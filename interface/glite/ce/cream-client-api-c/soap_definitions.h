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

#ifndef __SOAP_DEFINITIONS_H__
#define __SOAP_DEFINITIONS_H__

#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"


/**
 *
 * Remote CALLs
 *
 */
#define SOAP_CALL_JOB_CANCEL soap_call_creamapij__JobCancel
#define SOAP_CALL_JOB_SUSPEND soap_call_creamapij__JobSuspend
#define SOAP_CALL_JOB_RESUME soap_call_creamapij__JobResume
#define SOAP_CALL_JOB_START soap_call_creamapij__JobStart
#define SOAP_CALL_JOB_LIST soap_call_creamapij__JobList
#define SOAP_CALL_JOB_INFO soap_call_creamapij__JobInfo
#define SOAP_CALL_JOB_STATUS soap_call_creamapij__JobStatus
#define SOAP_CALL_JOB_PURGE soap_call_creamapij__JobPurge
#define SOAP_CALL_JOB_SIGNAL soap_call_creamapij__JobSignal
#define SOAP_CALL_JOB_ASSESS soap_call_creamapij__JobAssess
#define SOAP_CALL_JOB_REGISTER soap_call_creamapij__JobRegister
#define SOAP_CALL_GETPROXYREQ soap_call_delegation1__getProxyReq
#define SOAP_CALL_PUTPROXY soap_call_delegation1__putProxy
#define SOAP_CALL_PING soap_call_creamapij__Ping

/**
 *
 * Data types
 *
 */
#define SOAP_JOBINFO creamtypes__JobInfo
#define SOAP_JOBINFO_RESPONSE_MEMBER jobInfo
#define SOAP_JOBINFO_LIST creamtypes__JobInfoList
#define SOAP_JOBINFO_LIST_MEMBER jobInfo

//ns5__JobInfoList
#define SOAP_JOB_REGISTER_RESP creamapij__JobRegisterResponse
#define SOAP_JOB_START_RESP creamapij__JobStartResponse
#define SOAP_JOB_CANCEL_RESP creamapij__JobCancelResponse
#define SOAP_JOB_SUSPEND_RESP creamapij__JobSuspendResponse
#define SOAP_JOB_RESUME_RESP creamapij__JobResumeResponse
#define SOAP_JOB_ASSESS_RESP creamapij__JobAssessResponse
#define SOAP_JOB_PURGE_RESP creamapij__JobPurgeResponse
#define SOAP_JOB_INFO_RESP creamapij__JobInfoResponse
#define SOAP_JOB_STATUS_RESP creamapij__JobStatusResponse
#define SOAP_JOB_INFO_RESP_MEMBER JobInfoResponse
#define SOAP_JOB_IDLIST creamtypes__JobIdList
#define SOAP_JOB_IDLIST_MEMBER jobID
#define SOAP_JOB_FILTER creamtypes__JobFilter
#define SOAP_JOB_SIGNAL_RESP creamapij__JobSignalResponse
#define SOAP_JOB_LIST_RESP creamapij__JobListResponse
#define SOAP_JOB_LIST_RESP_MEMBER jobIdList
//#define SOAP_JOB_STATUS ns4__Status
#define PROXY_REQUEST_RESPONDE delegation1__getProxyReqResponse
#define PUT_PROXY_RESPONSE delegation1__putProxyResponse

/**
 *
 * FAULTS
 *
 */
#define BASEFAULT cefaults__BaseFaultType
#define DELEGATIONEXCEPTION delegation1__DelegationExceptionType
#endif
