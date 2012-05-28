#ifndef EMIES_CLIENTLIB_XML_DESERIFSOURCE_H
#define EMIES_CLIENTLIB_XML_DESERIFSOURCE_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

namespace emi_es {
  namespace client {

    namespace wrapper {
      class Source;
    }
    
    namespace xml {
      
      class XMLDoc;

      class DeserializeInputFileSource {
      
        friend class DeserializeInputFile;
      
      protected:
        static wrapper::Source* get( XMLDoc*, const int adPos, const int ifPos, const int index ); 
      };
      
    }
  }
}

#endif
