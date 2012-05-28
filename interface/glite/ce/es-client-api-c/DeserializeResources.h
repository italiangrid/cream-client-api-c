#ifndef EMIES_CLIENTLIB_XML_DESERRES_H
#define EMIES_CLIENTLIB_XML_DESERRES_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <string>

namespace emi_es {
  namespace client {

    class CreateActivityDescriptionFromXML;

    namespace wrapper {
      class Resources;
    }

    namespace xml {
      
      class XMLDoc;

      class DeserializeResources {
      
	friend class emi_es::client::CreateActivityDescriptionFromXML;
      
      protected:
	static wrapper::Resources* get( XMLDoc*, const int );
      };

    }
  }
}

#endif
