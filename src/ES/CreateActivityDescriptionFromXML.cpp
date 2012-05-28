#include "glite/ce/es-client-api-c/DeserializeActivityIdentification.h"
#include "glite/ce/es-client-api-c/CreateActivityDescriptionFromXML.h"
#include "glite/ce/es-client-api-c/ActivityIdentification.h"
#include "glite/ce/es-client-api-c/DeserializeApplication.h"
#include "glite/ce/es-client-api-c/DeserializeDataStaging.h"
#include "glite/ce/es-client-api-c/DeserializeResources.h"
#include "glite/ce/es-client-api-c/ActivityDescription.h"
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
client::CreateActivityDescriptionFromXML::create( const string& file, vector< pair<wrapper::ActivityDescription*, string> >& target ) throw(string)
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
    wrapper::Application* app = client::xml::DeserializeApplication::get( &doc, k );
    boost::scoped_ptr< wrapper::Application > app_safe_ptr( app );

    if(!app) {
      target.push_back( make_pair( (wrapper::ActivityDescription*)0, string("Missing <Application> tag in ActivityDescription #")+boost::lexical_cast<string>(k) ));
      continue;
    } else {
    
      wrapper::ActivityIdentification* ai = client::xml::DeserializeActivityIdentification::get( &doc, k );
      boost::scoped_ptr< wrapper::ActivityIdentification > ai_safe_ptr( ai );
      
      wrapper::DataStaging* DS = client::xml::DeserializeDataStaging::get( &doc, k );
      boost::scoped_ptr< wrapper::DataStaging > app_safe_ptr( DS );

      wrapper::Resources* R = client::xml::DeserializeResources::get( &doc, 1 );
      boost::scoped_ptr< wrapper::Resources > res_safe_ptr( R );

      wrapper::ActivityDescription* ad = new wrapper::ActivityDescription( ai, *app, R, DS );
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
client::CreateActivityDescriptionFromXML::free( vector< pair<wrapper::ActivityDescription*, string> >& toFree ) {
  vector<pair< wrapper::ActivityDescription*, string> >::const_iterator it = toFree.begin();
  for( ; it != toFree.end(); ++it ) {
    wrapper::ActivityDescription* current = it->first;
    delete current;
  }
}
