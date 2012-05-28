#include "glite/ce/es-client-api-c/ExecutableType.h"
#include <boost/lexical_cast.hpp>
#include "glite/ce/es-client-api-c/util.h"

using namespace std;

namespace wr = emi_es::client::wrapper;
namespace util = emi_es::client::util;

/**
 *
 *
 *
 *
 *
 *
 */
wr::ExecutableType::ExecutableType( const string& path,
	  	            	    const vector<std::string>& args,
		           	    const int failifexitcode )
{
  Path = path;
  Argument = args;
  FailIfExitCodeNotEqualTo = new int;
  *FailIfExitCodeNotEqualTo = failifexitcode;
}
/**
 *
 *
 *
 *
 *
 *
 */
wr::ExecutableType::ExecutableType( const string& path,
                                    const vector<std::string>& args )
{
  Path = path;
  Argument = args;
  FailIfExitCodeNotEqualTo = 0;//new int;
}

/**
 *
 *
 *
 *
 *
 *
 */
void
wr::ExecutableType::free( )
{
  delete FailIfExitCodeNotEqualTo;
}

/**
 *
 *
 *
 *
 *
 *
 */
void
wr::ExecutableType::set( const ExecutableType& src )
{
  FailIfExitCodeNotEqualTo = 0;

  Path = src.Path;
  Argument = src.Argument;
  if( src.FailIfExitCodeNotEqualTo ) {
    FailIfExitCodeNotEqualTo = new int;//string( *src.FailIfExitCodeNotEqualTo );
    *FailIfExitCodeNotEqualTo =  *src.FailIfExitCodeNotEqualTo;
  }
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::ExecutableType::ExecutableType( const ExecutableType& src )
  : ExecutableClassType()
{
  this->set( src );
}

/**
 *
 *
 *
 *
 *
 *
 */
string
wr::ExecutableType::toString( const bool tabbed ) const 
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
  
  string out;
  out += tab + "Path=";
  out += Path;
  out += tab + "Argument={";
  out += util::join( Argument, ", " ) + "}";
  out += tab + "FailIfExitCodeNotEqualTo=";
  out += boost::lexical_cast<string>( FailIfExitCodeNotEqualTo ? *FailIfExitCodeNotEqualTo : 0 );

  return out;
}
