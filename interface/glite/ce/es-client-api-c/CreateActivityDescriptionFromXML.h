#ifndef EMIES_CLIENTLIB_WRAPPERS_CRTACTFROMXML_H
#define EMIES_CLIENTLIB_WRAPPERS_CRTACTFROMXML_H

#include <string>
#include <vector>
#include <utility>

namespace emi_es {
  namespace client {
    
    namespace wrapper {
      class ActivityDescription;
    }
      
    class CreateActivityDescriptionFromXML 
    {
    public:
      static void create( const std::string& file, std::vector< std::pair<wrapper::ActivityDescription*, std::string> >& ) throw(std::string);
      static void free( std::vector< std::pair<wrapper::ActivityDescription*, std::string> >& );
    };
      
    
  }
}

#endif
