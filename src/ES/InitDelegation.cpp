#include "glite/ce/es-client-api-c/InitDelegation.h"

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
wr::InitDelegation::InitDelegation( const string& _CredentialType,
				    string* _RenewalID,
				    const ULONG64 _InitDelegationLifetime )
{
  CredentialType = _CredentialType;
  if(_RenewalID)
    RenewalID = new string(*_RenewalID);
  else
    RenewalID = 0;
  InitDelegationLifetime = new ULONG64( _InitDelegationLifetime );
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
wr::InitDelegation::set(const InitDelegation& src )
{
  RenewalID = 0;
  InitDelegationLifetime = 0;

  CredentialType = src.CredentialType;
  
  if(src.RenewalID)
    RenewalID = new string(*src.RenewalID);
  
  if(src.InitDelegationLifetime)
    InitDelegationLifetime = new ULONG64( *src.InitDelegationLifetime );
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
wr::InitDelegation::free( )
{
  delete RenewalID;
  delete InitDelegationLifetime;
}
