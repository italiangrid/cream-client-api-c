#ifndef EMIES_CLIENTLIB_XML_DESERIF_H
#define EMIES_CLIENTLIB_XML_DESERIF_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <vector>

#include "glite/ce/es-client-api-c/WInputFile.h"

namespace emi_es {
  namespace client {
    namespace xml {
      
      class XMLDoc;
      
      class DeserializeInputFile {
      
	friend class DeserializeDataStaging;

      protected:
        static void get( XMLDoc*, std::vector<wrapper::WInputFile>&, const int adPos ); 
      };
      
    }
  }
}

#endif
