#ifndef EMIES_CLIENTLIB_XML_GETMULTNODECONTENT_H
#define EMIES_CLIENTLIB_XML_GETMULTNODECONTENT_H

#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace xml {
      
      class XMLDoc;

      class XMLGetMultipleNodeContent {

	friend class DeserializeActivityIdentification;
	friend class DeserializeApplicationExecutable;
	friend class DeserializeApplicationNotification;
	friend class DeserializeApplicationPrePostExecutable;

      protected:
	static void get(XMLDoc* doc, std::vector<std::string>&, const char* xpath_expr );
      };
      
    }
  }
}


#endif
