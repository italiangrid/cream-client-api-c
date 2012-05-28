#ifndef EMIES_CLIENTLIB_XML_DESERAPP_H
#define EMIES_CLIENTLIB_XML_DESERAPP_H


#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

namespace emi_es {
  namespace client {

    class CreateActivityDescriptionFromXML;
  
    namespace wrapper {
      class Application;
    }
  
    namespace xml {
      
      class XMLDoc;

      class DeserializeApplication {
      
        friend class emi_es::client::CreateActivityDescriptionFromXML;
      
      protected:
        static wrapper::Application* get( XMLDoc*, const int ); 
	
      };
      
    }
  }
}

#endif
