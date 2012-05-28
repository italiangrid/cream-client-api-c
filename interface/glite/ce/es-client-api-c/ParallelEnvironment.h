#ifndef EMIES_CLIENTLIB_WRAPPERS_PE_H
#define EMIES_CLIENTLIB_WRAPPERS_PE_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"
#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class ParallelEnvironment : public ParallelEnvironmentType
      {
      private:
        ParallelEnvironment( ) : ParallelEnvironmentType( ) { }
	  
      public:
	ParallelEnvironment( const std::string& _Type,
			     std::string* _Version,
			     ProcessesPerHost*,
			     ThreadsPerProcess*,
			     const std::vector<OptionType>& _Options );
	
	std::vector<OptionType> getOptions( ) const;		
	
	virtual ~ParallelEnvironment( ) { this->free( ); }
	ParallelEnvironment( const ParallelEnvironment& );
	
	//std::string toString( const bool tabbed = false ) const;
	
      private:
	void free( );
	void set( const ParallelEnvironment& );
	ParallelEnvironment& operator=( const ParallelEnvironment& ) { return *this;}
	
      };
      
    }
  }
}

#endif
