#include "glite/ce/es-client-api-c/ParallelEnvironment.h"
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
wr::ParallelEnvironment::ParallelEnvironment( const ParallelEnvironment& src )
  : _ESADL__ParallelEnvironment( )
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
wr::ParallelEnvironment::ParallelEnvironment( const string& _Type,
                             		      string* _Version,
                             		      ProcessesPerHost* perHost,
                             		      ThreadsPerProcess* perProc,
			     		      const vector<OptionType>& _Options )
{
  Type = _Type;
  if(_Version)
    Version = new string( *_Version );
  else
    Version = 0;

  if(perHost) {
    ProcessesPerHostField = new ProcessesPerHost();
    ProcessesPerHostField->__item = perHost->__item;
    ProcessesPerHostField->useSlotsPerHost = perHost->useSlotsPerHost;
  } else ProcessesPerHostField = 0;

  if(perProc) {
    ThreadsPerProcessField = new ThreadsPerProcess();
    ThreadsPerProcessField->__item = perProc->__item;
    ThreadsPerProcessField->useSlotsPerHost = perProc->useSlotsPerHost;
  } else ThreadsPerProcessField = 0;
  
  vector<OptionType>::const_iterator it = _Options.begin();
  for( ; it != _Options.end(); ++it ) {
  
    OptionType *opt = new OptionType();
    opt->Name = it->Name;
    opt->Value = it->Value;
  
    OptionField.push_back( opt ); 
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
wr::ParallelEnvironment::set( const ParallelEnvironment& src )
{
  //Type = 0;
  Version = 0;
  ProcessesPerHostField  = 0;
  ThreadsPerProcessField = 0;
  
//   if(src.Type) {
//     Type = new ParallelEnvironmentEnumerationType;
//     (*Type) = *src.Type;
//   }
  Type = src.Type;

  if(src.Version )
    Version = new string( *src.Version );
  
  if(src.ProcessesPerHostField){
    ProcessesPerHostField = new ProcessesPerHost;
    ProcessesPerHostField->__item = src.ProcessesPerHostField->__item;
    ProcessesPerHostField->useSlotsPerHost = src.ProcessesPerHostField->useSlotsPerHost;
  }

  if( src.ThreadsPerProcessField ) {
    ThreadsPerProcessField = new ThreadsPerProcess;
    ThreadsPerProcessField->__item = src.ThreadsPerProcessField->__item;
    ThreadsPerProcessField->useSlotsPerHost = src.ThreadsPerProcessField->useSlotsPerHost;
  }
  
  vector<OptionType*>::const_iterator it = src.OptionField.begin();
  for( ; it != src.OptionField.end(); ++it ) {
  
    OptionType *opt = new  OptionType();
    opt->Name = (*it)->Name;
    opt->Value = (*it)->Value;
  
    OptionField.push_back( opt ); 
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
wr::ParallelEnvironment::free( )
{
   delete Version;
   delete ProcessesPerHostField;
   delete ThreadsPerProcessField;

   vector<OptionType*>::const_iterator it = OptionField.begin();
   for( ; it != OptionField.end( ); ++it ) {
     delete( *it );
   }
   OptionField.clear();
}

/**
 *
 *
 *
 *
 *
 *
 */
vector<OptionType>
wr::ParallelEnvironment::getOptions( void ) const
{
  vector<OptionType*>::const_iterator it = OptionField.begin();
  vector<OptionType> dest;
  for( ; it != OptionField.end( ); ++it )
  {
    OptionType opt;
    opt.Name = (*it)->Name;
    opt.Value = (*it)->Value;
    dest.push_back( opt );
  }
  
  return dest;
}
