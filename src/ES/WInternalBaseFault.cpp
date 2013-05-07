#include "glite/ce/es-client-api-c/WInternalBaseFault.h"
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
wr::WInternalBaseFault::WInternalBaseFault( const string& message,
					    time_t* timestamp,
					    string* desc,
					    int* failcode )
{
  Message     = message;
  Timestamp   = 0;
  Description = 0;
  FailureCode = 0;
  
  if(timestamp) {
    Timestamp = new time_t;
    *Timestamp = *timestamp;
  }
  if(desc)
    Description = new string(*desc );
    
  if(failcode) {
    FailureCode = new int;
    *FailureCode = *failcode;
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
wr::WInternalBaseFault::set( const WInternalBaseFault& src )
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
wr::WInternalBaseFault::WInternalBaseFault( const WInternalBaseFault& src ) 
  : InternalBaseFault()
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
wr::WInternalBaseFault::free( )
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
wr::WInternalBaseFault::toString( const bool tabbed ) const
{

  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "Fault:";
  out += tab + "  Message=" + Message;
  out += tab + "  Timestamp=" + (Timestamp ? boost::lexical_cast<string>( *Timestamp ) : "N/A");
  out += tab + "  Description=" + (Description ? *Description : "N/A");
  out += tab + "  FailureCode=" + (FailureCode ? boost::lexical_cast<string>( *FailureCode ) : "N/A");
  
  return out;
}
