#include "glite/ce/es-client-api-c/InternalBaseFault.h"
#include <boost/lexical_cast.hpp>

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
wr::InternalBaseFault::InternalBaseFault( const string& message,
					  const time_t timestamp,
					  const string& desc,
					  const int failcode )
{
  Message = message;
  Timestamp = new time_t;
  *Timestamp = timestamp;
  Description = new string(desc );
  FailureCode = new int;
  *FailureCode = failcode;
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
wr::InternalBaseFault::set( const InternalBaseFault& src )
{
  Timestamp = 0;
  Description = 0;
  FailureCode = 0;

  Message = src.Message;

  if( src.Timestamp ) {
    Timestamp = new time_t;
    *Timestamp = *src.Timestamp;
  }

  if( src.Description ) {
    Description = new string( *src.Description );
  }
  
  if( src.FailureCode ) {
    FailureCode = new int;
    *FailureCode = *src.FailureCode;
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
wr::InternalBaseFault::InternalBaseFault( const InternalBaseFault& src ) 
  : InternalBaseFaultType()
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
void
wr::InternalBaseFault::free( )
{
  delete Timestamp;
  delete Description;
  delete FailureCode;
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
wr::InternalBaseFault::toString( const bool tabbed ) const
{

  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "Message=" + Message;
  out += tab + "Timestamp=" + (Timestamp ? boost::lexical_cast<string>( *Timestamp ) : "N/A");
  out += tab + "Description=" + (Description ? *Description : "N/A");
  out += tab + "FailureCode=" + (FailureCode ? boost::lexical_cast<string>( *FailureCode ) : "N/A");
  
  return out;
}
