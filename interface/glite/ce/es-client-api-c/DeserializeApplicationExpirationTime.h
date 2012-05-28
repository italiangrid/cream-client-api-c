#ifndef EMIES_CLIENTLIB_XML_DESERAPPLEXPTIME_H
#define EMIES_CLIENTLIB_XML_DESERAPPLEXPTIME_H


#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <string>

#include "glite/ce/es-client-api-c/typedefs.h"

namespace emi_es {
  namespace client {  
    namespace xml {
      
      class XMLDoc;

      class DeserializeApplicationExpirationTime {
      
        friend class DeserializeApplication;
      
      protected:
        static OptionalTime* get( XMLDoc*, const int );
      };
      
    }
  }
}

#endif
