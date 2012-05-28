#include "glite/ce/es-client-api-c/Application.h"

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
 wr::Application::Application(  const ExecutableType* exe,
				string* in,
				string* out,
				string* err,
		     		const vector<OptionType>& env,
		     		const vector<ExecutableType>& preexe,
		     		const vector<ExecutableType>& postexe,
		     		const vector<RemoteLoggingWrapper>& rm,
				OptionalTime* exptime,
				OptionalDuration* wipetime,
		     		const vector<Notification>& notif )
{
  if( exe )
    Executable = new ExecutableType( *exe );
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
  
  vector<ExecutableType>::const_iterator exeit1 = preexe.begin( );
  for( ; exeit1 != preexe.end( ); ++exeit1 )
  {
    ExecutableType *exe = new ExecutableType( *exeit1 );
    
    PreExecutable.push_back( exe );
  }
  
  vector<ExecutableType>::const_iterator exeit2 = postexe.begin( );
  for( ; exeit2 != postexe.end( ); ++exeit2 )
  {
    ExecutableType *exe = new ExecutableType( *exeit2 );
    
    PostExecutable.push_back( exe );
  }
  
  vector<RemoteLoggingWrapper>::const_iterator rmit = rm.begin( );
  for( ; rmit != rm.end( ); ++rmit )
  {
    RemoteLoggingWrapper *remotel = new RemoteLoggingWrapper( *rmit );
    RemoteLoggingField.push_back( remotel );
  }
  
  if(exptime) {
    ExpirationTime = new OptionalTime();
    ExpirationTime->__item = exptime->__item;
    ExpirationTime->optional = exptime->optional;
  } else ExpirationTime = 0;
    
  if(wipetime) {
    WipeTime = new OptionalDuration();
    WipeTime->__item = wipetime->__item;
    WipeTime->optional = wipetime->optional;
  } else WipeTime = 0;
  
  vector<Notification>::const_iterator nit = notif.begin( );
  for( ; nit != notif.end( ); ++nit )
  {
    Notification *notification = new Notification( *nit );
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
wr::Application::set( const Application& appl ) 
{
  Executable = 0;
  Input = 0;
  Output = 0;
  Error = 0;
  ExpirationTime = 0;
  WipeTime = 0;
  
  if( appl.Executable )
    Executable = new ExecutableType( (const ExecutableType&)*appl.Executable );
  
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
  
  vector<ExecutableClassType *>::const_iterator exeit1 = appl.PreExecutable.begin( );
  for( ; exeit1 != appl.PreExecutable.end( ); ++exeit1 )
  {
    ExecutableType *exe = new ExecutableType( (const ExecutableType&)**exeit1 );
    PreExecutable.push_back( exe );
  }
  
  vector<ExecutableClassType *>::const_iterator exeit2 = appl.PostExecutable.begin( );
  for( ; exeit2 != appl.PostExecutable.end( ); ++exeit2 )
  {
    ExecutableType *exe = new ExecutableType( (const ExecutableType&)**exeit2 );
    
    PostExecutable.push_back( exe );
  }
  
  vector<RemoteLoggingType *>::const_iterator rmit = appl.RemoteLoggingField.begin( );
  for( ; rmit != appl.RemoteLoggingField.end( ); ++rmit )
  {
    RemoteLoggingWrapper *remotel = new RemoteLoggingWrapper( (const RemoteLoggingWrapper&)**rmit );
    RemoteLoggingField.push_back( remotel );
  }
  
  if( appl.ExpirationTime ) {
    ExpirationTime = new OptionalTime();
    ExpirationTime->__item = appl.ExpirationTime->__item;
    ExpirationTime->optional = appl.ExpirationTime->optional;
  }

  if( appl.WipeTime ) {
    WipeTime = new OptionalDuration();
    WipeTime->__item = appl.WipeTime->__item;
    WipeTime->optional = appl.WipeTime->optional;
  }

  vector<NotificationType *>::const_iterator nit = appl.NotificationField.begin( );
  for( ; nit != appl.NotificationField.end( ); ++nit )
  {
    Notification *notification = new Notification( (const Notification&)**nit );
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
wr::Application::Application( const Application& app )
  : ApplicationType()
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
wr::Application::free( )
{
  
  if(Executable) {
    ExecutableType *todelete = (ExecutableType *)Executable;
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
  
  vector<ExecutableClassType*>::const_iterator exeit1 = PreExecutable.begin( );
  for( ; exeit1 != PreExecutable.end( ); ++exeit1 )
    {
      ExecutableType* current = (ExecutableType*)*exeit1;
      delete current;
    }
  PreExecutable.clear();
  
  vector<ExecutableClassType*>::const_iterator exeit2 = PostExecutable.begin( );
  for( ; exeit2 != PostExecutable.end( ); ++exeit2 )
    {
      ExecutableType* current = (ExecutableType*)*exeit2;
      delete current;
    }
  PostExecutable.clear();

  vector<RemoteLoggingType*>::const_iterator rm = RemoteLoggingField.begin( );
  for( ; rm != RemoteLoggingField.end( ); ++rm )
    {
      RemoteLoggingWrapper *current = (RemoteLoggingWrapper *)*rm;
      delete current;
    }
  RemoteLoggingField.clear();
  
  vector<NotificationType*>::const_iterator nit = NotificationField.begin( );
  for( ; nit != NotificationField.end( ); ++nit )
    {
      Notification* current = (Notification*)*nit;
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
wr::Application::toString(const bool tabbed) const
{
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
  
  string out;
  out += tab + ((ExecutableType*)Executable)->toString( );
  out += tab + "Input=" + *Input;
  out += tab + "Output=" + *Output;
  out += tab + "Error=" + *Error;
  
  vector<ExecutableClassType*>::const_iterator it = PreExecutable.begin();
  for( ; it != PreExecutable.end(); ++it )
    {
      out += ((ExecutableType*)*it)->toString( );
    }

  it = PostExecutable.begin();
  for( ; it != PostExecutable.end(); ++it )
    {
      out += ((ExecutableType*)*it)->toString( );
    }
  {
    vector<RemoteLoggingType*>::const_iterator it = RemoteLoggingField.begin();
    for( ; it != RemoteLoggingField.end(); ++it )
      {
	out += ((RemoteLoggingWrapper*)*it)->toString( );
      }
  }

  {
    vector<NotificationType*>::const_iterator it = NotificationField.begin();
    for( ; it != NotificationField.end(); ++it )
      {
	out += ((Notification*)*it)->toString();
      }
  }

  return out;
}
