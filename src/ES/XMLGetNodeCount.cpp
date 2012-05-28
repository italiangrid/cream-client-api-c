#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
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
int
xml::XMLGetNodeCount::get( XMLDoc* doc, const char* xpath_expr ) {
  xmlChar* xpathExpr = (xmlChar*)xpath_expr;
  xmlXPathObject* pathObj;
  pathObj = xmlXPathEvalExpression(xpathExpr, doc->context() );
  if( !pathObj->nodesetval ) {
    xmlXPathFreeObject(pathObj);
    return 0;
  }
  int retval = pathObj->nodesetval->nodeNr;
  xmlXPathFreeObject(pathObj);
  return retval;
}
