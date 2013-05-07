#ifndef EMIES_CLIENTLIB_COMM_QRYRESOURCEINFO_H
#define EMIES_CLIENTLIB_COMM_QRYRESOURCEINFO_H

#include "glite/ce/es-client-api-c/AbstractCall.h"

#include <string>
//#include <boost/tuple.hpp>

namespace emi_es {
  namespace client {
    namespace comm {

      class QueryResourceInfoCall : public AbstractCall {

	friend class CallFactory;

	std::string  m_dialect;
	std::string  m_query;

/* 	std::vector<std::string> m_arrayResp; */
/* 	std::string              m_attribute; */
/* 	std::string              m_mixed; */
	std::vector<boost::tuple<std::string, std::string, std::string> > m_arrayResp;
	
      protected:
	QueryResourceInfoCall( const std::string& endpoint,
			       const std::string& dialect,
			       const std::string& query );

      public:
	virtual ~QueryResourceInfoCall() throw() {}

	bool execute( std::string& error, enum SOAP_CALL_ERROR_CODES& );

	void getResponse( std::vector<boost::tuple<std::string, std::string, std::string> >& arrayResp )
	  const
	{
	  arrayResp = m_arrayResp;
	}

      };

    }
  }
}

#endif
