#include "glite/ce/es-client-api-c/WExecutable.h"
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
wr::WExecutable::WExecutable( const string& path,
	  	              const vector<std::string>& args,
		              int* failifexitcode )
{
  Path = path;
  Argument = args;
  FailIfExitCodeNotEqualTo = 0;
  if( failifexitcode ) {
    FailIfExitCodeNotEqualTo = new int;
    *FailIfExitCodeNotEqualTo = *failifexitcode;
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
void
wr::WExecutable::free( )
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
wr::WExecutable::set( const WExecutable& src )
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
wr::WExecutable::WExecutable( const WExecutable& src )
  : ExecutableType()
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
wr::WExecutable::toString( const bool tabbed ) const 
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
