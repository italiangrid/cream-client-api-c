#include "glite/ce/es-client-api-c/DeserializeOutputFile.h"
#include "glite/ce/es-client-api-c/DeserializeOutputFileTarget.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"

#include <boost/scoped_ptr.hpp>

using namespace std;
namespace xml = emi_es::client::xml;
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
xml::DeserializeOutputFile::get( XMLDoc* doc, 
				 vector<wrapper::OutputFile>& target,
				 const int adPos )
{ 
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > classad_safe_ptr( buf );
  
  /**
   * Count # of OutputFile nodes
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/OutputFile", adPos );
  int count = XMLGetNodeCount::get( doc, buf );
  if(!count) return;
  
  /**
   * Load all the OutputFiles
   *
   */
  for( int k = 1; k <= count; ++k ) {
    vector<wrapper::Target> Targets;
    string Name;

    memset( (void*)buf, 0, 1024 );
    sprintf( buf, 
	     "//ActivityDescription[%d]/DataStaging/OutputFile[%d]/Name",
	     adPos, k );
    string *name = XMLGetNodeContent::get( doc, buf );
    if(!name)
      continue;
    else {
      Name = *name;
      delete name;
    }
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/DataStaging/OutputFile[%d]/Target", adPos, k );
    int countTarget = XMLGetNodeCount::get( doc, buf );
    
    /**
     * Load all the Targets
     */
    if(countTarget) {
      for( int j = 1; j <= countTarget; ++j ) {
	wrapper::Target *TGT = DeserializeOutputFileTarget::get( doc, adPos, k, j );
	if(TGT) {
	  Targets.push_back( *TGT );
	  delete TGT;
	}
      }
    }
    wrapper::OutputFile of(Name, Targets );
    target.push_back(of);
  }
}
