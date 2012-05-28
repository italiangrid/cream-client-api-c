#ifndef EMIES_CLIENTLIB_XML_DESERRESOPSYS_H
#define EMIES_CLIENTLIB_XML_DESERRESOPSYS_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <string>

#include "glite/ce/es-client-api-c/OperatingSystem.h"

namespace emi_es {
  namespace client {
    namespace xml {
      
      class XMLDoc;

      class DeserializeResourcesOperatingSystem {
      
	friend class DeserializeResources;
      
      protected:
	static void get( XMLDoc*, std::vector<wrapper::OperatingSystem>&, const int );
      };

    }
  }
}

#endif
