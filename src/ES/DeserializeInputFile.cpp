#include "glite/ce/es-client-api-c/DeserializeInputFile.h"
#include "glite/ce/es-client-api-c/DeserializeInputFileSource.h"
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
xml::DeserializeInputFile::get( XMLDoc* doc, 
				vector<wrapper::WInputFile>& target,
				const int adPos )
{ 
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > classad_safe_ptr( buf );
  
  /**
   * Count # of InputFile nodes
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/DataStaging/InputFile", adPos );
  int count = XMLGetNodeCount::get( doc, buf );
  if(!count) return;

  /**
   * Load all the InputFiles
   *
   */
  for( int k = 1; k <= count; ++k ) {
    vector<wrapper::WSource> Sources;
    string Name;
    string *isExe = 0;

    /**
     * Get the name
     */
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, 
	     "//ActivityDescription[%d]/DataStaging/InputFile[%d]/Name",
	     adPos, k );
    string *name = XMLGetNodeContent::get( doc, buf );
    if(!name)
      continue;
    else {
      Name = *name;
      delete name;
    }
    
    /**
     * Get the IsExecutable flag
     */
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, 
	     "//ActivityDescription[%d]/DataStaging/InputFile[%d]/IsExecutable",
	     adPos, k );
    isExe = XMLGetNodeContent::get( doc, buf );

    /**
     * Count the # of Source tags
     */
    memset( (void*)buf, 0, 1024 );
    sprintf( buf, "//ActivityDescription[%d]/DataStaging/InputFile[%d]/Source", adPos, k );
    int countSource = XMLGetNodeCount::get( doc, buf );
    
    /**
     * Load all the Sources
     */
    if(countSource) {
      for( int j = 0; j <= countSource; ++j ) {
	wrapper::WSource *SRC = DeserializeInputFileSource::get( doc, adPos, k, j );
	if(SRC) {
	  Sources.push_back( *SRC );
	  delete SRC;
	}
      }
    }

    /**
     * Build up the InputFile object and put it into the vector
     */
    if(isExe) {
      if((*isExe) == "true") {
        bool _t_ = true;
	wrapper::WInputFile If( Name, Sources, &_t_ );
	target.push_back(If);
      } else {
        bool _t_ = false;
	wrapper::WInputFile If( Name, Sources, &_t_ );
	target.push_back(If);
      }
    } else {
      wrapper::WInputFile If( Name, Sources, 0 );
      target.push_back(If);
    }
    delete isExe;
  }
}
