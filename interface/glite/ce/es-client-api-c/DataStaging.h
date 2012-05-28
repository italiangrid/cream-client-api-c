#ifndef EMIES_CLIENTLIB_WRAPPERS_DS_H
#define EMIES_CLIENTLIB_WRAPPERS_DS_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/InputFile.h"
#include "glite/ce/es-client-api-c/OutputFile.h"

namespace emi_es {
  namespace client {
    namespace wrapper {
	
	class DataStaging : public DataStagingType
	{
	
	private:
	  DataStaging( ) : DataStagingType( ) {}
	  
	public:
	  DataStaging( const bool _ClientDataPush,
		       const std::vector<InputFile>& _InputFiles,
		       const std::vector<OutputFile>& _OutputFiles);
	  
	  virtual ~DataStaging( ) { this->free( ); }
	  DataStaging( const DataStaging& );
	    
	  std::string toString( const bool tabbed = false ) const;

	private:
	  void set( const DataStaging& );
	  void free( ) ;
	  DataStaging& operator=( const DataStaging& ) { return *this; }
	};
	
    }
  }
}

#endif
