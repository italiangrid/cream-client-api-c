#ifndef EMIES_CLIENTLIB_XML_DESERAPPNOTIF_H
#define EMIES_CLIENTLIB_XML_DESERAPPNOTIF_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <vector>

#include "glite/ce/es-client-api-c/WNotification.h"

namespace emi_es {
  namespace client {
    namespace xml {
      
      class XMLDoc;

      class DeserializeApplicationNotification {
      
        friend class DeserializeApplication;
      
      protected:
        static void get( XMLDoc*, std::vector<wrapper::WNotification>&, const int ); 
	
      };
      
    }
  }
}

#endif
