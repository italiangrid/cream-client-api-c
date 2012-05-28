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

#ifndef _GLITE_CE_CREAM_CLIENT_API_UTIL_CEURL_H_
#define _GLITE_CE_CREAM_CLIENT_API_UTIL_CEURL_H_

#include <vector>
#include <string>
#include <map>
#include "glite/ce/cream-client-api-c/ceid_syntax_ex.h"
#include "boost/regex.hpp"

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace util {

	/// CREAM CE URL utilities
	/**
	   This namespace collects some functions that parse the format of the strings of CREAM resource
	   identifier, CREAM Jobs etc.
	*/
	namespace CEUrl {

	  static const boost::regex s_ceid_pattern("^([^:]+)(:[0-9]+)?/cream-([^-]+)-(.+)");
	  static const boost::regex s_ceid_es_pattern("^([^:]+)(:[0-9]+)?/es-([^-]+)-(.+)");
	  
	  static const boost::regex s_jceid_pattern("^(https?)://([^:]+)(:[0-9]+)?/(.+)");

	  /**
	     Checks the format of the the string containing a CREAM resource identifier that must be in the form 
	     <b><hostname>[:8443]/cream-<LRMS>-<QUEUE_NAME></b>; then splits it into several relevant pieces:
	     - The hostname
	     - The TCP port number
	     - The LRMS type (LSF, PBS, ...)
	     - The queue name

	     These pieces are put in this order into the vector<string> second argument.

	     If the CREAM resource identifier doesn't contain the TCP port number, the default is returned (8443) 
	     or that one specified by the user as third argument.
	     
	     Be careful!! The array of strings should be empty before be passed to this function.

	     \param ceid The CREAM URL
	     \param target An array of strings
	     \param default_tcpport The default TCP port number to put into the array if not present in the ceid
	  */
	  void parseCEID(const std::string& ceid, std::vector<std::string>& target,
	                 const std::string& default_tcpport = "8443")
	    throw(glite::ce::cream_client_api::util::CEUrl::ceid_syntax_ex&);

	  /**
	     Checks the format of the the string containing a CREAM Job ID that must be in the form 
	     <b><protocol>://<hostname>:<tcp_port>/CREAM[a-zA-z0-9]</b>; then splits it into several
	     relevant pieces:
	     - The transport protocol (http or https)
	     - The hostname
	     - The TCP port number
	     - The CREAM local identifier

	     These pieces are put in this order into the vector<string> second argument.

	     If the CREAM job ID doesn't contain the TCP port number, the default is returned (8443) 
	     or that one specified by the user as third argument.
	     
	     Be careful!! The array of strings should be empty before to be passed to this function.

	     \param jid The CREAM Job ID
	     \param target An array of strings 
	     \param default_tcpport The default TCP port number to put into the array if not present in the ceid
	  */
	  void parseJobID(const std::string& jid, std::vector<std::string>& target,
	                  const std::string& default_tcpport = "8443")
	    throw(glite::ce::cream_client_api::util::CEUrl::ceid_syntax_ex&);

	  /**
	     This function take a list of CREAM Job IDs and organize them basing on the CREAM endpoint the belong to. 
	     The output of the function is put in the second argument that is a map<string, vector<string> >. Each key 
	     of the map is a different CREAM URL, each value corresponding to an URL is a list of jobs submitted 
	     to that CREAM.
	     
	     This function extracts the endpoints from the jobs. In order to build an URL from the endpoint, a proper
	     postfix must be appended to the endpoint. This postfix is passed to the function as third argument.

	     Be careful!! The map should be empty before to be passed to this function.

	     \param jobs The list of jobs submitted to several CREAM endpoint
	     \param organized_jobs The jobs organized 
	     \param endpoint_postfix The string to append to each different endpoint extracted from the jobs
	  */
	  void organise_by_endpoint(const std::vector<std::string>& jobs,
				    std::map<std::string, std::vector<std::string> >& organized_jobs,
				    const char* endpoint_postfix)
	    throw(ceid_syntax_ex&);

	  /**
	     This function extracts the hostname and the TCP port number from a CREAM URL

	     \param url The CREAM URL to parse
	     \param host The string that will contain the hostname after a succesfull parsing
	     \param port The int that will contains the TCP port number after a succesfull parsing
	  */
	  void extractHostPort(const std::string& url, std::string& host, int& port) throw();

	  /**
	     This function extracts the endpoint (<hostname>:<tcp_port>) from a complete CREAM URL 
	     <b>http[s]://<hostname>[:tcp_port]/ce-cream/services/CREAM2</b>.

	     \param url The CREAM URL to parse
	     \return The extracted endpoint
	  */
	  std::string extractEndpointFromURL(const std::string& url) throw();
	}
      }
    }
  }
}

#endif
