#ifndef EMIES_CLIENTLIB_XML_DESERAPPENV_H
#define EMIES_CLIENTLIB_XML_DESERAPPENV_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <vector>

#include "glite/ce/es-client-api-c/typedefs.h"
#include "glite/ce/es-client-api-c/es_client_soapStub.h"

namespace emi_es {
  namespace client {
    namespace xml {
      
      class XMLDoc;

      class DeserializeApplicationEnvironment {
      
        friend class DeserializeApplication;
      
      protected:
        static void get( XMLDoc*, std::vector<OptionType>&, const int ); 
	
      };
      
    }
  }
}

#endif
