#include "glite/ce/es-client-api-c/DeserializeApplicationWipeTime.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"
#include "glite/ce/es-client-api-c/util.h"

#include <vector>

#include <boost/scoped_ptr.hpp>

using namespace std;
namespace xml = emi_es::client::xml;

//static ASN1_TIME *convtime_12(const string& data);
//static time_t convtime_1( const string& );

/**
 *
 *
 *
 *
 *
 *
 */
OptionalTime*
xml::DeserializeApplicationWipeTime::get( XMLDoc* doc, const int adIndex )
{
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );

  /**
   *
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/WipeTime", adIndex );
  string *Time = XMLGetNodeContent::get( doc, buf );
  if( !Time ) 
    return 0;
  boost::scoped_ptr< string > time_safe_ptr( Time );

  /**
   *
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/WipeTime/@optional", adIndex );
  string *Opt = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > opt_safe_ptr( Opt );

  bool _opt = false;
  if(Opt)
    if(*Opt == "true")
      _opt = true;

  OptionalTime *opt = new OptionalTime();
  if(Time)
    opt->__item = atoi(Time->c_str());
  opt->optional = _opt;
  return opt;
}

