#include "glite/ce/es-client-api-c/XMLDoc.h"
#include <iostream>

using namespace std;
namespace xml = emi_es::client::xml;

std::string globalerr = "";

void err_func(void* buf, xmlError* error) {
  globalerr = error->message;
}

/**
 *
 *
 *
 *
 *
 *
 */
xml::XMLDoc::XMLDoc( const string& filename )
  : m_context(0), m_doc( 0 ), m_valid(false), m_error("")
{
  //m_doc = xmlParseFile(filename.c_str());
  //void *error_report = malloc(2048);
  //xmlErrorPtr errPtr = 0;
  xmlSetStructuredErrorFunc(0, err_func);
  m_doc = xmlReadFile( filename.c_str(), 0, XML_PARSE_NOERROR|XML_PARSE_NOWARNING);
  if(!m_doc) {
    m_error = string("error parsing file ") + filename + ": " + globalerr;
    return;
  }

  m_context = xmlXPathNewContext(m_doc);
  if(!m_context) {
    m_error = string("error getting XMLPathContext for file ") + filename + ". Please check XML syntax.";
    return;
  }

  m_valid = true;
}

/**
 *
 *
 *
 *
 *
 *
 */
xml::XMLDoc::~XMLDoc( )
{
  if(m_context) xmlXPathFreeContext(m_context); 
  if(m_doc) xmlFreeDoc(m_doc); 

}
