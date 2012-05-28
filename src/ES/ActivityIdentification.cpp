#include "glite/ce/es-client-api-c/ActivityIdentification.h"
#include "glite/ce/es-client-api-c/util.h"

#include <boost/lexical_cast.hpp>

using namespace std;

namespace wr  = emi_es::client::wrapper;

char* wr::ActivityIdentification::ACTIVITYTYPE_STRING[] = {
  "ACTIVITYTYPE_COLLECTIONELEMENT",
  "ACTIVITYTYPE_PARALLELELEMENT",
  "ACTIVITYTYPE_SINGLE",
  "ACTIVITYTYPE_WORKFLOWNODE"
};

/**
 *
 *
 *
 *
 *
 *
 */
wr::ActivityIdentification::ActivityIdentification(const string& name,
	  			  		   const string& description,
				  		   const ACTIVITYTYPE type,
				  		   const vector<string>& annotation )
{
  Name = new string( name );
  Description = new string( description );
  Type = new ActivityTypeEnumeration;
  (*Type) = (ActivityTypeEnumeration)type;
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
wr::ActivityIdentification::set( const ActivityIdentification& src )
{
  Name = 0;
  Description = 0;
  Type = 0;

  if( src.Name )
    Name = new string( *src.Name );

  if( src.Description )
    Description = new string( *src.Description );
  
  if( src.Type ) {
    Type = new ActivityTypeEnumeration;
    (*Type) = (ActivityTypeEnumeration)*src.Type;
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
wr::ActivityIdentification::ActivityIdentification( const ActivityIdentification& src )
  : ActivityIdentificationType()
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
wr::ActivityIdentification::free( )
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
wr::ActivityIdentification::toString( const bool tabbed ) const
{  
  string tab;
  if(tabbed)
    tab = "\n\t";
  else 
    tab = "\n";

  string out;

  out += tab + "Name=" + (Name ? *Name : "N/A");
  out += tab + "Description=" + (Description ? *Description : "N/A");
  if(Type)
    out += tab + "Type=" + ACTIVITYTYPE_STRING[ *Type ];
  else
    out += tab + "Type=N/A";

  out += tab + "Annotation={" + util::join( Annotation, ", " ) + "}";

  return out;
}
