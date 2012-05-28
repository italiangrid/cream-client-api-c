#include "glite/ce/es-client-api-c/ActivityDescription.h"


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
wr::ActivityDescription::ActivityDescription( ActivityIdentification* act,
					      const Application& appl,
					      Resources* res,
					      DataStaging* datas )
{
  if( act )
    ActivityIdentificationField = new ActivityIdentification( *act );
  else
    ActivityIdentificationField = 0;
								     
  ApplicationField = new Application( appl );
 
  if( res ) 
    ResourcesField = new Resources( *res );
  else
    ResourcesField = 0;
  
  if( datas )
    DataStagingField = new DataStaging( *datas );
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
wr::ActivityDescription::set( const ActivityDescription& src )
{ 
  ActivityIdentificationField  = 0;
  ApplicationField             = 0;
  ResourcesField               = 0;
  DataStagingField             = 0;

  if( src.ActivityIdentificationField )
    ActivityIdentificationField 
      = new ActivityIdentification( *((ActivityIdentification*)src.ActivityIdentificationField) );
  
  if( src.ApplicationField )
    ApplicationField 
      = new Application( *((Application*)src.ApplicationField) );
  
  if( src.ResourcesField )
    ResourcesField 
      = new Resources( *((Resources*)src.ResourcesField) );
  
  if( src.DataStagingField )
    DataStagingField 
      = new DataStaging( *((DataStaging*)src.DataStagingField) );
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::ActivityDescription::ActivityDescription( const ActivityDescription& src )
  : ActivityDescriptionType()
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
wr::ActivityDescription::free( )
{
  ActivityIdentification* ai = (ActivityIdentification*)ActivityIdentificationField;
  Application *app           = (Application *)ApplicationField;
  Resources *res             = (Resources *)ResourcesField;
  DataStaging *ds            = (DataStaging *)DataStagingField;

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
wr::ActivityDescription::toString( const bool tabbed ) const
{ 
  ActivityIdentification* ai = (ActivityIdentification*)ActivityIdentificationField;
  Application *app           = (Application *)ApplicationField;
  Resources *res             = (Resources *)ResourcesField;
  DataStaging *ds            = (DataStaging *)DataStagingField;

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

