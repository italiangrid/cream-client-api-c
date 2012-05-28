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
#ifndef _GLITE_CE_CREAM_CLIENT_UTIL_CONFMGR_H_
#define _GLITE_CE_CREAM_CLIENT_UTIL_CONFMGR_H_

#include <map>
#include <string>
#include <vector>
#include <cstdio>
#include "glite/ce/cream-client-api-c/file_ex.h"
#include "glite/ce/cream-client-api-c/classad_syntax_ex.h"
//#include "glite/ce/cream-client-api-c/string_manipulation.h"

namespace util = glite::ce::cream_client_api::util;

namespace glite {
  namespace ce {
    namespace cream_client_api {
      namespace util {

	class ConfigurationManager {

	  std::map<std::string, std::string> m_hash;
	  bool m_loaded;
	  
	public:
	  enum conf_format {
	    xml = 0, classad = 1, pairs = 2
	  };

	  ConfigurationManager(const ConfigurationManager&);
	  ConfigurationManager(const ConfigurationManager::conf_format& f=ConfigurationManager::pairs) : m_loaded(false), m_fmt(f) {}
	  ConfigurationManager& operator=(const ConfigurationManager&);
	  virtual ~ConfigurationManager() {}
	  
	  virtual std::string        getProperty(const std::string& s);// { return m_hash[s]; }
	  virtual void               setProperty(const std::string& s, const std::string& S) { m_hash[s]=S; }
	  virtual std::string        getProperty(const std::string& s, const std::string& def);/* {
	    if( m_hash[s].empty() ) return def;
	    else return m_hash[s];
	  }*/
	  virtual void          listProperties(FILE*);
	  virtual void          getKeys(std::vector<std::string>&);
	  virtual void          load(const char* filename) throw(util::file_ex&, util::classad_syntax_ex&);
	  /**
	   * When we load multiple files the attributes from different files
	   * are merged together in the internal hash table.
	   * Furthermore in case of attribute duplication, thanks to the map<> property,
	   * the attribute from i-th file overwrites the attribute with same name 
	   * specified in the (i-1)-th file.
	   */
	  virtual void          load(const std::vector<std::string>&) throw(util::file_ex&);
	  virtual void          store(const char* filename) throw (util::file_ex&) {}
	  
	private:
	  conf_format m_fmt;
	};
      }
    }
  }
}

#endif
