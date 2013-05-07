#ifndef EMIES_CLIENTLIB_WRAPPERS_DS_H
#define EMIES_CLIENTLIB_WRAPPERS_DS_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/WInputFile.h"
#include "glite/ce/es-client-api-c/WOutputFile.h"

namespace emi_es {
  namespace client {
    namespace wrapper {
	
	class WDataStaging : public DataStaging
	{
	
	private:
	  WDataStaging( ) : DataStaging( ) {}
	  
	public:
	  WDataStaging( const bool _ClientDataPush,
		       const std::vector<WInputFile>& _InputFiles,
		       const std::vector<WOutputFile>& _OutputFiles);
	  
	  virtual ~WDataStaging( ) { this->free( ); }
	  WDataStaging( const WDataStaging& );
	    
	  std::string toString( const bool tabbed = false ) const;

	private:
	  void set( const WDataStaging& );
	  void free( ) ;
	  WDataStaging& operator=( const WDataStaging& ) { return *this; }
	};
	
    }
  }
}

#endif
