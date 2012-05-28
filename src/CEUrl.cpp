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

#include "glite/ce/cream-client-api-c/CEUrl.h"
#include <iostream>
#include <cctype>
#include <sys/types.h>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/find.hpp>

using namespace std;

#define MATCH_NUM 10
#define PROTO "https://"
#define PROTO_NA "http://"

namespace ceurl_util = glite::ce::cream_client_api::util::CEUrl;

//_______________________________________________________________________________
void ceurl_util::parseCEID(const string& ceid, vector<string>& pieces,
			   const string& _tcpport)
  throw(ceurl_util::ceid_syntax_ex&)
{
  boost::cmatch what;
  if ( !boost::regex_match(ceid.c_str(), what, s_ceid_pattern) ) {
    throw ceurl_util::ceid_syntax_ex("Specified CEID has wrong format. Must be <host>:<tcp_port>/cream-<batch_system_name>-<queue_name>");
  }

  string tcpport = what[2];

  if( tcpport.empty() )
    tcpport = _tcpport;
  else tcpport = tcpport.substr(1, tcpport.length()-1);

  pieces.push_back(what[1]);
  pieces.push_back(tcpport);
  pieces.push_back(what[3]);
  pieces.push_back(what[4]);
}

//_______________________________________________________________________________
void ceurl_util::parseJobID(const string& jid, vector<string>& pieces,
                            const string& _tcpport)
  throw(ceurl_util::ceid_syntax_ex&)
{
  boost::cmatch what;
  if ( !boost::regex_match(jid.c_str(), what, s_jceid_pattern) )
    throw ceurl_util::ceid_syntax_ex("Specified JobID hasn't format http[s]://<host>:<tcp_port>/<ID>");

  string tcpport = what[3];

  if( tcpport.empty() ) {
    tcpport = _tcpport;
  } else {
    tcpport = tcpport.substr(1, tcpport.length()-1);
  }

  pieces.push_back(what[1]);
  pieces.push_back(what[2]);
  pieces.push_back(tcpport);
  pieces.push_back(what[4]);
}

//_______________________________________________________________________________
void ceurl_util::organise_by_endpoint(const vector<string>& src,
				      map<string, vector<string> >& target,
				      const char* postfix)
  throw(ceurl_util::ceid_syntax_ex&)
{
  vector<string> pieces;
  string endpoint;
  pieces.reserve(3);
  for(vector<string>::const_iterator it = src.begin();
      it != src.end();
      ++it) 
    {
      parseJobID(*it, pieces);
      endpoint = pieces[0] + "://" + pieces[1] + ":" + pieces[2] + postfix;
      target[endpoint].push_back(*it);
      pieces.clear();
    }
}

//_______________________________________________________________________________
void ceurl_util::extractHostPort(const std::string& endpoint,
				 std::string& host,
				 int& port) throw()
{
  string _endpoint = endpoint;
  static vector<string> _tmp;
  _tmp.clear();
  unsigned int pos = _endpoint.find("://", 0);
  if(pos != string::npos)
    _endpoint = _endpoint.substr(pos+3, _endpoint.length());

  pos = _endpoint.find("/",0);
  if(pos != string::npos)
    _endpoint = _endpoint.substr(0, pos);
  if(_endpoint.find(":", 0) != string::npos) {
    boost::split(_tmp, _endpoint, boost::is_any_of(":"));
    host = _tmp[0];
    port = atoi(_tmp[1].c_str());
  } else { host =_endpoint; port = -1; }
}

//_______________________________________________________________________________
string ceurl_util::extractEndpointFromURL( const string& url ) throw()
{
  string tmp = url;
  boost::replace_first( tmp, "http://", "" );
  boost::replace_first( tmp, "https://", "" );
  unsigned int pos = tmp.find("/");
  if ( pos != string::npos ) 
    tmp = tmp.substr(0, pos);
  
  pos = tmp.find( ":" );
  if( pos != string::npos )
    tmp = tmp.substr(0, pos);
    
  return tmp;
}
