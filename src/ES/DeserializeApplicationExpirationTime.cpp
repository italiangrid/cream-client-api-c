#include "glite/ce/es-client-api-c/DeserializeApplicationExpirationTime.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/XMLGetNodeContent.h"
#include "glite/ce/es-client-api-c/XMLGetMultipleNodeContent.h"
#include "glite/ce/es-client-api-c/util.h"
//#include <openssl/pem.h>
#include <openssl/asn1.h>
#include <vector>

#include <boost/scoped_ptr.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>


using namespace std;
namespace xml = emi_es::client::xml;

//static ASN1_TIME *convtime_1(const string& data); 
//static time_t convtime_2( const string& );

/**
 *
 *
 *
 *
 *
 *
 */
OptionalTime*
xml::DeserializeApplicationExpirationTime::get( XMLDoc* doc, const int adIndex )
{
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );

  /**
   *
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/ExpirationTime", adIndex );
  string *Time = XMLGetNodeContent::get( doc, buf );
  if( !Time ) 
    return 0;
  boost::scoped_ptr< string > time_safe_ptr( Time );

  /**
   *
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application[1]/ExpirationTime/@optional", adIndex );
  string *Opt = XMLGetNodeContent::get( doc, buf );
  boost::scoped_ptr< string > opt_safe_ptr( Opt );

  bool _opt = false;
  if(Opt)
    if(*Opt == "true")
      _opt = true;

  OptionalTime *opt = new OptionalTime();
  
  opt->__item = util::string_to_time( *Time );
  opt->optional = _opt;
  return opt;
}

//______________________________________________________________________________
// static ASN1_TIME *convtime_1(const string& data)
// {
//   ASN1_TIME *t= ASN1_TIME_new();
// 
//   t->data   = (unsigned char *)(data.data());
//   t->length = data.size();
//   switch(t->length) {
//   case 10:
//     t->type = V_ASN1_UTCTIME;
//     break;
//   case 15:
//     t->type = V_ASN1_GENERALIZEDTIME;
//     break;
//   case 20:
//     t->type = V_ASN1_GENERALIZEDTIME;
//     break;
//   default:
//     ASN1_TIME_free(t);
//     return NULL;
//   }
//   return t;
// }

//______________________________________________________________________________
// static time_t convtime_2( const string& date ) {
//   //return 0;
  
//   string buf = date;
//   boost::trim( buf );
//   vector<string> pieces;
//   boost::split(pieces, buf, boost::is_any_of("T"));

//   if(!pieces.size()) return 0;

//   string Date = pieces[0];
//   string Time = pieces[1];

//   vector<string> date_pieces;
//   boost::split( date_pieces, Date, boost::is_any_of("-"));
  
//   struct tm T;
//   T.tm_year = atoi( date_pieces[0].c_str() ) - 1900;
//   T.tm_mon  = atoi( date_pieces[1].c_str() ) -1;
//   T.tm_mday = atoi( date_pieces[2].c_str() );

//   /**
//    * let's remove trailing 'Z'
//    */ 
//   Time = Time.substr( 0, Time.length()-1 );
  
//   vector<string> time_pieces;
//   boost::split( time_pieces, Time, boost::is_any_of(":"));



//   T.tm_hour = atoi( time_pieces[0].c_str() );
//   T.tm_min  = atoi( time_pieces[1].c_str() );
//   T.tm_sec  = atoi( time_pieces[2].c_str() );

//   return mktime( &T );

//   string buf = date;
//   boost::trim( buf );
//   if( boost::ends_with( buf, "Z" ) )
//     offset = 0;
//   else {
//     if ((*str != '+') && (str[5] != '-')) {
//       newtime = 0;
//     }
//     offset=((str[1]-'0')*10+(str[2]-'0'))*60;
//     offset+=(str[3]-'0')*10+(str[4]-'0');
//     if (*str == '-') {
//       offset=-offset;
//     }
//   }
//   char     *str;
//   time_t    offset;
//   time_t    newtime;
//   char      buff1[32];
//   char     *p;
//   int       i;
//   struct tm tm;
// 
//   static bool tzadjusted = false;
//   static int  tzcor = 0;
//   
//   p = buff1;
//   i = date.length();//ctm->length;
//   str = (char *)date.c_str();//data;
//   if ((i < 11) || (i > 17)) {
//     newtime = 0;
//   }
//   
//   memcpy(p,str,12);
//   p += 12;
//   str += 12;
// 
//   if ((*str == 'Z') || (*str == '-') || (*str == '+')) {
//     *(p++)='0'; *(p++)='0';
//   }
//   else {
//     *(p++)= *(str++); *(p++)= *(str++);
//   }
//   *(p++)='Z';
//   *(p++)='\0';
// 
//   if (*str == 'Z') {
//     offset=0;
//   }
//   else {
//     if ((*str != '+') && (str[5] != '-')) {
//       newtime = 0;
//     }
//     offset=((str[1]-'0')*10+(str[2]-'0'))*60;
//     offset+=(str[3]-'0')*10+(str[4]-'0');
//     if (*str == '-') {
//       offset=-offset;
//     }
//   }
// 
//   tm.tm_isdst = 0;
//   int index = 0;
//   tm.tm_year  = (buff1[index++]-'0')*1000;
//   tm.tm_year += (buff1[index++]-'0')*100;
//   tm.tm_year += (buff1[index++]-'0')*10;
//   tm.tm_year += (buff1[index++]-'0');
// 
//   if (tm.tm_year < 70) {
//     tm.tm_year+=100;
//   }
// 
//   if (tm.tm_year > 1900) {
//     tm.tm_year -= 1900;
//   }
// 
//   tm.tm_mon   = (buff1[index++]-'0')*10;
//   tm.tm_mon  += (buff1[index++]-'0')-1;
//   tm.tm_mday  = (buff1[index++]-'0')*10;
//   tm.tm_mday += (buff1[index++]-'0');
//   tm.tm_hour  = (buff1[index++]-'0')*10;
//   tm.tm_hour += (buff1[index++]-'0');
//   tm.tm_min   = (buff1[index++]-'0')*10;
//   tm.tm_min  += (buff1[index++]-'0');
//   tm.tm_sec   = (buff1[index++]-'0')*10;
//   tm.tm_sec  += (buff1[index++]-'0');
//   
//   newtime = mktime( &tm );
//   
//   if(!tzadjusted) {
// 
//     time_t now = time(0);
//     struct tm ltn, gtn;
//     if (!localtime_r(&now, &ltn))
//       return newtime;
//     if (!gmtime_r(&now, &gtn))
//       return newtime;
//     //
//     //
//     // Calculate correction
//     tzcor = ((ltn.tm_hour - gtn.tm_hour) +
//              (ltn.tm_mday - gtn.tm_mday) * 24) * 3600;
//     //
//     // We did it
//     tzadjusted=true;
//   }
// 
//   newtime += tzcor;
// 
//   return newtime;
//}
