#ifndef EMIES_CLIENTLIB_XML_XMLCHECKSYNTAX_H
#define EMIES_CLIENTLIB_XML_XMLCHECKSYNTAX_H

#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/xpath.h>
#include <libxml2/libxml/xpathInternals.h>
#include <string>

namespace emi_es {
  namespace client {
  
    class CreateActivityDescriptionFromXML;
  
    namespace xml {

      class XMLDoc {

	friend class XMLGetNodeContent;
	friend class XMLGetNodeCount;
	friend class XMLGetMultipleNodeContent;
        friend class emi_es::client::CreateActivityDescriptionFromXML;
	
	xmlXPathContext*  m_context;
	xmlDoc*           m_doc;
	bool              m_valid;
	std::string       m_error;
	
      protected:
	XMLDoc( const std::string& );
	~XMLDoc( );

	bool is_valid( ) const { return m_valid; }
	std::string error( ) const { return m_error; }

	xmlXPathContext* context( ) const { return m_context; }

      };

    }
  }
}
	
#endif
