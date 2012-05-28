#ifndef EMIES_CLIENTLIB_XML_DESERAI_H
#define EMIES_CLIENTLIB_XML_DESERAI_H


#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <string>

namespace emi_es {
  namespace client {
 
    class CreateActivityDescriptionFromXML;
 
    namespace wrapper {
      class ActivityIdentification;
    }
  
    namespace xml {
      
      class XMLDoc;

      class DeserializeActivityIdentification {
      
        friend class emi_es::client::CreateActivityDescriptionFromXML;
      
      protected:
        static wrapper::ActivityIdentification* get( XMLDoc*, const int ); 
	
      };
      
    }
  }
}

#endif
