#ifndef EMIES_CLIENTLIB_XML_DESERAPPEXEI_H
#define EMIES_CLIENTLIB_XML_DESERAPPEXEI_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <string>

namespace emi_es {
  namespace client {
  
    namespace wrapper {
      class WExecutable;
    }
  
    namespace xml {
      
      class XMLDoc;

      class DeserializeApplicationExecutable {
      
        friend class DeserializeApplication;
      
      protected:
        static wrapper::WExecutable* get( XMLDoc*, const int ); 
	
      };
      
    }
  }
}

#endif
