#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"

#include <cstring>

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
void
xml::XMLGetMultipleNodeContent::get( XMLDoc* doc, vector<string>& target, const char* xpath_expr ) {
  xmlChar* xpathExpr = (xmlChar*)xpath_expr;
  xmlXPathObject* pathObj;
  pathObj = xmlXPathEvalExpression(xpathExpr, doc->context() );
  int count = pathObj->nodesetval->nodeNr;
  xmlXPathFreeObject(pathObj);

  char buf[1024];
  for( int idx = 1; idx <= count; ++idx ) {
    ::memset((void*)buf, 0, 1024);
    sprintf( buf, "%s[%d]", xpath_expr, idx );
    xpathExpr = (xmlChar*)buf;
    pathObj = xmlXPathEvalExpression(xpathExpr, doc->context() );
    char *content = (char*)xmlNodeGetContent(pathObj->nodesetval->nodeTab[0]);
    target.push_back(content);
    free(content);
    xmlXPathFreeObject(pathObj);
  }
}
