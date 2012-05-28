#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"

using namespace std;
namespace xml = emi_es::client::xml;

/**
 *
 *
 *
 *
 *
 *
 */
string*
xml::XMLGetNodeContent::get( XMLDoc* doc, const char* xpath_expr ) {
  xmlChar* xpathExpr = (xmlChar*)xpath_expr;
  xmlXPathObject* pathObj;
  pathObj = xmlXPathEvalExpression(xpathExpr, doc->context() );
  if( !pathObj->nodesetval ) {
    xmlXPathFreeObject(pathObj);
    return 0;
  }
  if(!pathObj->nodesetval->nodeNr) {
    xmlXPathFreeObject(pathObj);
    return 0;
  } else {
    char *content = (char*)xmlNodeGetContent(pathObj->nodesetval->nodeTab[0]);
    string* retval = new string(content);
    free(content);
    xmlXPathFreeObject(pathObj);
    return retval;
  }
}
