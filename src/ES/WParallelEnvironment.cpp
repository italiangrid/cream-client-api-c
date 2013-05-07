#include "glite/ce/es-client-api-c/WParallelEnvironment.h"
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
wr::WParallelEnvironment::WParallelEnvironment( const WParallelEnvironment& src )
  : ParallelEnvironment( )
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
wr::WParallelEnvironment::WParallelEnvironment( const string& _Type,
                             		        string* _Version,
                             		        ProcessesPerHost* perHost,
                             		        ThreadsPerProcess* perProc,
			     		        const vector<OptionType>& _Options )
{
  Type = _Type;
  Version = 0;
  ProcessesPerHostField = 0;
  ThreadsPerProcessField = 0;
  
  if(_Version)
    Version = new string( *_Version );

  if(perHost) {
    ProcessesPerHostField = new ProcessesPerHost();
    ProcessesPerHostField->__item = perHost->__item;
    ProcessesPerHostField->useSlotsPerHost = perHost->useSlotsPerHost;
  }

  if(perProc) {
    ThreadsPerProcessField = new ThreadsPerProcess();
    ThreadsPerProcessField->__item = perProc->__item;
    ThreadsPerProcessField->useSlotsPerHost = perProc->useSlotsPerHost;
  }
  
  vector<OptionType>::const_iterator it = _Options.begin();
  for( ; it != _Options.end(); ++it ) {
  
    OptionType *opt = new OptionType();
    opt->Name = it->Name;
    opt->Value = it->Value;
  
    OptionTypeField.push_back( opt ); 
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
wr::WParallelEnvironment::set( const WParallelEnvironment& src )
{
  Version = 0;
  ProcessesPerHostField  = 0;
  ThreadsPerProcessField = 0;
  
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
  
    OptionTypeField.push_back( opt ); 
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
wr::WParallelEnvironment::free( )
{
   delete Version;
   delete ProcessesPerHostField;
   delete ThreadsPerProcessField;

   vector<OptionType*>::const_iterator it = OptionField.begin();
   for( ; it != OptionTypeField.end( ); ++it ) {
     delete( *it );
   }
   OptionTypeField.clear();
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
wr::WParallelEnvironment::getOptions( vector<OptionType>& target ) const
{
  vector<OptionType*>::const_iterator it = OptionField.begin();

  for( ; it != OptionField.end( ); ++it )
  {
    OptionType opt;
    opt.Name = (*it)->Name;
    opt.Value = (*it)->Value;
    target.push_back( opt );
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
string
wr::WParallelEnvironment::toString( const bool tabbed ) const
{
  
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "ParallelEnvironment:";
  out += tab + "  Type=";
  out += Type;
  out += tab + "  Version=";
  out += (Version ? *Version : "N/A");
  out += tab + "  Procs per host=";
  out += (ProcessesPerHostField ? boost::lexical_cast<string>(ProcessesPerHostField->__item) : "N/A");
  out += tab + "  Threads per process=";
  out += (ThreadsPerProcessField ? boost::lexical_cast<string>(ThreadsPerProcessField->__item) : "N/A");
  return out;
}
