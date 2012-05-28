#ifndef EMIES_CLIENTLIB_WRAPPERS_ACTI_H
#define EMIES_CLIENTLIB_WRAPPERS_ACTI_H

#include "glite/ce/es-client-api-c/es_client_soapStub.h"
#include "glite/ce/es-client-api-c/typedefs.h"


#include <string>
#include <vector>

namespace emi_es {
  namespace client {
    namespace wrapper {
	
	class ActivityIdentification : public ActivityIdentificationType
	{
	private:
	  ActivityIdentification() : ActivityIdentificationType( ) { }
	    
	public:

          enum ACTIVITYTYPE {
            ACTIVITYTYPE_COLLECTIONELEMENT = ESADL__ActivityTypeEnumeration__collectionelement,
            ACTIVITYTYPE_PARALLELELEMENT   = ESADL__ActivityTypeEnumeration__parallelelement,
            ACTIVITYTYPE_SINGLE            = ESADL__ActivityTypeEnumeration__single,
            ACTIVITYTYPE_WORKFLOWNODE      = ESADL__ActivityTypeEnumeration__workflownode
          };

	  ActivityIdentification( const std::string& name,
				  const std::string& Description,
				  const ACTIVITYTYPE type,
				  const std::vector<std::string>& annotation );
	    
	  virtual ~ActivityIdentification( ) { this->free( ); }
	  ActivityIdentification( const ActivityIdentification& );
	    
	  static char *ACTIVITYTYPE_STRING[];

	  std::string toString( const bool tabbed = false ) const;

	private:
	  void free( );
	  void set( const ActivityIdentification& );
	  ActivityIdentification& operator=(const ActivityIdentification& ) { return *this; }
	};
	
    }
  }
}

#endif
