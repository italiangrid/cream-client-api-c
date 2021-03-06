#ifndef EMIES_CLIENTLIB_XML_DESEROF_H
#define EMIES_CLIENTLIB_XML_DESEROF_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <vector>

#include "glite/ce/es-client-api-c/OutputFile.h"

namespace emi_es {
  namespace client {
    namespace xml {
      
      class XMLDoc;
      
      class DeserializeOutputFile {
      
	friend class DeserializeDataStaging;

      protected:
        static void get( XMLDoc*, std::vector<wrapper::OutputFile>&, const int adPos ); 
      };
      
    }
  }
}

#endif
