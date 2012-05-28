#include "glite/ce/es-client-api-c/SlotRequirement.h"

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
wr::SlotRequirement::SlotRequirement( const ULONG64 num, 
				      SlotsPerHostType* _sl, 
				      bool* excl ) 
  : SlotRequirementType( )
{
  NumberOfSlots = num;
  SlotsPerHost = 0;
  if(_sl) {
    SlotsPerHost = new SlotsPerHostType( );
    SlotsPerHost->__item = _sl->__item;
    SlotsPerHost->useNumberOfSlots = _sl->useNumberOfSlots;
  }
  ExclusiveExecution = 0;//new bool;
  if( excl )
    ExclusiveExecution = new bool(excl);
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::SlotRequirement::SlotRequirement( const SlotRequirement& src ) 
  : SlotRequirementType()
{ 
  if(getenv("ES_CLIENT_DEBUG_CTOR") )
    cerr << "SlotRequirement::SlotRequirement EXECUTED" << endl;

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
wr::SlotRequirement&
wr::SlotRequirement::operator=( const SlotRequirement& src )
{
  if(getenv("ES_CLIENT_DEBUG_CTOR") )
    cerr << "SlotRequirement::operator= EXECUTED" << endl;

  this->free( );
  this->set( src );
  return *this;
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
wr::SlotRequirement::set( const SlotRequirement& src )
{
  SlotsPerHost = 0;
  ExclusiveExecution = 0;

  NumberOfSlots = src.NumberOfSlots;

  if( src.SlotsPerHost ) {
    SlotsPerHost = new SlotsPerHostType( );
    (*SlotsPerHost) = *src.SlotsPerHost;
  }
  
  if( src.ExclusiveExecution ) {
    ExclusiveExecution = new bool;
    (*ExclusiveExecution) = *src.ExclusiveExecution;
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
wr::SlotRequirement::free() 
{
  if(getenv("ES_CLIENT_DEBUG_DTOR") )
    cerr << "SlotRequirement::free EXECUTED" << endl;
  
  delete SlotsPerHost;
  delete ExclusiveExecution;
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
wr::SlotRequirement::toString( const bool tabbed ) const
{

  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
    
  string out;
  out += tab + "NumberOfSlots=";
  out += boost::lexical_cast<string>( NumberOfSlots );
  out += tab + "SlotsPerHost.__item=";
  out += boost::lexical_cast<string>(SlotsPerHost->__item);
  out += tab + "SlotsPerHost.useNumberOfSlots=";
  out += boost::lexical_cast<string>(SlotsPerHost->useNumberOfSlots);
  out += tab + "ExclusiveExecution=";
  if(ExclusiveExecution)
    out += boost::lexical_cast<string>(*ExclusiveExecution);
  else 
    out += "N/A";
  
  return out;
}
