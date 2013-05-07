#ifndef EMIES_CLIENTLIB_WRAPPERS_TYPEDEFS_H
#define EMIES_CLIENTLIB_WRAPPERS_TYPEDEFS_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"

typedef _ESACTIVITYMANAGEMENTTYPES__CancelActivity		CancelActivity;
typedef _ESACTIVITYMANAGEMENTTYPES__CancelActivityResponse	CancelActivityResponse;
typedef _ESACTIVITYMANAGEMENTTYPES__CancelActivityResponseItem	CancelActivityResponseItem;
typedef _ESACTIVITYMANAGEMENTTYPES__NotifyRequestItem		NotifyRequestItem;
typedef _ESACTIVITYMANAGEMENTTYPES__NotifyResponseItem		NotifyResponseItem;
typedef _ESACTIVITYMANAGEMENTTYPES__NotifyService		NotifyService;
typedef _ESACTIVITYMANAGEMENTTYPES__NotifyServiceResponse	NotifyServiceResponse;
typedef _ESACTIVITYMANAGEMENTTYPES__PauseActivity		PauseActivity;
typedef _ESACTIVITYMANAGEMENTTYPES__PauseActivityResponse	PauseActivityResponse;
typedef _ESACTIVITYMANAGEMENTTYPES__PauseActivityResponseItem	PauseActivityResponseItem;
typedef _ESACTIVITYMANAGEMENTTYPES__RestartActivity		RestartActivity;
typedef _ESACTIVITYMANAGEMENTTYPES__RestartActivityResponse	RestartActivityResponse;
typedef _ESACTIVITYMANAGEMENTTYPES__RestartActivityResponseItem	RestartActivityResponseItem;
typedef _ESACTIVITYMANAGEMENTTYPES__ResumeActivity		ResumeActivity;
typedef _ESACTIVITYMANAGEMENTTYPES__ResumeActivityResponse	ResumeActivityResponse;
typedef _ESACTIVITYMANAGEMENTTYPES__ResumeActivityResponseItem	ResumeActivityResponseItem;
typedef _ESACTIVITYMANAGEMENTTYPES__WipeActivity		WipeActivity;
typedef _ESACTIVITYMANAGEMENTTYPES__WipeActivityResponse	WipeActivityResponse;
typedef _ESACTIVITYMANAGEMENTTYPES__WipeActivityResponseItem	WipeActivityResponseItem;
typedef ESACTIVITYTYPES__ActivityInfoDocument_USCOREt		ActivityInfoDocument;
typedef _ESACTIVITYTYPES__ActivityInfoItem			ActivityInfoItem;
typedef _ESACTIVITYTYPES__ActivityNotFoundFault			ActivityNotFoundFault;
typedef _ESACTIVITYTYPES__ActivityNotInTerminalStateFault	ActivityNotInTerminalStateFault;
typedef _ESACTIVITYTYPES__ActivityStatus			ActivityStatus2;
typedef _ESACTIVITYTYPES__ActivityStatusItem			ActivityStatusItem;
typedef _ESACTIVITYTYPES__AttributeInfoItem			AttributeInfoItem;
typedef _ESACTIVITYTYPES__ComputingActivityHistory		ComputingActivityHistory;
typedef _ESACTIVITYTYPES__GetActivityInfo			GetActivityInfo;
typedef _ESACTIVITYTYPES__GetActivityInfoResponse		GetActivityInfoResponse;
typedef _ESACTIVITYTYPES__GetActivityStatus			GetActivityStatus;
typedef _ESACTIVITYTYPES__GetActivityStatusResponse		GetActivityStatusResponse;
typedef _ESACTIVITYTYPES__InternalNotificationFault		InternalNotificationFault;
typedef _ESACTIVITYTYPES__InvalidActivityIDFault		InvalidActivityIDFault;
typedef _ESACTIVITYTYPES__InvalidActivityLimitFault		InvalidActivityLimitFault;
typedef _ESACTIVITYTYPES__InvalidActivityStateFault		InvalidActivityStateFault;
typedef _ESACTIVITYTYPES__InvalidParameterFault			InvalidParameterFault;
typedef _ESACTIVITYTYPES__ListActivities			ListActivities;
typedef _ESACTIVITYTYPES__ListActivitiesResponse		ListActivitiesResponse;
typedef _ESACTIVITYTYPES__Operation				Operation;
typedef _ESACTIVITYTYPES__OperationNotAllowedFault		OperationNotAllowedFault;
typedef _ESACTIVITYTYPES__OperationNotPossibleFault		OperationNotPossibleFault;
typedef _ESACTIVITYTYPES__UnableToRetrieveStatusFault		UnableToRetrieveStatusFault;
typedef _ESACTIVITYTYPES__UnknownActivityIDFault		UnknownActivityIDFault;
typedef _ESACTIVITYTYPES__UnknownAttributeFault			UnknownAttributeFault;
typedef _ESADL__ActivityDescription				ActivityDescription;
typedef _ESADL__ActivityIdentification				ActivityIdentification;
typedef _ESADL__Application					Application;
typedef _ESADL__Benchmark					Benchmark;
typedef ESADL__CoprocessorType					CoprocessorType;
typedef _ESADL__DataStaging					DataStaging;
typedef ESADL__Executable_USCOREType				ExecutableType;
typedef _ESADL__InputFile					InputFile;
typedef ESADL__NetworkInfoType					NetworkInfoType;
typedef _ESADL__Notification					Notification;
typedef _ESADL__OperatingSystem					OperatingSystem;
typedef ESADL__OptionalTime					OptionalTime;
typedef ESADL__OptionType					OptionType;
typedef _ESADL__OutputFile					OutputFile;
typedef _ESADL__ParallelEnvironment				ParallelEnvironment;
typedef _ESADL__ProcessesPerHost				ProcessesPerHost;
typedef _ESADL__RemoteLogging					RemoteLogging;
typedef _ESADL__Resources					Resources;
typedef _ESADL__RuntimeEnvironment				RuntimeEnvironment;
typedef _ESADL__SlotRequirement					SlotRequirement;
typedef _ESADL__SlotRequirement_SlotsPerHost			SlotRequirement_SlotsPerHost;
typedef _ESADL__Source						Source;
typedef _ESADL__Target						Target;
typedef _ESADL__ThreadsPerProcess				ThreadsPerProcess;
typedef _ESCREATIONTYPES__ActivityCreationResponse		ActivityCreationResponse;
typedef _ESCREATIONTYPES__CreateActivity			CreateActivity;
typedef _ESCREATIONTYPES__CreateActivityResponse		CreateActivityResponse;
typedef ESCREATIONTYPES__DirectoryReference			DirectoryReference;
typedef _ESCREATIONTYPES__InvalidActivityDescriptionFault	InvalidActivityDescriptionFault;
typedef _ESCREATIONTYPES__InvalidActivityDescriptionSemanticFault	InvalidActivityDescriptionSemanticFault;
typedef _ESCREATIONTYPES__UnsupportedCapabilityFault		UnsupportedCapabilityFault;
typedef _ESDELEGATIONTYPES__GetDelegationInfo			GetDelegationInfo;
typedef _ESDELEGATIONTYPES__GetDelegationInfoResponse		GetDelegationInfoResponse;
typedef _ESDELEGATIONTYPES__InitDelegation			InitDelegation;
typedef _ESDELEGATIONTYPES__InitDelegationResponse		InitDelegationResponse;
typedef _ESDELEGATIONTYPES__InternalServiceDelegationFault	InternalServiceDelegationFault;
typedef _ESDELEGATIONTYPES__PutDelegation			PutDelegation;
typedef _ESDELEGATIONTYPES__UnknownDelegationIDFault		UnknownDelegationIDFault;
typedef _ESRESOURCEINFOTYPES__GetResourceInfo			GetResourceInfo;
typedef _ESRESOURCEINFOTYPES__GetResourceInfoResponse		GetResourceInfoResponse;
typedef _ESRESOURCEINFOTYPES__InternalResourceInfoFault		InternalResourceInfoFault;
typedef _ESRESOURCEINFOTYPES__NotSupportedQueryDialectFault	NotSupportedQueryDialectFault;
typedef _ESRESOURCEINFOTYPES__NotValidQueryStatementFault	NotValidQueryStatementFault;
typedef ESRESOURCEINFOTYPES__QueryExpressionType		QueryExpressionType;
typedef _ESRESOURCEINFOTYPES__QueryResourceInfo			QueryResourceInfo;
typedef _ESRESOURCEINFOTYPES__QueryResourceInfoItem		QueryResourceInfoItem;
typedef _ESRESOURCEINFOTYPES__QueryResourceInfoResponse		QueryResourceInfoResponse;
typedef _ESRESOURCEINFOTYPES__ResourceInfoNotFoundFault		ResourceInfoNotFoundFault;
typedef _ESRESOURCEINFOTYPES__Services				Services;
typedef _ESRESOURCEINFOTYPES__UnknownQueryFault			UnknownQueryFault;
typedef _ESTYPES__AccessControlFault				AccessControlFault;
typedef _ESTYPES__ActivityStatus				ActivityStatus;
typedef ESTYPES__InternalBaseFault_USCOREType			InternalBaseFault;
typedef _ESTYPES__VectorLimitExceededFault			VectorLimitExceededFault;
typedef ns1__AccessPolicy_USCOREt				AccessPolicy;
typedef ns1__ActivityBase_USCOREt				ActivityBase;
typedef ns1__Activity_USCOREt					Activity;
typedef _ns1__Activity_USCOREt_Associations			Activity_Associations;
typedef ns1__AdminDomain_USCOREt				AdminDomain;
typedef _ns1__ApplicationEnvironments				ApplicationEnvironments;
typedef ns1__ApplicationEnvironment_USCOREt			ApplicationEnvironment;
typedef _ns1__ApplicationEnvironment_USCOREt_Associations	ApplicationEnvironment_Associations;
typedef ns1__ApplicationHandle_USCOREt				ApplicationHandle;
typedef ns1__Benchmark_USCOREt					Benchmark2;
typedef _ns1__ComputingActivities				ComputingActivities;
typedef ns1__ComputingActivity_USCOREt				ComputingActivity;
typedef _ns1__ComputingActivity_USCOREt_Associations		ComputingActivity_Associations;
typedef ns1__ComputingEndpoint_USCOREt				ComputingEndpoint;
typedef _ns1__ComputingEndpoint_USCOREt_Associations		ComputingEndpoint_Associations;
typedef ns1__ComputingManager_USCOREt				ComputingManager;
typedef ns1__ComputingService_USCOREt				ComputingService;
typedef _ns1__ComputingService_USCOREt_Associations		ComputingService_Associations;
typedef ns1__ComputingShare_USCOREt				ComputingShare;
typedef _ns1__ComputingShare_USCOREt_Associations		ComputingShare_Associations;
typedef ns1__Contact_USCOREt					Contact;
typedef ns1__DataStore_USCOREt					DataStore;
typedef ns1__Domains_USCOREt					Domains;
typedef ns1__Domain_USCOREt					Domain;
typedef ns1__EndpointBase_USCOREt				EndpointBase;
typedef ns1__Endpoint_USCOREt					Endpoint;
typedef _ns1__Endpoint_USCOREt_Activities			Endpoint_Activities;
typedef ns1__Entity_USCOREt					Entity;
typedef _ns1__ExecutionEnvironments				ExecutionEnvironments;
typedef ns1__ExecutionEnvironment_USCOREt			ExecutionEnvironment;
typedef _ns1__ExecutionEnvironment_USCOREt_Associations		ExecutionEnvironment_Associations;
typedef ns1__Extensions_USCOREt					Extensions;
typedef ns1__Extension_USCOREt					Extension;
typedef ns1__Location_USCOREt					Location;
typedef ns1__Manager_USCOREt					Manager;
typedef ns1__MappingPolicy_USCOREt				MappingPolicy;
typedef ns1__Policy_USCOREt					Policy;
typedef _ns1__Policy_USCOREt_Associations			Policy_Associations;
typedef ns1__ResourceBase_USCOREt				ResourceBase;
typedef ns1__ServiceBase_USCOREt				ServiceBase;
typedef ns1__Service_USCOREt					Service;
typedef _ns1__Service_USCOREt_Associations			Service_Associations;
typedef ns1__ShareBase_USCOREt					ShareBase;
typedef ns1__StorageAccessProtocol_USCOREt			StorageAccessProtocol;
typedef _ns1__StorageAccessProtocol_USCOREt_Associations	StorageAccessProtocol_Associations;
typedef ns1__StorageEndpoint_USCOREt				StorageEndpoint;
typedef ns1__StorageManager_USCOREt				StorageManager;
typedef ns1__StorageServiceCapacity_USCOREt			StorageServiceCapacity;
typedef ns1__StorageService_USCOREt				StorageService;
typedef _ns1__StorageService_USCOREt_Associations		StorageService_Associations;
typedef ns1__StorageShareCapacity_USCOREt			StorageShareCapacity;
typedef ns1__StorageShare_USCOREt				StorageShare;
typedef _ns1__StorageShare_USCOREt_Associations			StorageShare_Associations;
typedef ns1__ToComputingService_USCOREt				ToComputingService;
typedef _ns1__ToComputingService_USCOREt_Associations		ToComputingService_Associations;
typedef ns1__ToStorageService_USCOREt				ToStorageService;
typedef _ns1__ToStorageService_USCOREt_Associations		ToStorageService_Associations;
typedef ns1__UserDomain_USCOREt					UserDomain;

/**
 *
 * ActivityTypeEnumeration / ComputingActivityType
 *
 */
#define   ActivityTypeEnumeration    ESADL__ActivityTypeEnumeration     
#define            ACTIVITYTYPE_COLLECTIONELEMENT  ESADL__ActivityTypeEnumeration__collectionelement
#define            ACTIVITYTYPE_PARALLELELEMENT    ESADL__ActivityTypeEnumeration__parallelelement
#define            ACTIVITYTYPE_SINGLE             ESADL__ActivityTypeEnumeration__single
#define            ACTIVITYTYPE_WORKFLOWNODE       ESADL__ActivityTypeEnumeration__workflownode

#define ComputingActivityType ns1__ComputingActivityType_USCOREt
#define  COMPUTINGACTIVITYTYPE_COLLECTIONELEMENT ns1__ComputingActivityType_USCOREt__collectionelement
#define  COMPUTINGACTIVITYTYPE_PARALLELELEMENT ns1__ComputingActivityType_USCOREt__parallelelement
#define COMPUTINGACTIVITYTYPE_SINGLE ns__ComputingActivityType_USCOREt__single
#define COMPUTINGACTIVITYTYPE_WORKFLOWNODE ns1__ComputingActivityType_USCOREt__workflownode

/**
 *
 * ActivityStatus/Attribute and PROTOCOLTYPEENUMERATION
 *
 */
#define ActivityStatusState ESTYPES__ActivityStatusState
#define ActivityStatusAttribute ESTYPES__ActivityStatusAttribute

#define   ACCEPTED      	ESTYPES__ActivityStatusState__accepted
#define	  PREPROCESSING         ESTYPES__ActivityStatusState__preprocessing
#define	  PROCESSING            ESTYPES__ActivityStatusState__processing
#define	  PROCESSING_ACCEPTING  ESTYPES__ActivityStatusState__processing_accepting
#define	  PROCESSING_QUEUED     ESTYPES__ActivityStatusState__processing_queued
#define	  PROCESSING_RUNNING    ESTYPES__ActivityStatusState__processing_running
#define	  POSTPROCESSING        ESTYPES__ActivityStatusState__postprocessing
#define	  TERMINAL              ESTYPES__ActivityStatusState__terminal

#define   EMAIL			ESADL__ProtocolTypeEnumeration__email

#define   UNKNOWN               9999

#define	  VALIDATING 			ESTYPES__ActivityStatusAttribute__validating
#define	  SERVER_PAUSED 		ESTYPES__ActivityStatusAttribute__server_paused
#define	  PAUSED 			ESTYPES__ActivityStatusAttribute__client_paused
#define	  CLIENT_STAGEIN_POSSIBLE 	ESTYPES__ActivityStatusAttribute__client_stagein_possible
#define	  CLIENT_STAGEOUT_POSSIBLE 	ESTYPES__ActivityStatusAttribute__client_stageout_possible
#define	  PROVISIONING 			ESTYPES__ActivityStatusAttribute__provisioning
#define	  DEPROVISIONING 		ESTYPES__ActivityStatusAttribute__deprovisioning
#define	  SERVER_STAGEIN 		ESTYPES__ActivityStatusAttribute__server_stagein
#define	  SERVER_STAGEOUT 		ESTYPES__ActivityStatusAttribute__server_stageout
#define	  BATCH_SUSPEND 		ESTYPES__ActivityStatusAttribute__batch_suspend
#define	  APP_RUNNING 			ESTYPES__ActivityStatusAttribute__app_running
#define	  PREPROCESSING_CANCEL 		ESTYPES__ActivityStatusAttribute__preprocessing_cancel
#define	  PROCESSING_CANCEL 		ESTYPES__ActivityStatusAttribute__processing_cancel
#define	  POSTPROCESSING_CANCEL 	ESTYPES__ActivityStatusAttribute__postprocessing_cancel
#define	  VALIDATION_FAILURE 		ESTYPES__ActivityStatusAttribute__validation_failure
#define	  PREPROCESSING_FAILURE 	ESTYPES__ActivityStatusAttribute__preprocessing_failure
#define	  PROCESSING_FAILURE 		ESTYPES__ActivityStatusAttribute__processing_failure
#define	  POSTPROCESSING_FAILURE 	ESTYPES__ActivityStatusAttribute__postprocessing_failure
#define	  APP_FAILURE 			ESTYPES__ActivityStatusAttribute__app_failure
#define	  EXPIRED 			ESTYPES__ActivityStatusAttribute__expired


//--------------------------------
//           ENUMERATIONS
//--------------------------------
#define NodeAccessEnumeration ESADL__NodeAccessEnumeration
#define CoprocessorEnumeration ESADL__CoprocessorEnumeration
#define ProtocolTypeEnumeration ESADL__ProtocolTypeEnumeration
#define NetworkInfoEnumeration ESADL__NetworkInfoEnumeration

#define CreationFlagEnumeration__overwrite ESADL__CreationFlagEnumeration__overwrite
#define CreationFlagEnumeration__append ESADL__CreationFlagEnumeration__append
#define CreationFlagEnumeration__dontOverwrite ESADL__CreationFlagEnumeration__dontOverwrite


#define BenchmarkTypeEnumeration ESADL__BenchmarkTypeEnumeration
#define BOGOMIPS ESADL__BenchmarkTypeEnumeration__bogomips
#define CFP2006 ESADL__BenchmarkTypeEnumeration__cfp2006
#define CINT2006 ESADL__BenchmarkTypeEnumeration__cint2006
#define LINPACK ESADL__BenchmarkTypeEnumeration__linpack
#define SPECFP2000 ESADL__BenchmarkTypeEnumeration__specfp2000
#define SPECINT2000 ESADL__BenchmarkTypeEnumeration__specint2000

//--------------------------------
//           FIELDS
//--------------------------------
#define CreationFlagEnumeration ESADL__CreationFlagEnumeration
#define TargetField ESADL__Target
#define SourceField ESADL__Source
#define InputFileField ESADL__InputFile
#define OutputFileField ESADL__OutputFile
#define ActivityIdentificationField ESADL__ActivityIdentification
#define ApplicationField ESADL__Application
#define ResourcesField ESADL__Resources
#define DataStagingField ESADL__DataStaging
#define OperatingSystemField ESADL__OperatingSystem
#define RuntimeEnvironmentField ESADL__RuntimeEnvironment
#define ParallelEnvironmentField ESADL__ParallelEnvironment
#define SlotRequirementField ESADL__SlotRequirement
#define OptionField ESADL__Option
#define ActivityDescriptionField ESADL__ActivityDescription
#define EnvironmentField ESADL__Environment
#define RemoteLoggingField ESADL__RemoteLogging
#define NotificationField ESADL__Notification
#define BenchmarkField ESADL__Benchmark
#define ProcessesPerHostField ESADL__ProcessesPerHost
#define ThreadsPerProcessField ESADL__ThreadsPerProcess
#define OptionTypeField ESADL__Option
#define ActivityIDField ESTYPES__ActivityID
#define ActivityMgmtEndpointURLField ESTYPES__ActivityMgmtEndpointURL
#define ResourceInfoEndpointURLField ESTYPES__ResourceInfoEndpointURL
#define ActivityStatusField ESTYPES__ActivityStatus
#define InternalBaseFaultField ESTYPES__InternalBaseFault
#define AccessControlFaultField ESTYPES__AccessControlFault
#define InvalidActivityDescriptionFaultField ESCREATIONTYPES__InvalidActivityDescriptionFault
#define InvalidActivityDescriptionSemanticFaultField ESCREATIONTYPES__InvalidActivityDescriptionSemanticFault
#define UnsupportedCapabilityFaultField ESCREATIONTYPES__UnsupportedCapabilityFault
#define ActivityCreationResponseField ESCREATIONTYPES__ActivityCreationResponse
	
	
//--------------------------------
//           REMOTE CALLS
//--------------------------------
#define CREATEACTIVITYCALL soap_call___ESCREATION__CreateActivity
	
//--------------------------------
//           FAULT TYPES
//--------------------------------
#define INTERNALBASE 				SOAP_TYPE_ESTYPES__InternalBaseFault_USCOREType
#define UNSUPPORTEDCAPABILITY 			SOAP_TYPE__ESCREATIONTYPES__UnsupportedCapabilityFault
#define INVALIDACTIVITYDESCRIPTIONSEMANTIC	SOAP_TYPE__ESCREATIONTYPES__InvalidActivityDescriptionSemanticFault
#define INVALIDACTIVITYDESCRIPTION 		SOAP_TYPE__ESCREATIONTYPES__InvalidActivityDescriptionFault
#define VECTORLIMITEXCEEDED 			SOAP_TYPE__ESTYPES__VectorLimitExceededFault
#define ACCESSCONTROL 				SOAP_TYPE__ESTYPES__AccessControlFault
#define INVALIDACTIVITYID 			SOAP_TYPE__ESACTIVITYTYPES__InvalidActivityIDFault
#define UNKNOWNACTIVITYID 			SOAP_TYPE__ESACTIVITYTYPES__UnknownActivityIDFault
#define UNABLETORETRIEVESTATUS 			SOAP_TYPE__ESACTIVITYTYPES__UnableToRetrieveStatusFault
#define UNKNOWNATTRIBUTE 			SOAP_TYPE__ESACTIVITYTYPES__UnknownAttributeFault
#define OPERATIONNOTALLOWED 			SOAP_TYPE__ESACTIVITYTYPES__OperationNotAllowedFault
#define ACTIVITYNOTFOUND 			SOAP_TYPE__ESACTIVITYTYPES__ActivityNotFoundFault
#define INTERNALNOTIFICATION 			SOAP_TYPE__ESACTIVITYTYPES__InternalNotificationFault
#define OPERATIONNOTPOSSIBLE			SOAP_TYPE__ESACTIVITYTYPES__OperationNotPossibleFault
#define INVALIDACTIVITYSTATE			SOAP_TYPE__ESACTIVITYTYPES__InvalidActivityStateFault
#define ACTIVITYNOTINTERMINALSTATE		SOAP_TYPE__ESACTIVITYTYPES__ActivityNotInTerminalStateFault
#define INVALIDACTIVITYLIMIT			SOAP_TYPE__ESACTIVITYTYPES__InvalidActivityLimitFault
#define INVALIDPARAMETER			SOAP_TYPE__ESACTIVITYTYPES__InvalidParameterFault
#define UNKNOWNDELEGATION			SOAP_TYPE__ESDELEGATIONTYPES__UnknownDelegationIDFault
#define INTERNALSERVICEDELEGATION		SOAP_TYPE__ESDELEGATIONTYPES__InternalServiceDelegationFault
#define NOTSUPPORTEDQUERYDIALECT		SOAP_TYPE__ESRESOURCEINFOTYPES__NotSupportedQueryDialectFault
#define NOTVALIDQUERYSTATEMENT			SOAP_TYPE__ESRESOURCEINFOTYPES__NotValidQueryStatementFault
#define UNKNOWNQUERY				SOAP_TYPE__ESRESOURCEINFOTYPES__UnknownQueryFault
#define INTERNALRESOURCEINFO			SOAP_TYPE__ESRESOURCEINFOTYPES__InternalResourceInfoFault
#define RESOURCEINFONOTFOUND			SOAP_TYPE__ESRESOURCEINFOTYPES__ResourceInfoNotFoundFault

#endif
