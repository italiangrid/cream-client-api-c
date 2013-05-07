#ifndef EMIES_CLIENTLIB_XML_DESEROFTARGET_H
#define EMIES_CLIENTLIB_XML_DESEROFTARGET_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

namespace emi_es {
  namespace client {

    namespace wrapper {
      class WTarget;
    }
    
    namespace xml {
      
      class XMLDoc;

      class DeserializeOutputFileTarget {
      
        friend class DeserializeOutputFile;
      
      protected:
        static wrapper::WTarget* get( XMLDoc*, const int adPos, const int ifPos, const int index ); 
      };
      
    }
  }
}

#endif
