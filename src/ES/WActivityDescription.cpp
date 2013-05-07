#include "glite/ce/es-client-api-c/WActivityDescription.h"


using namespace std;

namespace wr  = emi_es::client::wrapper;

/**
 *
 *
 *
 *
 *
 *
 */
wr::WActivityDescription::WActivityDescription( WActivityIdentification* act,
						WApplication* appl,
						WResources* res,
						WDataStaging* datas )
{
  if( act )
    ActivityIdentificationField = new WActivityIdentification( *act );
  else
    ActivityIdentificationField = 0;

  if(appl)						     
    ApplicationField = new WApplication( *appl );
  else
    ApplicationField = 0;
    
  if( res ) 
    ResourcesField = new WResources( *res );
  else
    ResourcesField = 0;
  
  if( datas )
    DataStagingField = new WDataStaging( *datas );
  else
    DataStagingField = 0;

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
wr::WActivityDescription::set( const WActivityDescription& src )
{ 
  ActivityIdentificationField  = 0;
  ApplicationField             = 0;
  ResourcesField               = 0;
  DataStagingField             = 0;

  if( src.ActivityIdentificationField )
    ActivityIdentificationField 
      = new WActivityIdentification( *((WActivityIdentification*)src.ActivityIdentificationField) );
  
  if( src.ApplicationField )
    ApplicationField 
      = new WApplication( *((WApplication*)src.ApplicationField) );
  
  if( src.ResourcesField )
    ResourcesField 
      = new WResources( *((WResources*)src.ResourcesField) );
  
  if( src.DataStagingField )
    DataStagingField 
      = new WDataStaging( *((WDataStaging*)src.DataStagingField) );
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::WActivityDescription::WActivityDescription( const WActivityDescription& src )
  : ActivityDescription()
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
wr::WActivityDescription::free( )
{
  WActivityIdentification* ai = (WActivityIdentification*)ActivityIdentificationField;
  WApplication *app           = (WApplication *)ApplicationField;
  WResources *res             = (WResources *)ResourcesField;
  WDataStaging *ds            = (WDataStaging *)DataStagingField;

  delete ai;
  delete app;
  delete res;
  delete ds;
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
wr::WActivityDescription::toString( const bool tabbed ) const
{ 
  WActivityIdentification* ai = (WActivityIdentification*)ActivityIdentificationField;
  WApplication *app           = (WApplication *)ApplicationField;
  WResources *res             = (WResources *)ResourcesField;
  WDataStaging *ds            = (WDataStaging *)DataStagingField;

  string out;
  if(ai)
    out += ai->toString( tabbed );
  if(app)
    out += app->toString( tabbed );
  if(res)
    out += res->toString( tabbed );
  if(ds)
    out += ds->toString( tabbed );
  
  return out;
}

