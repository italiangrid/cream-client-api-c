#ifndef EMIES_CLIENTLIB_WRAPPERS_NOTIF_H
#define EMIES_CLIENTLIB_WRAPPERS_NOTIF_H

#include "glite/ce/es-client-api-c/WActivityStatus.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <vector>
#include <string>

namespace emi_es {
  namespace client {
    namespace wrapper {
      
      class WNotification : public Notification
      {
      private:
	WNotification( ) : Notification( ) { }

	static char *PROTOCOLTYPEENUM_STRING[];
	
      public:
	WNotification( const ProtocolTypeEnumeration protocol,
		       const std::vector<std::string>& recipient,
		       const std::vector<ActivityStatusState> onstate,
		       bool* optional );
	  
	//ProtocolTypeEnumeration getProtocolTypeNum( const char* ) const;  
	  
	virtual ~WNotification() { this->free( ); }
	WNotification( const WNotification& );

	std::string toString( const bool tabbed = false ) const;

	WNotification& operator=( const WNotification& src ) { this->free( ); this->set(src); return *this; }
	static ProtocolTypeEnumeration getProtoNumber( const std::string& ) ;
	
      private:
        static std::map<std::string, ProtocolTypeEnumeration> *s_ProtoStringToNum;
	static boost::recursive_mutex  s_mutex;
	void free( );
	void set( const WNotification& );
      };
      
    }
  }
}

#endif
