#include "glite/ce/es-client-api-c/WActivityIdentification.h"
#include "glite/ce/es-client-api-c/util.h"

#include <boost/lexical_cast.hpp>

using namespace std;

namespace wr  = emi_es::client::wrapper;

char* wr::WActivityIdentification::ACTIVITYTYPE_STRING[] = {
  "COLLECTIONELEMENT",
  "PARALLELELEMENT",
  "SINGLE",
  "WORKFLOWNODE"
};

/**
 *
 *
 *
 *
 *
 *
 */
wr::WActivityIdentification::WActivityIdentification( string* name,
	  			  		      string* description,
				  		      ActivityTypeEnumeration *type,
				  		      const vector<string>& annotation )
 : ActivityIdentification( )
{
  Name        = 0;
  Description = 0;
  Type        = 0;
  if(name)
    Name = new string( *name );
  if(description)
    Description = new string( *description );
  if(type) {
    Type = new ActivityTypeEnumeration;
    (*Type) = *type;
  }
  Annotation = annotation;
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
wr::WActivityIdentification::set( const WActivityIdentification& src )
{
  Name        = 0;
  Description = 0;
  Type        = 0;

  if( src.Name )
    Name = new string( *src.Name );

  if( src.Description )
    Description = new string( *src.Description );
  
  if( src.Type ) {
    Type = new ActivityTypeEnumeration;
    (*Type) = *src.Type;
  }

  Annotation = src.Annotation;
}

/**
 *
 *
 *
 *
 *
 *
 */
wr::WActivityIdentification::WActivityIdentification( const WActivityIdentification& src )
  : ActivityIdentification()
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
wr::WActivityIdentification::free( )
{
  delete Name;
  delete Description;
  delete Type;
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
wr::WActivityIdentification::toString( const bool tabbed ) const
{  
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;
  out += tab + "ActivityIdentification:";
  out += tab + "  Name=" + (Name ? *Name : "N/A");
  out += tab + "  Description=" + (Description ? *Description : "N/A");
  out += tab + "  Type=" + (Type ?  ACTIVITYTYPE_STRING[ *Type ] : "N/A" );
  out += tab + "  Annotation={" + util::join( Annotation, ", " ) + "}";

  return out;
}
