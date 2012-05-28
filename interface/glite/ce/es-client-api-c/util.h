#ifndef ES_CLIENT_UTIL
#define ES_CLIENT_UTIL

#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <ctime>
#include <sys/time.h>

namespace emi_es {
  namespace client {
    namespace util {

      template< typename T> std::string 
	join( const std::vector<T>& array, const std::string& sep)
	{
	  std::string joinstring( "" );
	  if ( array.size() != 0 ) {
	    joinstring += boost::lexical_cast<std::string>(array[0]);
	  } else {
	    return "";
	  }
	  
	  for( unsigned int j = 1 ; j < array.size(); ++j )
	    joinstring += sep + boost::lexical_cast<std::string>(array[j]);
	  
	  return joinstring;
	};

      std::string time_to_string( time_t tval );
      time_t      string_to_time( const std::string& );
      
      class GetRandom {    
	public:
	static int get_random( const int max) {
	  struct timeval tv;
	  gettimeofday( &tv, 0 );
	  srand( tv.tv_usec );
	  double R = (double)(((double)rand())/((double)RAND_MAX));
	  return (int)(R*(double)max);
	}
      };
      
    }
  }
}

#endif
