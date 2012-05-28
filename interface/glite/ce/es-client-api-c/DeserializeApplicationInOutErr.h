#ifndef EMIES_CLIENTLIB_XML_DESERAPPINOUTERR_H
#define EMIES_CLIENTLIB_XML_DESERAPPINOUTERR_H

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <string>

#include <boost/tuple/tuple.hpp>

namespace emi_es {
  namespace client {
    namespace xml {
      
      class XMLDoc;

      class DeserializeApplicationInOutErr {
      
        friend class DeserializeApplication;
      
      protected:
        static boost::tuple<std::string*, std::string*, std::string*> get( XMLDoc*, const int ); 
      };
      
    }
  }
}

#endif
