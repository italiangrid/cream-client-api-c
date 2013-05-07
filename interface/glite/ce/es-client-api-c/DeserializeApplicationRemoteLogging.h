#ifndef EMIES_CLIENTLIB_XML_DESERAPPRL_H
#define EMIES_CLIENTLIB_XML_DESERAPPRL_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <vector>

#include "glite/ce/es-client-api-c/WRemoteLogging.h"

namespace emi_es {
  namespace client {
    namespace xml {
      
      class XMLDoc;

      class DeserializeApplicationRemoteLogging {
      
        friend class DeserializeApplication;
      
      protected:
        static void get( XMLDoc*, std::vector<wrapper::WRemoteLogging>&, const int ); 
	
      };
      
    }
  }
}

#endif
