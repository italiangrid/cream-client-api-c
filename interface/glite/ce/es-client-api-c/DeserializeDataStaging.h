#ifndef EMIES_CLIENTLIB_XML_DESERDATASTA_H
#define EMIES_CLIENTLIB_XML_DESERDATASTA_H


#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

namespace emi_es {
  namespace client {
    
    class CreateActivityDescriptionFromXML;

    namespace wrapper {
	class DataStaging;
    }
    
    namespace xml {
      
      class XMLDoc;
      
      class DeserializeDataStaging {
	
        friend class emi_es::client::CreateActivityDescriptionFromXML;
      
      protected:
        static wrapper::DataStaging* get( XMLDoc*, const int ); 
	
      };
      
    }
  }
}

#endif
