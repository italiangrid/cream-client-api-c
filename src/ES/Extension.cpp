#include "glite/ce/es-client-api-c/Extension.h"
#include "glite/ce/es-client-api-c/typedefs.h"
//#include <boost/lexical_cast.hpp>

using namespace std;

namespace wr = emi_es::client::wrapper;

/**
 *
 *
 *
 *
 *
 *
 */
wr::Extension::Extension(const std::string& localID, const std::string& key,
			 const std::string& value, const char* any )
{
  LocalID = localID;
  Key = key;
  Value = value;
  __any = (char*)malloc( any.length()+1);
  memset( (void*)__any, 0, any.length()+1);
  memcpy( (void*)__any, any, any.length() );
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
wr::Extension::set(const Extension& src )
{
  __any = 0;

  LocalID = src.LocalID;
  Key = src.Key;
  Value = src.Value;

  if(src.__any) {
    __any = (char*)malloc( strlen( src.__any ) + 1 );
    memset( (void*)__any, 0, strlen( src.__any ) + 1 );
    memcpy( (void*)__any, src.__any, strlen( src.__any ) );
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
wr::Extension::free( )
{
  if(__any)
    ::free( __any );
}
