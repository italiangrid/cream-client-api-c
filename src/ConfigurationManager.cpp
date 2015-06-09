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

#include <cstring>
#include <cstdio>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cerrno>

#include "classad_distribution.h"
#include "glite/ce/cream-client-api-c/creamApiLogger.h"
#include "glite/ce/cream-client-api-c/ConfigurationManager.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

using namespace std;
namespace util = glite::ce::cream_client_api::util;

//______________________________________________________________________________
void loadPairs(const char* file, map<string, string>& H) throw(util::file_ex&) 
{
  string Buf="";
  vector<string> keyval;
  keyval.reserve(2);
  ifstream is( file, ios::in );
  if(!is)
    throw util::file_ex("Error opening configuration file");
  int line=1;

  while(is.peek()!=EOF) {

    std::getline(is, Buf, '\n');

    if(is.fail() || is.bad())
      throw util::file_ex("Error reading from configuration file");
    if( Buf.empty() ) {line++; continue;}
    boost::trim(Buf);
    if(boost::starts_with(Buf, "#")) {line++;continue;}
    if(boost::starts_with(Buf, "//")) {line++;continue;}
    boost::cmatch what;
    const boost::regex match("\\w+=\\w+");
    if( !boost::regex_match(Buf.c_str(), match) ) {
      line++;
      continue;
    }
    keyval.clear();
    //    util::string_manipulation::split(Buf, "=", keyval);
    boost::split(keyval, Buf, boost::is_any_of("="));
    H[keyval.at(0)] = keyval.at(1);
    line++;
  }

  is.close();
}

//______________________________________________________________________________
void loadClassAd(const char* file, map<string, string>& H) 
  throw(util::file_ex&, util::classad_syntax_ex&) 
{
  ifstream is( file, ios::in );
  if(!is)
    throw util::file_ex("Error opening configuration file");
  string completeBuf="", Buf="";

  std::getline(is, Buf, '\0');  
  if(is.fail() || is.bad())
    throw util::file_ex("Error reading from configuration file");
  is.close();

  classad::ClassAdParser parser;
  classad::ClassAdUnParser unp;
  const classad::ExprTree *tree;
  classad::ClassAd *ad;
  classad::ClassAdIterator it;
  if(!(ad=parser.ParseClassAd(Buf.c_str())))
    throw util::classad_syntax_ex("Configuration file has classad syntax error");

  it.Initialize(*ad);
  string buffer, attrName;
  while(!it.IsAfterLast()) {
    it.CurrentAttribute( attrName, tree );
    unp.Unparse( buffer, tree );
    boost::trim(attrName);
    boost::trim(buffer);
    if(boost::ends_with(buffer, "\"")) {
      buffer = buffer.substr(0, buffer.length()-1);
    }
    if(boost::starts_with(buffer, "\"")) {
      buffer = buffer.substr(1, buffer.length()-1);
    }
    boost::to_lower(attrName);
    H[attrName]=buffer;
    attrName = "";
    buffer = "";
    it.NextAttribute( attrName, tree );
  }
}

//______________________________________________________________________________
util::ConfigurationManager::ConfigurationManager(const util::ConfigurationManager& C) 
{
  map<string, string>::const_iterator it;
  for(it = C.m_hash.begin(); it != C.m_hash.end(); it++)
    this->m_hash[(*it).first] = (*it).second;
}

//______________________________________________________________________________
util::ConfigurationManager& 
util::ConfigurationManager::operator=(const util::ConfigurationManager& C) 
{
  m_hash.clear();
  map<string, string>::const_iterator it;
  for(it = C.m_hash.begin(); it != C.m_hash.end(); it++) {
    this->m_hash[(*it).first] = (*it).second;
  }
  return *this;
}

//______________________________________________________________________________
void util::ConfigurationManager::load(const char* filename) 
  throw (util::file_ex&, util::classad_syntax_ex&) 
{
//   struct stat buf;
//   if(stat(filename, &buf) < 0)
//     {
//       int saveerr = errno;
//       if(saveerr == ENOENT) return;

//       else throw util::file_ex(strerror(saveerr));
//     }
#ifdef NEWBOOSTFS
  if(!boost::filesystem::exists( boost::filesystem::path(filename).native() ))
#else
  if(!boost::filesystem::exists( boost::filesystem::path(filename, boost::filesystem::native) ))
#endif
    throw util::file_ex( string("file")+ filename + " doest not exist");
  
  ifstream input( filename );
  if(!input)
    throw util::file_ex( string("file")+ filename + " cannot be read");

//   if(!(buf.st_mode & S_IRUSR))
//     throw util::file_ex("Conf file is there but it is not readable");
  
  if(m_fmt == pairs) {
    loadPairs(filename, m_hash);
  }
  if(m_fmt == classad) {
    loadClassAd(filename, m_hash);
  }
}

//______________________________________________________________________________
void util::ConfigurationManager::load(const vector<string>& files) 
  throw (util::file_ex&) 
{
  int good = 0;
  for(vector<string>::const_iterator sit = files.begin();
      sit != files.end();
      sit++) { //unsigned int j=0; j<files.size(); j++) {
    
    if(*sit != "") {
      try {
	this->load( (*sit).c_str() );
      } catch(util::file_ex& ex) {
	CREAM_SAFE_LOG(util::creamApiLogger::instance()->getLogger()->log( log4cpp::Priority::WARN, "ConfigurationManager::load() - File [%s] is not suitable for configuration loading. Skipping it...", (*sit).c_str() ));
          continue;
      } catch(util::classad_syntax_ex& ex) {
	CREAM_SAFE_LOG(util::creamApiLogger::instance()->getLogger()->log( log4cpp::Priority::WARN,  "ConfigurationManager::load() - File [%s] is not suitable for configuration loading. Skipping it...", (*sit).c_str()));
	continue;
      }
      good++;
    }
  }

  if(good == 0) {
    throw util::file_ex("No configuration file suitable for loading");
  }
}

//______________________________________________________________________________
void util::ConfigurationManager::listProperties(FILE* f) {
  map<string, string>::const_iterator it;
  for(it = m_hash.begin(); it != m_hash.end(); it++)
    fprintf(f,"[%s]=[%s]\n", (*it).first.c_str(), (*it).second.c_str());
}

//______________________________________________________________________________
void util::ConfigurationManager::getKeys(vector<string>& keys) {
  for(map<string, string>::iterator it=m_hash.begin(); it!=m_hash.end(); it++) {
    keys.push_back((*it).first);
  }
}

//______________________________________________________________________________
std::string util::ConfigurationManager::getProperty(const std::string& s)
{
  string tmp = s;
  boost::to_lower(tmp);
  return m_hash[tmp];
}

//______________________________________________________________________________
std::string util::ConfigurationManager::getProperty(const std::string& s, 
						    const std::string& def)
{
  string tmp = s;
  boost::to_lower(tmp);

  if( m_hash[tmp].empty() ) 
    return def;
  else 
    return m_hash[tmp];
}
