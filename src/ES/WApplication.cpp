#include "glite/ce/es-client-api-c/WApplication.h"

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
 wr::WApplication::WApplication(  const WExecutable* exe,
				  string* in,
				  string* out,
				  string* err,
		     		  const vector<OptionType>& env,
		     		  const vector<WExecutable>& preexe,
		     		  const vector<WExecutable>& postexe,
		     		  const vector<WRemoteLogging>& rm,
				  OptionalTime* exptime,
				  OptionalTime* wipetime,
		     		  const vector<WNotification>& notif )
{
  if( exe )
    Executable = new WExecutable( *exe );
  else
    Executable = 0;

  if(in)
    Input = new string( *in );
  else
    Input = 0;

  if( out )
    Output = new string( *out );
  else
    Output = 0;
  
  if( err ) 
    Error = new string( *err );
  else 
    Error = 0;
  
  vector<OptionType>::const_iterator eit = env.begin( );
  for( ; eit != env.end( ); ++eit ) 
  {
    OptionType* opt = new OptionType();
    opt->Name = eit->Name;
    opt->Value = eit->Value;
    EnvironmentField.push_back( opt );
  }
  
  vector<WExecutable>::const_iterator exeit1 = preexe.begin( );
  for( ; exeit1 != preexe.end( ); ++exeit1 )
  {
    WExecutable *exe = new WExecutable( *exeit1 );
    
    PreExecutable.push_back( exe );
  }
  
  vector<WExecutable>::const_iterator exeit2 = postexe.begin( );
  for( ; exeit2 != postexe.end( ); ++exeit2 )
  {
    WExecutable *exe = new WExecutable( *exeit2 );
    
    PostExecutable.push_back( exe );
  }
  
  vector<WRemoteLogging>::const_iterator rmit = rm.begin( );
  for( ; rmit != rm.end( ); ++rmit )
  {
    WRemoteLogging *remotel = new WRemoteLogging( *rmit );
    RemoteLoggingField.push_back( remotel );
  }
  
  if(exptime) {
    ExpirationTime = new OptionalTime();
    ExpirationTime->__item = exptime->__item;
    ExpirationTime->optional = exptime->optional;
  } else ExpirationTime = 0;
    
  if(wipetime) {
    WipeTime = new OptionalTime();
    WipeTime->__item = wipetime->__item;
    WipeTime->optional = wipetime->optional;
  } else WipeTime = 0;
  
  vector<WNotification>::const_iterator nit = notif.begin( );
  for( ; nit != notif.end( ); ++nit )
  {
    WNotification *notification = new WNotification( *nit );
    NotificationField.push_back( notification );						  
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
wr::WApplication::set( const WApplication& appl ) 
{
  Executable = 0;
  Input = 0;
  Output = 0;
  Error = 0;
  ExpirationTime = 0;
  WipeTime = 0;
  
  if( appl.Executable )
    Executable = new WExecutable( (const WExecutable&)*appl.Executable );
  
  if( appl.Input )
    Input  = new string( *appl.Input );

  if( appl.Output )
    Output = new string( *appl.Output );

  if( appl.Error )
    Error  = new string( *appl.Error );
  
  vector<OptionType*>::const_iterator eit = appl.EnvironmentField.begin( );
  for( ; eit != appl.EnvironmentField.end( ); ++eit ) 
  {
    OptionType *opt = new OptionType();
    opt->Name = (*eit)->Name;
    opt->Value = (*eit)->Value;
    EnvironmentField.push_back( opt );
  }
  
  vector<ExecutableType*>::const_iterator exeit1 = appl.PreExecutable.begin( );
  for( ; exeit1 != appl.PreExecutable.end( ); ++exeit1 )
  {
    WExecutable *exe = new WExecutable( (const WExecutable&)**exeit1 );
    PreExecutable.push_back( exe );
  }
  
  vector<ExecutableType*>::const_iterator exeit2 = appl.PostExecutable.begin( );
  for( ; exeit2 != appl.PostExecutable.end( ); ++exeit2 )
  {
    WExecutable *exe = new WExecutable( (const WExecutable&)**exeit2 );
    
    PostExecutable.push_back( exe );
  }
  
  vector<RemoteLogging*>::const_iterator rmit = appl.RemoteLoggingField.begin( );
  for( ; rmit != appl.RemoteLoggingField.end( ); ++rmit )
  {
    WRemoteLogging *remotel = new WRemoteLogging( (const WRemoteLogging&)**rmit );
    RemoteLoggingField.push_back( remotel );
  }
  
  if( appl.ExpirationTime ) {
    ExpirationTime = new OptionalTime();
    ExpirationTime->__item = appl.ExpirationTime->__item;
    ExpirationTime->optional = appl.ExpirationTime->optional;
  }

  if( appl.WipeTime ) {
    WipeTime = new OptionalTime();
    WipeTime->__item = appl.WipeTime->__item;
    WipeTime->optional = appl.WipeTime->optional;
  }

  vector<Notification*>::const_iterator nit = appl.NotificationField.begin( );
  for( ; nit != appl.NotificationField.end( ); ++nit )
  {
    WNotification *notification = new WNotification( (const WNotification&)**nit );
    NotificationField.push_back( notification );						  
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
wr::WApplication::WApplication( const WApplication& app )
  : Application()
{
  this->set( app );
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
wr::WApplication::free( )
{
  
  if(Executable) {
    WExecutable *todelete = (WExecutable*)Executable;
    delete todelete;
  }
  if(Input) delete Input;
  if(Output) delete Output;
  if(Error) delete Error;
  if(ExpirationTime) delete ExpirationTime;
  if(WipeTime) delete WipeTime;
  
  vector<OptionType*>::const_iterator eit = EnvironmentField.begin( );
  for( ; eit != EnvironmentField.end( ); ++eit ) 
    {
      delete *eit;
    }
  EnvironmentField.clear();
  
  vector<ExecutableType*>::const_iterator exeit1 = PreExecutable.begin( );
  for( ; exeit1 != PreExecutable.end( ); ++exeit1 )
    {
      WExecutable* current = (WExecutable*)*exeit1;
      delete current;
    }
  PreExecutable.clear();
  
  vector<ExecutableType*>::const_iterator exeit2 = PostExecutable.begin( );
  for( ; exeit2 != PostExecutable.end( ); ++exeit2 )
    {
      WExecutable* current = (WExecutable*)*exeit2;
      delete current;
    }
  PostExecutable.clear();

  vector<RemoteLogging*>::const_iterator rm = RemoteLoggingField.begin( );
  for( ; rm != RemoteLoggingField.end( ); ++rm )
    {
      WRemoteLogging *current = (WRemoteLogging*)*rm;
      delete current;
    }
  RemoteLoggingField.clear();
  
  vector<Notification*>::const_iterator nit = NotificationField.begin( );
  for( ; nit != NotificationField.end( ); ++nit )
    {
      WNotification* current = (WNotification*)*nit;
      delete current;
    }
  NotificationField.clear();
  
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
wr::WApplication::toString(const bool tabbed) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
  
  string out;
  out += tab + "Application:";
  out += tab + ((WExecutable*)Executable)->toString( );
  out += tab + "  Input=" + *Input;
  out += tab + "  Output=" + *Output;
  out += tab + "  Error=" + *Error;
  
  vector<ExecutableType*>::const_iterator it = PreExecutable.begin();
  for( ; it != PreExecutable.end(); ++it )
    {
      out += ((WExecutable*)*it)->toString( );
    }

  it = PostExecutable.begin();
  for( ; it != PostExecutable.end(); ++it )
    {
      out += ((WExecutable*)*it)->toString( );
    }
  {
    vector<RemoteLogging*>::const_iterator it = RemoteLoggingField.begin();
    for( ; it != RemoteLoggingField.end(); ++it )
      {
	out += ((WRemoteLogging*)*it)->toString( );
      }
  }

  {
    vector<Notification*>::const_iterator it = NotificationField.begin();
    for( ; it != NotificationField.end(); ++it )
      {
	out += ((WNotification*)*it)->toString();
      }
  }

  return out;
}
