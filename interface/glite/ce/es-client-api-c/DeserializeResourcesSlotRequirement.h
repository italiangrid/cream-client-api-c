#ifndef EMIES_CLIENTLIB_XML_DESERRESSLREQ_H
#define EMIES_CLIENTLIB_XML_DESERRESSLREQ_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <string>

namespace emi_es {
  namespace client {
  
    namespace wrapper {
      class WSlotRequirement;
    }
  
    namespace xml {
      
      class XMLDoc;

      class DeserializeResourcesSlotRequirement {
      
	friend class DeserializeResources;
      
      protected:
	static wrapper::WSlotRequirement* get( XMLDoc*, const int );
      };

    }
  }
}

#endif
