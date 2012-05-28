#include "glite/ce/es-client-api-c/util.h"

#include <boost/scoped_ptr.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>


using namespace std;

/**
 *
 *
 *
 *
 *
 *
 */
std::string 
emi_es::client::util::time_to_string( time_t tval ) {
  char buf[26]; // ctime_r wants a buffer of at least 26 bytes
  ctime_r( &tval, buf );
  if(buf[strlen(buf)-1] == '\n')
    buf[strlen(buf)-1] = '\0';
  return std::string( buf );
}

/**
 *
 *
 *
 *
 *
 *
 */
time_t
emi_es::client::util::string_to_time( const string& date )
{  
  string buf = date;
  boost::trim( buf );
  vector<string> pieces;
  boost::split(pieces, buf, boost::is_any_of("T"));

  if(pieces.size()!=2) 
    return 0;
  
  string Date = pieces[0];
  string Time = pieces[1];

  vector<string> date_pieces;
  boost::split( date_pieces, Date, boost::is_any_of("-"));

  if(date_pieces.size()!=3)
    return 0;

  struct tm T;
  T.tm_year = atoi( date_pieces[0].c_str() ) - 1900;
  T.tm_mon  = atoi( date_pieces[1].c_str() ) -1;
  T.tm_mday = atoi( date_pieces[2].c_str() );

  /**
   * let's remove trailing 'Z'
   */ 
  Time = Time.substr( 0, Time.length()-1 );
  
  vector<string> time_pieces;
  boost::split( time_pieces, Time, boost::is_any_of(":"));

  if(time_pieces.size()!=3)
    return 0;
  
  T.tm_hour = atoi( time_pieces[0].c_str() );
  T.tm_min  = atoi( time_pieces[1].c_str() );
  T.tm_sec  = atoi( time_pieces[2].c_str() );

  return mktime( &T );
}
