#include "glite/ce/es-client-api-c/ComputingActivityAssociations.h"
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
wr::ComputingActivityAssociations::ComputingActivityAssociations( 
const string& _UserDomainID,
//const string& _ComputingEndpointID,
const string& _ComputingShareID,
const string& _ExecutionEnvironmentID,
const vector<string>& IDs
)
{
  UserDomainID           = new string( _UserDomainID );
  //ComputingEndpointID    = new string( _ComputingEndpointID );
  ComputingShareID       = new string( _ComputingShareID );
  ExecutionEnvironmentID = new string( _ExecutionEnvironmentID );
  ActivityID             = IDs;
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
wr::ComputingActivityAssociations::set( const ComputingActivityAssociations& src )
{
  UserDomainID           = 0;
  //ComputingEndpointID    = 0;
  ComputingShareID       = 0;
  ExecutionEnvironmentID = 0;

  if(src.UserDomainID)
    UserDomainID = new string( *src.UserDomainID );

//   if(src.ComputingEndpointID)
//     ComputingEndpointID = new string(*src.ComputingEndpointID);

  if(src.ComputingShareID)
    ComputingShareID = new string(*src.ComputingShareID);

  if(src.ExecutionEnvironmentID)
    ExecutionEnvironmentID = new string(*src.ExecutionEnvironmentID);

  
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
wr::ComputingActivityAssociations::free( )
{
  delete UserDomainID;
  //delete ComputingEndpointID;
  delete ComputingShareID;
  delete ExecutionEnvironmentID;
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
wr::ComputingActivityAssociations::toString( const bool tabbed ) const
{

  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
  
  string out;
  if(UserDomainID)
    out += tab + "UserDomainID=" + *UserDomainID;
  else
    out += tab + "UserDomainID=N/A";

  //out += tab + "ComputingEndpointID=" + *ComputingEndpointID;
  if(ComputingShareID)
    out += tab + "ComputingShareID=" + *ComputingShareID;
  else
    out += tab + "ComputingShareID=N/A";

  if(ExecutionEnvironmentID)
    out += tab + "ExecutionEnvironmentID=" + *ExecutionEnvironmentID;
  else
    out += tab + "ExecutionEnvironmentID=N/A";

  return out;
}
