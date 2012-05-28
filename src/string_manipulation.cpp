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

#include "glite/ce/cream-client-api-c/string_manipulation.h"
#include <cstdio>
#include <cstdlib>
#include <cctype>
//#include <regex.h>
#include <iostream>
#include <exception>
#include <strings.h>
#include "boost/algorithm/string.hpp"
#include "boost/regex.hpp"

using namespace std;

namespace util = glite::ce::cream_client_api::util;
/*
//______________________________________________________________________________
bool util::string_manipulation::startsWith(const string& t, const string& s)
{
  unsigned int pos = t.find(s, 0);
  if((pos == string::npos) || (pos>0)) return false;
  return true;
}

//______________________________________________________________________________
bool util::string_manipulation::startsWith(const string& t, const char* s)
{
  unsigned int pos = t.find(s, 0);
  if((pos == string::npos) || (pos>0)) return false;
  return true;
}

//______________________________________________________________________________
bool util::string_manipulation::startsWith(const string& s, const char& c)
{
  unsigned int pos = s.find(c, 0);
  if((pos == string::npos) || (pos>0)) return false;
  return true;
}

//______________________________________________________________________________
bool util::string_manipulation::endsWith(const string& t, const char* s)
{
  int len = strlen(s);
  try {
    if( s==t.substr(t.length()-len, len) )
      return true;
//    return false;
  } catch(...) {}
  return false;
}

//______________________________________________________________________________
bool util::string_manipulation::endsWith(const string& t, const string& s)
{
  try {
    if( s==t.substr(t.length()-s.length(), s.length()) )
      return true;
  } catch(...) {}
  return false;
}

//______________________________________________________________________________
// bool util::string_manipulation::endsWith(const string& t, const char& c)
// {
//   try {
//     if( c == t[t.length()-1] );//t.substr(t.length()-1, 1).compare(string(1, c)))
//       return true;
//   } catch(...) {}
//   return false;
// }

*/

//______________________________________________________________________________
int util::string_manipulation::iCompare(const string& t, const string& s) 
{
  return strcasecmp( t.c_str(), s.c_str() ) ;
}

//______________________________________________________________________________
void util::string_manipulation::toLowerCase(string& s) 
{
  try {
    char *tmp = new char[s.length()+1];
    memset((void*)tmp, 0,s.length()+1); 
    unsigned int j=0;
    for(j=0; j<s.length(); j++) {
      if( 
	 (s.at(j)<65)||(s.at(j)>122)||
	 (s.at(j)<97 && s.at(j)>90)
	 ) {*(tmp+j)=s.at(j); continue;}
      
      if(s.at(j)<91) *(tmp+j)=s.at(j)+32;
      else *(tmp+j)=s.at(j);
    }
    s.assign(string(tmp));
  } catch(...) {}
}

//______________________________________________________________________________
void util::string_manipulation::toUpperCase(string& s) 
{
  try {
    char *tmp = new char[s.length()+1];
    memset((void*)tmp, 0,s.length()+1);
    unsigned int j=0;
    for(j=0; j<s.length(); j++) {
      if( 
	 (s.at(j)<65)||(s.at(j)>122)||
	 ((s.at(j)<97) && (s.at(j)>90))
	 ) {*(tmp+j)=s.at(j); continue;}
      
      if(s.at(j)>96) *(tmp+j)=s.at(j)-32;
      else *(tmp+j)=s.at(j);
    }
    s.assign(string(tmp));
  } catch(...) {}
}

/*

//______________________________________________________________________________
void util::string_manipulation::trim(string& t, const std::string& s) 
{
  if(!t.length())
    return;
  if(t==s) {
    t="";
    return;
  }
  unsigned int len =s.length();
  try {
    while(startsWith(t, s)) {
      t.assign(t.substr(len, t.length()-len));
      if(t==s) {
	t="";
	return;
      }
    }
    while(endsWith(t, s)) {
      t.assign(t.substr(0, t.length()-len));
      if(t==s) {
	t="";
	return;
      }
    }
  } catch(...) {
    ;
  }
}

//______________________________________________________________________________
void util::string_manipulation::trim(string& s, const char& c) 
{
  string t ="";
  t.append(1,c);
  trim(s, t);
}

//______________________________________________________________________________
void util::string_manipulation::trim(string& s) 
{
  trim(s, ' ');
}

//______________________________________________________________________________
void util::string_manipulation::split(const string& t, const string& tok,
                                      vector<string>& pieces)
{
  split(t, tok.c_str(), pieces);
}


//______________________________________________________________________________
void util::string_manipulation::split(const string& t, const char& tok, 
				      vector<string>& pieces)
{
  split(t, string(1, tok), pieces);
}

//______________________________________________________________________________
void util::string_manipulation::split(const string& s, 
		                      const char* tok,
				      vector<string>& target)
{
  try {
    string tmp = s;
    int toklen = strlen(tok);//tok.length();
    trim(tmp, tok);
    if(tmp.find(tok, 0)==std::string::npos) {
      target.push_back(tmp);
      return;
    }
    
    if(!contains(tmp, tok)) {
      target.push_back(tmp);
      return;
    }
    
    unsigned int pos;
    string _tmp;
    do {
      pos = tmp.find(tok, 0);
      _tmp = tmp.substr(0, pos);
      
      if(_tmp.length()) {
	try {target.push_back(_tmp);}
	catch(...) { }
      }
      try {tmp = tmp.substr(pos+toklen, tmp.length()-pos-toklen);}
      catch(...) {}
    } while(pos!=std::string::npos);  
  } catch(...) {}
}

*/

//______________________________________________________________________________
bool util::string_manipulation::contains(const string& t, const std::string& s)
{
  if(t.find(s, 0)==std::string::npos) return false;
  return true;
}

//______________________________________________________________________________
bool util::string_manipulation::iContains(const string& t, const std::string& s) 
{
  string tmp1=t;
  string tmp2=s;
  toLowerCase(tmp1);
  toLowerCase(tmp2);
  if(tmp1.find(tmp2, 0)==string::npos) return false;
  return true;
}

//______________________________________________________________________________
int util::string_manipulation::indexOf(const string& t, const char& c, 
				       const unsigned int& off)
{
  return t.find(c, off);
}

//______________________________________________________________________________
int util::string_manipulation::indexOf(const string& t, const std::string& c, 
				       const unsigned int& off)
{
  return t.find(c, off);
}

//______________________________________________________________________________
int util::string_manipulation::lastIndexOf(const string& s, const char& c)
{
  unsigned int pos = 0, savepos = 0;
  do {
    savepos = pos;
    pos = indexOf(s, c, pos+1);
  } while(pos!=string::npos);
  if(!savepos) return -1;
  return savepos;
}

//______________________________________________________________________________
int util::string_manipulation::lastIndexOf(const string& s, 
					   const std::string& c)
{
  unsigned int pos = 0, savepos = 0;
  do {
    savepos = pos;
    pos = indexOf(s, c, pos+1);
  } while(pos!=std::string::npos);
  if(savepos==string::npos) return -1;
  return savepos;
}

//______________________________________________________________________________
bool util::string_manipulation::matches(const char* s, 
					const char* regex_buf)
{
  boost::cmatch what;
  const boost::regex pattern(regex_buf);
  if ( !boost::regex_match(s, what, pattern) ) return false;
  return true;
}

//______________________________________________________________________________
bool util::string_manipulation::matches(const string& s, 
					const string& regex_buf)
{
  return matches(s.c_str(), regex_buf.c_str());
}

//______________________________________________________________________________
bool util::string_manipulation::matches(const char* s, 
					const string& regex_buf)
{
  return matches(s, regex_buf.c_str());
}

//______________________________________________________________________________
bool util::string_manipulation::matches(const string& s, 
					const char* regex_buf)
{
  return matches(s.c_str(), regex_buf);
}

//______________________________________________________________________________
void util::string_manipulation::chomp(string& t)
{
  try {
    if(boost::ends_with(t, "\n"))
      t.assign(t.substr(0,t.length()-1));
  } catch(...) {}
}

//______________________________________________________________________________
bool util::string_manipulation::vector_contains(const vector<string>& v, 
						const string& s)
{
  vector<string>::const_iterator it;
  for( it=v.begin(); it!=v.end(); it++ )
    if( *(it) == s) return true;
  return false;
}

//______________________________________________________________________________
void util::string_manipulation::notContainedIn(const vector<string>& t, 
							 const vector<string>& v,
							 vector<string>& missing)
{
  bool found;
  //missing.reserve(t.size());
  for(unsigned int i = 0; i<t.size(); i++) {
    found = false;
    for(unsigned int j=0; j<v.size(); j++) {
      if( t[i] == v[j] ) { found = true; break;}
    }
    if(!found) missing.push_back(t.at(i));
  }
}

//______________________________________________________________________________
int util::string_manipulation::string2int(const string& S) 
  throw(NumericException&)
{
  if(!isNum(S)) 
    throw NumericException(string("String [")+S+"] doesn't represent a number");
  return atoi(S.c_str());
}

//______________________________________________________________________________
bool util::string_manipulation::isNum(const string& S) {
  if(!S.length()) return false;
  int start=0;
  if(S[0] == '-') start = 1;
  for(unsigned j=start; j<S.length(); j++)
    if(!isdigit(S[j])) return false;
  return true;
}
