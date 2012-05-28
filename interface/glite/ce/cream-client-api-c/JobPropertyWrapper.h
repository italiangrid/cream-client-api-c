/* LICENSE:
Copyright (c) Members of the EGEE Collaboration. 2010.
See http://www.eu-egee.org/partners/ for details on the copyright
holders.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
implied.
See the License for the specific language governing permissions and
limitations under the License.

END LICENSE */

#ifndef GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JPW
#define GLITE_CE_CREAM_CLIENT_API_SOAPPROXY_JPW

//#include "CREAM_CLIENTH.h"
//#include "CREAM_CLIENTStub.h"

#include "glite/ce/cream-client-api-c/cream_client_soapH.h"
#include "glite/ce/cream-client-api-c/cream_client_soapStub.h"

#include <string>

namespace glite {
namespace ce {
namespace cream_client_api {
namespace soap_proxy {

  /// A wrapper class for the property
  /**
     Some information job-related and service-related are exchanged between  
     CREAM and its clients as couple of strings (name, value) that are structured in the property class.

     \see JobIdWrapper
  */
  class JobPropertyWrapper : public CREAMTYPES__Property {
    
  protected:

    JobPropertyWrapper& operator=( const JobPropertyWrapper& aProp ) throw ()
      { 
	if ( &aProp != this ) {
	  name  = aProp.name;
	  value = aProp.value;
	}
	return *this; 
      }

    JobPropertyWrapper( const CREAMTYPES__Property* other ) 
      {
	if ( other ) {
	  name = other->name;
	  value = other->value;
	}
      }
    
  public:
    /**
       Class constructor
       
       \param n The name of a property
       \param v The value of the property
    */
    JobPropertyWrapper( const std::string& n, const std::string& v) throw() 
      { name = n; value = v; }
    
    
    

    /**
       Clas destructor
    */
    virtual ~JobPropertyWrapper() throw() {}
    
    /**
       Return the name of the property

       \return std::string
    */
    std::string getPropertyName( void ) const { return name; }

    /**
       Return the value of the property
       
       \return std::string
    */
    std::string getPropertyValue( void ) const { return value; }
    
  };
  
}
}
}
}

#endif
