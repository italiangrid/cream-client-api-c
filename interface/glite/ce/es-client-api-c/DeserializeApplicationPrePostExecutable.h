#ifndef EMIES_CLIENTLIB_XML_DESERAPPPREPOSTEXE_H
#define EMIES_CLIENTLIB_XML_DESERAPPPREPOSTEXE_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <vector>

#include "glite/ce/es-client-api-c/WExecutable.h"

namespace emi_es {
  namespace client {
    namespace xml {
      
      class XMLDoc;
      //class DeserializeApplication;

      class DeserializeApplicationPrePostExecutable {
      
        friend class DeserializeApplication;
      
      protected:
        static void get( XMLDoc*, 
			 std::vector<wrapper::WExecutable>&, 
			 std::vector<wrapper::WExecutable>&, 
			 const int ); 
	
      };
      
    }
  }
}

#endif
