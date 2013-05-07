#include "glite/ce/es-client-api-c/WActivityCreationResponse.h"
#include <boost/lexical_cast.hpp>

using namespace std;

namespace wr = emi_es::client::wrapper;

/**
 *
 *
 *
 *
 *
 *
 */
wr::WActivityCreationResponse::WActivityCreationResponse( const FAULT_TYPE ft,
							  WInternalBaseFault* F,
							  string* ID,
						          string* MgrURL,
							  string* ResInfoURL,
						          WActivityStatus* astatus,
						          time_t* etnsc,
						          DirectoryReference* sin,
						          DirectoryReference* ssin,
						          DirectoryReference* sout)
{
  m_fault_type                  = ft;
  InternalBaseFaultField        = F;
#if GSOAP_VERSION_NUM==20709
#else
  ActivityIDField               = 0;
  ActivityMgmtEndpointURLField  = 0;
  ResourceInfoEndpointURLField  = 0;
#endif
  ETNSC                  	= 0;
  StageInDirectory       	= 0;
  SessionDirectory       	= 0;
  StageOutDirectory      	= 0;
#if GSOAP_VERSION_NUM==20709
  if(ID)
    ActivityIDField = *ID;
  else
    ActivityIDField = "N/A";
  if(MgrURL) 
    ActivityMgmtEndpointURLField = *MgrURL;
  else
    ActivityMgmtEndpointURLField = "N/A";
  if(ResInfoURL)
    ResourceInfoEndpointURLField = *ResInfoURL;
  else
    ResourceInfoEndpointURLField = "N/A"; 
#else
 
  if(ID)
    ActivityIDField = new string( *ID );
  if(MgrURL)
    ActivityMgmtEndpointURLField = new string( *MgrURL );
  if(ResInfoURL)
    ResourceInfoEndpointURLField = new string( *ResInfoURL );
#endif

  if(astatus)
    ActivityStatusField = new WActivityStatus( *astatus );

  if(etnsc) {
    ETNSC = new time_t;
    *ETNSC = *etnsc;
  }
  
  if(sin) {
    StageInDirectory  = new DirectoryReference( );
    StageInDirectory->URL = sin->URL;
  }
  if(ssin) {
    SessionDirectory  = new DirectoryReference( );
    SessionDirectory->URL = ssin->URL;
  }
  if(sout) {
    StageOutDirectory = new DirectoryReference( );
    StageOutDirectory->URL = sout->URL;
  }
}

/**
 *
 *
 *
 *
 *
 *
 */
void
wr::WActivityCreationResponse::set( const WActivityCreationResponse& src ) 
{
  m_fault_type           	= NONE;
  InternalBaseFaultField 	= 0;
#if GSOAP_VERSION_NUM==20709
#else
  ActivityIDField               = 0;
  ActivityMgmtEndpointURLField  = 0;
  ResourceInfoEndpointURLField  = 0;
#endif
  ETNSC                  	= 0;
  StageInDirectory       	= 0;
  SessionDirectory       	= 0;
  StageOutDirectory      	= 0;
  
  
  if(src.InternalBaseFaultField) {
    m_fault_type = NUM_INTERNALBASE;
    InternalBaseFaultField = new WInternalBaseFault( *((WInternalBaseFault*)src.InternalBaseFaultField) );
  }
  if(src.AccessControlFaultField) {
    m_fault_type = NUM_ACCESSCONTROL;
    InternalBaseFaultField = new WInternalBaseFault( *((WInternalBaseFault*)src.AccessControlFaultField) );
  }
  if(src.UnsupportedCapabilityFaultField) {
    m_fault_type = NUM_UNSUPPORTEDCAPABILITY;
    InternalBaseFaultField = new WInternalBaseFault( *((WInternalBaseFault*)src.UnsupportedCapabilityFaultField) );
  }
  if(src.InvalidActivityDescriptionFaultField) {
    m_fault_type = NUM_INVALIDACTIVITYDESCRIPTION;
    InternalBaseFaultField = new WInternalBaseFault( *((WInternalBaseFault*)src.InvalidActivityDescriptionFaultField) );
  }
  if(src.InvalidActivityDescriptionSemanticFaultField) {
    m_fault_type = NUM_INVALIDACTIVITYDESCRIPTIONSEMANTIC;
    InternalBaseFaultField = new WInternalBaseFault( *((WInternalBaseFault*)src.InvalidActivityDescriptionSemanticFaultField) );
  }
  
  m_fault_message = (InternalBaseFaultField ? ((WInternalBaseFault*)InternalBaseFaultField)->toString( ) : "");

#if GSOAP_VERSION_NUM==20709
   ActivityIDField = src.ActivityIDField;
   ActivityMgmtEndpointURLField = src.ActivityMgmtEndpointURLField;
   ResourceInfoEndpointURLField = src.ResourceInfoEndpointURLField;
#else
  
  if( src.ActivityIDField )
    ActivityIDField = new string( *src.ActivityIDField );

  if( src.ActivityMgmtEndpointURLField )
    ActivityMgmtEndpointURLField = new string( *src.ActivityMgmtEndpointURLField );

  if( src.ResourceInfoEndpointURLField )
    ResourceInfoEndpointURLField = new string( *src.ResourceInfoEndpointURLField );
#endif

  if( src.ActivityStatusField )
    ActivityStatusField = new WActivityStatus( *((WActivityStatus*)src.ActivityStatusField) );
  
  if( src.ETNSC ) {
    ETNSC = new time_t;
    *ETNSC = *src.ETNSC;
  }

  if( src.StageInDirectory ) {
    StageInDirectory = new DirectoryReference( );
    StageInDirectory->URL = src.StageInDirectory->URL; 
  }

  if( src.SessionDirectory ) {
    SessionDirectory = new DirectoryReference( );
    SessionDirectory->URL = src.SessionDirectory->URL;
  }

  if( src.StageOutDirectory ) {
    StageOutDirectory= new DirectoryReference( );
    StageOutDirectory->URL = src.StageOutDirectory->URL;
  }
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::WActivityCreationResponse::WActivityCreationResponse( const WActivityCreationResponse& src )
  : ActivityCreationResponse()
{
  this->set( src );
}

/**
 *
 *
 *
 *
 *
 *
 */
void
wr::WActivityCreationResponse::free( )
{
  
  WActivityStatus *status = 0;
  if(ActivityStatusField)
    status = (WActivityStatus *)ActivityStatusField;

#if GSOAP_VERSION_NUM==20709  
#else
  delete ActivityIDField;
  delete ActivityMgmtEndpointURLField;
  delete ResourceInfoEndpointURLField;
#endif
  delete status;
  delete InternalBaseFaultField;
  delete ETNSC;
  delete StageInDirectory;
  delete SessionDirectory;
  delete StageOutDirectory;
}

/**
 *
 *
 *
 *
 *
 *
 */
string
wr::WActivityCreationResponse::toString( const bool tabbed ) const
{
//   string tab;
//   if(tabbed)
//     tab = "\n\t";
//   else 
//     tab = "\n";
//   
//   string out;
//   switch(m_fault_type) {
//     case NONE:
//     break;
//     case INVALIDACTIVITYDESCRIPTION:
//       out += tab + "*** Invalid Activity Description Fault:";
//       out += tab + "    Message=" + InvalidActivityDescriptionFaultField->Message;
//       out += tab + "    Timestamp=" + (InvalidActivityDescriptionFaultField->Timestamp ? boost::lexical_cast<string>( *InvalidActivityDescriptionFaultField->Timestamp ) : "N/A");
//       out += tab + "    Description=" + (InvalidActivityDescriptionFaultField->Description ? *InvalidActivityDescriptionFaultField->Description : "N/A");
//       out += tab + "    FailureCode=" + (InvalidActivityDescriptionFaultField->FailureCode ? boost::lexical_cast<string>( *InvalidActivityDescriptionFaultField->FailureCode ) : "N/A");
//       break;
//     case INVALIDACTIVITYDESCRIPTIONSEMANTIC:
//       out += tab + "*** Invalid Activity Description Semantic Fault:";
//       out += tab + "    Message=" + InvalidActivityDescriptionSemanticFaultField->Message;
//       out += tab + "    Timestamp=" + (InvalidActivityDescriptionSemanticFaultField->Timestamp ? boost::lexical_cast<string>( *InvalidActivityDescriptionSemanticFaultField->Timestamp ) : "N/A");
//       out += tab + "    Description=" + (InvalidActivityDescriptionSemanticFaultField->Description ? *InvalidActivityDescriptionSemanticFaultField->Description : "N/A");
//       out += tab + "    FailureCode=" + (InvalidActivityDescriptionSemanticFaultField->FailureCode ? boost::lexical_cast<string>( *InvalidActivityDescriptionSemanticFaultField->FailureCode ) : "N/A");
//       break;  
//     case UNSUPPORTEDCAPABILITY:
//       out += tab + "*** Unsupported Capability Fault:";
//       out += tab + "    Message=" + UnsupportedCapabilityFaultField->Message;
//       out += tab + "    Timestamp=" + (UnsupportedCapabilityFaultField->Timestamp ? boost::lexical_cast<string>( *UnsupportedCapabilityFaultField->Timestamp ) : "N/A");
//       out += tab + "    Description=" + (UnsupportedCapabilityFaultField->Description ? *UnsupportedCapabilityFaultField->Description : "N/A");
//       out += tab + "    FailureCode=" + (UnsupportedCapabilityFaultField->FailureCode ? boost::lexical_cast<string>( *UnsupportedCapabilityFaultField->FailureCode ) : "N/A");
//       break;
//     case INTERNALBASE:
//       out += tab + "*** Internal Base Fault:";
//       out += tab + "    Message=" + InternalBaseFaultField->Message;
//       out += tab + "    Timestamp=" + (InternalBaseFaultField->Timestamp ? boost::lexical_cast<string>( *InternalBaseFaultField->Timestamp ) : "N/A");
//       out += tab + "    Description=" + (InternalBaseFaultField->Description ? *InternalBaseFaultField->Description : "N/A");
//       out += tab + "    FailureCode=" + (InternalBaseFaultField->FailureCode ? boost::lexical_cast<string>( *InternalBaseFaultField->FailureCode ) : "N/A");
//       break;
//     case ACCESSCONTROL:
//       out += tab + "*** Access Control Fault:";
//       out += tab + "    Message=" + AccessControlFaultField->Message;
//       out += tab + "    Timestamp=" + (AccessControlFaultField->Timestamp ? boost::lexical_cast<string>( *AccessControlFaultField->Timestamp ) : "N/A");
//       out += tab + "    Description=" + (AccessControlFaultField->Description ? *AccessControlFaultField->Description : "N/A");
//       out += tab + "    FailureCode=" + (AccessControlFaultField->FailureCode ? boost::lexical_cast<string>( *AccessControlFaultField->FailureCode ) : "N/A");
//       break;
//     default:
//       break;
//   }
// //   if( InternalBaseFaultField ) {
// //     InternalBaseFault *IBF = (InternalBaseFault*)InternalBaseFaultField;
// //     out += IBF->toString();
// //   }
//   ActivityStatus *status = (ActivityStatus*)ActivityStatusField;
// 
//   out += tab + "ActivityID=" + (ActivityIDField ? *ActivityIDField : "N/A");
//   out += tab + "ActivityManagementURL=" + (ActivityManagementURL ? *ActivityManagementURL : "N/A");
//   out += tab + "ResourceInfoURL=" + (ResourceInfoURL ? *ResourceInfoURL : "N/A");
//   
//   if(status)
//     out += tab + status->toString( );
//   
//   out += tab + "ETNSC=" + (ETNSC ? boost::lexical_cast<string>( *ETNSC ) : "N/A");
//   out += tab + util::join( StageInDirectory->URL, ", " );
//   out += tab + util::join( SessionDirectory->URL, ", " );
//   out += tab + util::join( StageOutDirectory->URL, ", " );

  return "";// out;
}
