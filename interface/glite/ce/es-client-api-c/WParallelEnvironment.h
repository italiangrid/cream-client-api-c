#ifndef EMIES_CLIENTLIB_WRAPPERS_PE_H
#define EMIES_CLIENTLIB_WRAPPERS_PE_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"
#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class WParallelEnvironment : public ParallelEnvironment
      {
      private:
        WParallelEnvironment( ) : ParallelEnvironment( ) { }
	  
      public:
	WParallelEnvironment( const std::string& _Type,
			      std::string* _Version,
			      ProcessesPerHost*,
			      ThreadsPerProcess*,
			      const std::vector<OptionType>& _Options );
	
	void getOptions( std::vector<OptionType>& ) const;		
	
	virtual ~WParallelEnvironment( ) { this->free( ); }
	WParallelEnvironment( const WParallelEnvironment& );
	
	std::string toString( const bool tabbed = false ) const;
	
      private:
	void free( );
	void set( const WParallelEnvironment& );
	WParallelEnvironment& operator=( const WParallelEnvironment& ) { return *this; }
	
      };
      
    }
  }
}

#endif
