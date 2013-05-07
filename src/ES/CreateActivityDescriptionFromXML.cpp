#include "glite/ce/es-client-api-c/DeserializeActivityIdentification.h"
#include "glite/ce/es-client-api-c/CreateActivityDescriptionFromXML.h"
#include "glite/ce/es-client-api-c/WActivityIdentification.h"
#include "glite/ce/es-client-api-c/DeserializeApplication.h"
#include "glite/ce/es-client-api-c/DeserializeDataStaging.h"
#include "glite/ce/es-client-api-c/DeserializeResources.h"
#include "glite/ce/es-client-api-c/WActivityDescription.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"

#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/operations.hpp>

#include <fstream>

using namespace std;
namespace client = emi_es::client;
namespace wrapper = emi_es::client::wrapper;


/**
 *
 *
 *
 *
 *
 *
 */
void
client::CreateActivityDescriptionFromXML::create( const string& file, vector< pair<wrapper::WActivityDescription*, string> >& target ) throw(string)
{
  if(!boost::filesystem::exists(file))
    throw string("File ") + file + " does not exist";

  ifstream infile(file.c_str());
  if(!infile) {
    throw string("File ") + file + " does exist but cannot be read; check file's permissions";
  }
  //is.close();
  
  client::xml::XMLDoc doc( file );
  
  if(!doc.is_valid()) 
    throw doc.error();

  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription" );
  int actCount = client::xml::XMLGetNodeCount::get( &doc, buf );
  if(!actCount)
    throw string("Missing <ActivityDescription> tag in XML file ") + file;
    
  for( int k = 1; k <= actCount; ++k )
  {
    wrapper::WApplication* app = client::xml::DeserializeApplication::get( &doc, k );
    boost::scoped_ptr< wrapper::WApplication > app_safe_ptr( app );

    if(!app) {
      target.push_back( make_pair( (wrapper::WActivityDescription*)0, string("Missing <Application> tag in ActivityDescription #")+boost::lexical_cast<string>(k) ));
      continue;
    } else {
    
      wrapper::WActivityIdentification* ai = client::xml::DeserializeActivityIdentification::get( &doc, k );
      boost::scoped_ptr< wrapper::WActivityIdentification > ai_safe_ptr( ai );
      
      wrapper::WDataStaging* DS = client::xml::DeserializeDataStaging::get( &doc, k );
      boost::scoped_ptr< wrapper::WDataStaging > app_safe_ptr( DS );

      wrapper::WResources* R = client::xml::DeserializeResources::get( &doc, 1 );
      boost::scoped_ptr< wrapper::WResources > res_safe_ptr( R );

      wrapper::WActivityDescription* ad = new wrapper::WActivityDescription( ai, app, R, DS );
      target.push_back( make_pair( ad, "" ) );
    }
    
    
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
client::CreateActivityDescriptionFromXML::free( vector< pair<wrapper::WActivityDescription*, string> >& toFree ) {
  vector<pair< wrapper::WActivityDescription*, string> >::const_iterator it = toFree.begin();
  for( ; it != toFree.end(); ++it ) {
    wrapper::WActivityDescription* current = it->first;
    delete current;
  }
}
