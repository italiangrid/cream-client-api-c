#ifndef EMIES_CLIENTLIB_XML_DESERRESPE_H
#define EMIES_CLIENTLIB_XML_DESERRESPE_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <string>

//#include "glite/ce/es-client-api-c/WParallelEnvironment.h"

namespace emi_es {
  namespace client { 

    namespace wrapper {
      class WParallelEnvironment;
    }
    
    namespace xml {
      
      class XMLDoc;

      class DeserializeResourcesParallelEnvironment {
      
	friend class DeserializeResources;
      
      protected:
	static wrapper::WParallelEnvironment* get( XMLDoc*, const int );
      };

    }
  }
}

#endif
