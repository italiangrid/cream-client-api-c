#ifndef EMIES_CLIENTLIB_XML_DESERRESRUNENV_H
#define EMIES_CLIENTLIB_XML_DESERRESRUNENV_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <string>

#include <boost/lexical_cast.hpp>

#include "glite/ce/es-client-api-c/RuntimeEnvironment.h"

namespace emi_es {
  namespace client {
    namespace xml {
      
      class XMLDoc;

      class DeserializeResourcesRuntimeEnvironment {
	
	friend class DeserializeResources;
      
protected:     
	static void get( XMLDoc*, std::vector<wrapper::RuntimeEnvironment>&, const int );
      };

    }
  }
}

#endif
