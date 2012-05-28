#include "glite/ce/es-client-api-c/ActivityCreationResponse.h"
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
wr::ActivityCreationResponse::ActivityCreationResponse(InternalBaseFault* ibf,
						       const string& ID,
						       const string& MgrURI,
						       const ActivityStatus& astatus,
						       const time_t etnsc,
						       const DirectoryReferenceType& sin,
						       const DirectoryReferenceType& ssin,
						       const DirectoryReferenceType& sout)
{
  if( ibf ) {
    InternalBaseFaultField = new InternalBaseFault( *ibf );
    m_fault_type = (FAULT_TYPE)ibf->soap_type();
  }
  else
    InternalBaseFaultField = 0;
  
  ActivityIDField = new string( ID );
  ActivityManagerURI = new string( MgrURI );
  ActivityStatusField = new ActivityStatus( astatus );

  ETNSC = new time_t;
  *ETNSC = etnsc;

  StageInDirectory = new DirectoryReferenceType( );
  StageInDirectory->URL = sin.URL;

  SessionDirectory = new DirectoryReferenceType( );
  SessionDirectory->URL = ssin.URL;

  StageOutDirectory= new DirectoryReferenceType( );
  StageOutDirectory->URL = sout.URL;
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
wr::ActivityCreationResponse::set( const ActivityCreationResponse& src ) 
{
  InternalBaseFaultField = 0;
  ActivityIDField = 0;
  ActivityManagerURI = 0;
  ActivityStatusField = 0;
  ETNSC = 0;
  StageInDirectory = 0;
  SessionDirectory = 0;
  StageOutDirectory = 0;

  if( src.InternalBaseFaultField ) {
    InternalBaseFaultField = new InternalBaseFault( *((InternalBaseFault*)src.InternalBaseFaultField) );
    m_fault_type = (FAULT_TYPE)src.InternalBaseFaultField->soap_type();
  }
  
  if( src.ActivityIDField )
    ActivityIDField = new string( *src.ActivityIDField );

  if( src.ActivityManagerURI )
    ActivityManagerURI = new string( *src.ActivityManagerURI );

  if( src.ActivityStatusField )
    ActivityStatusField = new ActivityStatus( *((ActivityStatus*)src.ActivityStatusField) );
  
  if( src.ETNSC ) {
    ETNSC = new time_t;
    *ETNSC = *src.ETNSC;
  }

  if( src.StageInDirectory ) {
    StageInDirectory = new DirectoryReferenceType( );
    StageInDirectory->URL = src.StageInDirectory->URL; 
  }

  if( src.SessionDirectory ) {
    SessionDirectory = new DirectoryReferenceType( );
    SessionDirectory->URL = src.SessionDirectory->URL;
  }

  if( src.StageOutDirectory ) {
    StageOutDirectory= new DirectoryReferenceType( );
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
wr::ActivityCreationResponse::ActivityCreationResponse( const ActivityCreationResponse& src )
  : ActivityCreationResponseType()
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
wr::ActivityCreationResponse::free( )
{
  InternalBaseFault *ibf = (InternalBaseFault*)InternalBaseFaultField;
  ActivityStatus *status = (ActivityStatus *)ActivityStatusField;
  
  delete ibf;
  
  delete ActivityIDField;
  delete ActivityManagerURI;
  
  delete status;
  
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
wr::ActivityCreationResponse::toString( const bool tabbed ) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
  
  string out;
  if( InternalBaseFaultField ) {
    InternalBaseFault *IBF = (InternalBaseFault*)InternalBaseFaultField;
    out += IBF->toString();
  }
  ActivityStatus *status = (ActivityStatus*)ActivityStatusField;

  out += tab + "ActivityID=" + (ActivityIDField ? *ActivityIDField : "N/A");
  out += tab + "ActivityManagerURI=" + (ActivityManagerURI ? *ActivityManagerURI : "N/A");
  if(status)
    out += tab + status->toString( );
  
  out += tab + "ETNSC=" + (ETNSC ? boost::lexical_cast<string>( *ETNSC ) : "N/A");
  out += tab + util::join( StageInDirectory->URL, ", " );
  out += tab + util::join( SessionDirectory->URL, ", " );
  out += tab + util::join( StageOutDirectory->URL, ", " );

  return out;
}
