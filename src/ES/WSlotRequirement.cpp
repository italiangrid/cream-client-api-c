#include "glite/ce/es-client-api-c/WSlotRequirement.h"

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
wr::WSlotRequirement::WSlotRequirement( const ULONG64 num, 
				        SlotRequirement_SlotsPerHost* _sl, 
				        bool* excl ) 
  : SlotRequirement( )
{
  NumberOfSlots = num;
  SlotsPerHost = 0;
  if(_sl) {
    SlotsPerHost = new SlotRequirement_SlotsPerHost( );
    SlotsPerHost->__item = _sl->__item;
    SlotsPerHost->useNumberOfSlots = _sl->useNumberOfSlots;
  }
  ExclusiveExecution = 0;
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
wr::WSlotRequirement::WSlotRequirement( const WSlotRequirement& src ) 
  : SlotRequirement()
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
wr::WSlotRequirement&
wr::WSlotRequirement::operator=( const WSlotRequirement& src )
{
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
wr::WSlotRequirement::set( const WSlotRequirement& src )
{
  SlotsPerHost = 0;
  ExclusiveExecution = 0;

  NumberOfSlots = src.NumberOfSlots;

  if( src.SlotsPerHost ) {
    SlotsPerHost = new SlotRequirement_SlotsPerHost( );
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
wr::WSlotRequirement::free() 
{
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
wr::WSlotRequirement::toString( const bool tabbed ) const
{

  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";
    
  string out;
  out += tab + "SlotRequirement:";
  out += tab + "  NumberOfSlots=";
  out += boost::lexical_cast<string>( NumberOfSlots );
  out += tab + "  SlotsPerHost.__item=";
  out += boost::lexical_cast<string>(SlotsPerHost->__item);
  out += tab + "  SlotsPerHost.useNumberOfSlots=";
  out += boost::lexical_cast<string>(SlotsPerHost->useNumberOfSlots);
  out += tab + "  ExclusiveExecution=";
  if(ExclusiveExecution)
    out += boost::lexical_cast<string>(*ExclusiveExecution);
  else 
    out += "N/A";
  
  return out;
}
