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

#include "glite/ce/cream-client-api-c/certUtil.h"
#include "glite/ce/cream-client-api-c/creamApiLogger.h"

extern "C" {
  #include "gridsite.h"
}

#include "boost/algorithm/string.hpp"
#include "boost/format.hpp"

#include <vector>
#include <ctime>
#include <unistd.h>
#include <openssl/sha.h>
#include <sys/time.h>

#include <iostream>

namespace soapProxy = glite::ce::cream_client_api::soap_proxy;

void getFQANs(const std::string& pxfile, std::vector<std::string>& vect) throw (soapProxy::auth_ex&);
			   
#define GRST_MAX_CHAIN_LEN 9

//______________________________________________________________________________
ASN1_TIME *glite::ce::cream_client_api::certUtil::convtime(const std::string& data)
{
  ASN1_TIME *t= ASN1_TIME_new();

  t->data   = (unsigned char *)(data.data());
  t->length = data.size();
  switch(t->length) {
  case 10:
    t->type = V_ASN1_UTCTIME;
    break;
  case 15:
    t->type = V_ASN1_GENERALIZEDTIME;
    break;
  default:
    ASN1_TIME_free(t);
    return NULL;
  }
  return t;
}



//______________________________________________________________________________
time_t glite::ce::cream_client_api::certUtil::stillvalid(ASN1_TIME *ctm)
{
  char     *str;
  time_t    offset;
  time_t    newtime;
  char      buff1[32];
  char     *p;
  int       i;
  struct tm tm;
  int       size;

  static bool tzadjusted = false;
  static int  tzcor = 0;

  switch (ctm->type) {
  case V_ASN1_UTCTIME:
    size=10;
    break;
  case V_ASN1_GENERALIZEDTIME:
    size=12;
    break;
  }
  p = buff1;
  i = ctm->length;
  str = (char *)ctm->data;
  if ((i < 11) || (i > 17)) {
    newtime = 0;
  }
  memcpy(p,str,size);
  p += size;
  str += size;

  if ((*str == 'Z') || (*str == '-') || (*str == '+')) {
    *(p++)='0'; *(p++)='0';
  }
  else {
    *(p++)= *(str++); *(p++)= *(str++);
  }
  *(p++)='Z';
  *(p++)='\0';

  if (*str == 'Z') {
    offset=0;
  }
  else {
    if ((*str != '+') && (str[5] != '-')) {
      newtime = 0;
    }
    offset=((str[1]-'0')*10+(str[2]-'0'))*60;
    offset+=(str[3]-'0')*10+(str[4]-'0');
    if (*str == '-') {
      offset=-offset;
    }
  }

  tm.tm_isdst = 0;
  int index = 0;
  if (ctm->type == V_ASN1_UTCTIME) {
    tm.tm_year  = (buff1[index++]-'0')*10;
    tm.tm_year += (buff1[index++]-'0');
  }
  else {
    tm.tm_year  = (buff1[index++]-'0')*1000;
    tm.tm_year += (buff1[index++]-'0')*100;
    tm.tm_year += (buff1[index++]-'0')*10;
    tm.tm_year += (buff1[index++]-'0');
  }

  if (tm.tm_year < 70) {
    tm.tm_year+=100;
  }

  if (tm.tm_year > 1900) {
    tm.tm_year -= 1900;
  }

  tm.tm_mon   = (buff1[index++]-'0')*10;
  tm.tm_mon  += (buff1[index++]-'0')-1;
  tm.tm_mday  = (buff1[index++]-'0')*10;
  tm.tm_mday += (buff1[index++]-'0');
  tm.tm_hour  = (buff1[index++]-'0')*10;
  tm.tm_hour += (buff1[index++]-'0');
  tm.tm_min   = (buff1[index++]-'0')*10;
  tm.tm_min  += (buff1[index++]-'0');
  tm.tm_sec   = (buff1[index++]-'0')*10;
  tm.tm_sec  += (buff1[index++]-'0');

  newtime = mktime( &tm );

  if(!tzadjusted) {

    time_t now = time(0);
    struct tm ltn, gtn;
    if (!localtime_r(&now, &ltn))
      return newtime;
    if (!gmtime_r(&now, &gtn))
      return newtime;
    //
    // Calculate correction
    tzcor = ((ltn.tm_hour - gtn.tm_hour) +
	     (ltn.tm_mday - gtn.tm_mday) * 24) * 3600;
    //
    // We did it
    tzadjusted=true;
  }

  newtime += tzcor;

  return newtime;
}

static void mpcerror(FILE *debugfp, char *msg)
{
  if (debugfp != NULL)
    {
      fputs(msg, debugfp);
      CREAM_SAFE_LOG(glite::ce::cream_client_api::util::creamApiLogger::instance()->getLogger()->errorStream()
		     << msg
		     );

      fprintf( debugfp, "%s", msg);

    }
}

#ifndef GRST_BACKDATE_SECONDS
#define GRST_BACKDATE_SECONDS 300
#endif
/*
 * TODO verify if it is still useful
 */
/// Make a GSI Proxy chain from a request, certificate and private key
int glite::ce::cream_client_api::certUtil::GRSTx509MakeProxyCert_local(char **proxychain, FILE *debugfp, 
                          char *reqtxt, char *cert, char *key, int minutes)
///
/// The proxy chain is returned in *proxychain. If debugfp is non-NULL,
/// errors are output to that file pointer. The proxy will expired in
/// the given number of minutes starting from the current time.
{
  char *ptr, *certchain;
  int i, ncerts;
  long serial = 1234, ptrlen;
  EVP_PKEY *pkey, *CApkey;
  const EVP_MD *digest;
  X509 *certs[GRST_MAX_CHAIN_LEN];
  X509_REQ *req;
  X509_NAME *name, *CAsubject, *newsubject;
  X509_NAME_ENTRY *ent;
  FILE *fp;
  BIO *reqmem, *certmem;
  time_t notAfter;
  time_t notBefore;

  /* read in the request */
  reqmem = BIO_new(BIO_s_mem());
  BIO_puts(reqmem, reqtxt);
    
  if (!(req = PEM_read_bio_X509_REQ(reqmem, NULL, NULL, NULL)))
    {
      mpcerror(debugfp,
              "GRSTx509MakeProxyCert(): error reading request from BIO memory\n");
      BIO_free(reqmem);
      return GRST_RET_FAILED;
    }
    
  BIO_free(reqmem);

  /* verify signature on the request */
  if (!(pkey = X509_REQ_get_pubkey(req)))
    {
      mpcerror(debugfp,
              "GRSTx509MakeProxyCert(): error getting public key from request\n");
      
      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }

  if (X509_REQ_verify(req, pkey) != 1)
    {
      mpcerror(debugfp,
            "GRSTx509MakeProxyCert(): error verifying signature on certificate\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }
    
  /* read in the signing certificate */
  if (!(fp = fopen(cert, "r")))
    {
      mpcerror(debugfp,
            "GRSTx509MakeProxyCert(): error opening signing certificate file\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }    

  for (ncerts = 1; ncerts < GRST_MAX_CHAIN_LEN; ++ncerts)
   if ((certs[ncerts] = PEM_read_X509(fp, NULL, NULL, NULL)) == NULL) break;

  if (ncerts == 1) /* zeroth cert with be new proxy cert */
    {
      mpcerror(debugfp,
            "GRSTx509MakeProxyCert(): error reading signing certificate file\n");

      X509_REQ_free(req);
      fclose( fp );
      return GRST_RET_FAILED;
    }    

  fclose(fp);
  
  CAsubject = X509_get_subject_name(certs[1]);

  /* read in the CA private key */
  if (!(fp = fopen(key, "r")))
    {
      mpcerror(debugfp,
            "GRSTx509MakeProxyCert(): error reading signing private key file\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }    

  if (!(CApkey = PEM_read_PrivateKey(fp, NULL, NULL, NULL)))
    {
      mpcerror(debugfp,
            "GRSTx509MakeProxyCert(): error reading signing private key in file\n");

      X509_REQ_free(req);
      fclose( fp );
      return GRST_RET_FAILED;
    }    

  fclose(fp);
  
  /* get subject name */
  if (!(name = X509_REQ_get_subject_name(req)))
    {
      mpcerror(debugfp,
            "GRSTx509MakeProxyCert(): error getting subject name from request\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }    

  /* create new certificate */
  if (!(certs[0] = X509_new()))
    {
      mpcerror(debugfp,
            "GRSTx509MakeProxyCert(): error creating X509 object\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }    

  /* set version number for the certificate (X509v3) and the serial number   
     need 3 = v4 for GSI proxy?? */
  if (X509_set_version(certs[0], 2L) != 1)
    {
      mpcerror(debugfp,
            "GRSTx509MakeProxyCert(): error setting certificate version\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }    

  ASN1_INTEGER_set(X509_get_serialNumber(certs[0]), serial++);

  if (!(name = X509_get_subject_name(certs[1])))
    {
      mpcerror(debugfp,
      "GRSTx509MakeProxyCert(): error getting subject name from CA certificate\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }    

  if (X509_set_issuer_name(certs[0], name) != 1)
    {
      mpcerror(debugfp,
      "GRSTx509MakeProxyCert(): error setting issuer name of certificate\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }    

  /* set issuer and subject name of the cert from the req and the CA */
  ent = X509_NAME_ENTRY_create_by_NID(NULL, OBJ_txt2nid("commonName"), 
                                      MBSTRING_ASC, (unsigned char*)"proxy", -1);

  newsubject = X509_NAME_dup(CAsubject);

  X509_NAME_add_entry(newsubject, ent, -1, 0);

  if (X509_set_subject_name(certs[0], newsubject) != 1)
    {
      mpcerror(debugfp,
      "GRSTx509MakeProxyCert(): error setting subject name of certificate\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }    
    
  X509_NAME_free(newsubject);
  X509_NAME_ENTRY_free(ent);

  /* set public key in the certificate */
  if (X509_set_pubkey(certs[0], pkey) != 1)
    {
      mpcerror(debugfp,
      "GRSTx509MakeProxyCert(): error setting public key of the certificate\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }    

  /* set duration for the certificate */
  if (!(X509_gmtime_adj(X509_get_notBefore(certs[0]), -GRST_BACKDATE_SECONDS)))
    {
      mpcerror(debugfp,
      "GRSTx509MakeProxyCert(): error setting beginning time of the certificate\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }    

  if (!(X509_gmtime_adj(X509_get_notAfter(certs[0]), 60 * minutes)))
    {
      mpcerror(debugfp,
      "GRSTx509MakeProxyCert(): error setting ending time of the certificate\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }
    
  /* go through chain selecting the highest start-time*/

  notBefore = 
    GRSTasn1TimeToTimeT((char*)ASN1_STRING_data(X509_get_notBefore(certs[0])), 0);

  for (i=1; i < ncerts; ++i)
       if (notBefore < 
           GRSTasn1TimeToTimeT((char*)ASN1_STRING_data(X509_get_notBefore(certs[i])),
                               0))
         {
           notBefore = 
            GRSTasn1TimeToTimeT((char*)ASN1_STRING_data(X509_get_notBefore(certs[i])),
                                0);
            
           ASN1_UTCTIME_set(X509_get_notBefore(certs[0]), notBefore);
         }

  /* go through chain making sure this proxy is not longer lived */

  notAfter = 
    GRSTasn1TimeToTimeT((char*)ASN1_STRING_data(X509_get_notAfter(certs[0])), 0);

  for (i=1; i < ncerts; ++i)
       if (notAfter > 
           GRSTasn1TimeToTimeT((char*)ASN1_STRING_data(X509_get_notAfter(certs[i])),
                               0))
         {
           notAfter = 
            GRSTasn1TimeToTimeT((char*)ASN1_STRING_data(X509_get_notAfter(certs[i])),
                                0);
            
           ASN1_UTCTIME_set(X509_get_notAfter(certs[0]), notAfter);
         }

  /* sign the certificate with the signing private key */
  if (EVP_PKEY_type(CApkey->type) == EVP_PKEY_RSA)
    digest = EVP_md5();
  else
    {
      mpcerror(debugfp,
      "GRSTx509MakeProxyCert(): error checking signing private key for a valid digest\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }    

  if (!(X509_sign(certs[0], CApkey, digest)))
    {
      mpcerror(debugfp,
      "GRSTx509MakeProxyCert(): error signing certificate\n");

      X509_REQ_free(req);
      return GRST_RET_FAILED;
    }    

  /* store the completed certificate chain */

  certchain = strdup("");

  for (i=0; i < ncerts; ++i)
     {
       certmem = BIO_new(BIO_s_mem());

       if (PEM_write_bio_X509(certmem, certs[i]) != 1)
         {
           mpcerror(debugfp,
            "GRSTx509MakeProxyCert(): error writing certificate to memory BIO\n");            

           X509_REQ_free(req);
	   free( certchain );
	   BIO_free(certmem);
           return GRST_RET_FAILED;
         }

       ptrlen = BIO_get_mem_data(certmem, &ptr);
  
       certchain = (char*)realloc(certchain, strlen(certchain) + ptrlen + 1);
       
       strncat(certchain, ptr, ptrlen);
    
       BIO_free(certmem);
       X509_free(certs[i]);
     }
  
  EVP_PKEY_free(pkey);
  EVP_PKEY_free(CApkey);
  X509_REQ_free(req);
      
  *proxychain = certchain; 
  return GRST_RET_OK;
}

/**
 * END OF PATCH STUFF
 */


//____________________________________________________________________________________
 X509* glite::ce::cream_client_api::certUtil::read_BIO( const std::string& pxfile ) 
   throw(soapProxy::auth_ex&)
 {
   BIO *in = NULL;
   in = BIO_new(BIO_s_file());
   glite::ce::cream_client_api::helper_BIOnew h( in ); // smart container to 
   						      // free 'in' when leaving this scope
   if (in) {
     if (BIO_read_filename( in, pxfile.c_str() ) > 0) {

       X509* x = PEM_read_bio_X509(in, NULL, 0, NULL);
       if(!x) {
 	throw  soapProxy::auth_ex(std::string("certUtil::read_BIO() - PEM_read_bio_X509 failed while reading X509 proxy file: ")+ pxfile);
       }
      
       return x;

     } else {
       throw  soapProxy::auth_ex(std::string("certUtil::read_BIO() - BIO_read_filename failed while reading X509 proxy file: ")+ pxfile);
     }
   } else {
     throw  soapProxy::auth_ex(std::string("certUtil::read_BIO() - unable to allocate memory when creatin a BIO object with BIO_new() call, for the proxy file: ")+ pxfile);
   }
 }

//____________________________________________________________________________________
 std::string glite::ce::cream_client_api::certUtil::getDN(const std::string& pxfile) 
   throw(soapProxy::auth_ex&) 
 {
   BIO *in = NULL;
   X509 *x = NULL;
   std::string distinguished_name = "";
   in = BIO_new(BIO_s_file());
   glite::ce::cream_client_api::helper_BIOnew h( in ); // smart container to 
   						      // free 'in' when leaving this scope
  
   if (in) {
     if (BIO_read_filename( in, pxfile.c_str() ) > 0) {
       x = PEM_read_bio_X509(in, NULL, 0, NULL);
       glite::ce::cream_client_api::helper_X509new X(x); // smart container to free 'x'
       							// when leaving this scope    
       if (x) {
 	char *name = X509_NAME_oneline(X509_get_subject_name(x), NULL, 0);
 	if(name) {
 	  distinguished_name = name;
 	  free(name);
 	} else {
 	  throw soapProxy::auth_ex("X509_NAME_oneline returned a NULL pointer!");
 	}
       } else{
 	throw  soapProxy::auth_ex(std::string("unable to read X509 proxy file: ")+ pxfile);
       }
     } else {
       throw  soapProxy::auth_ex(std::string("unable to open X509 proxy file: ")+ pxfile);
     }
   } else {
     throw  soapProxy::auth_ex(std::string("unable to allocate memory for the proxy file: ")+ pxfile);
   }

   return distinguished_name;
 }

//____________________________________________________________________________________
std::string glite::ce::cream_client_api::certUtil::getCertSubj(const std::string& pxfile) 
   throw(soapProxy::auth_ex&) 
 {
   std::string Subject;

   X509 *x = glite::ce::cream_client_api::certUtil::read_BIO( pxfile ); // can raise a auth_ex
   glite::ce::cream_client_api::helper_X509new X(x);
   char *name = X509_NAME_oneline(X509_get_subject_name(x), NULL, 0);
   if(name) {
     Subject = name;
     free(name);
   } else {
     throw soapProxy::auth_ex("X509_NAME_oneline returned a NULL pointer!");
   }

   return Subject;
 }

//____________________________________________________________________________________
 const long int glite::ce::cream_client_api::certUtil::getProxyTimeLeft( const std::string& pxfile )
   throw (soapProxy::auth_ex&)
 {

     long int timeleft = 0;

     X509 *x = glite::ce::cream_client_api::certUtil::read_BIO( pxfile ); // can raise a auth_ex
     glite::ce::cream_client_api::helper_X509new X(x);
    
     timeleft = (long int)((long int)ASN1_UTCTIME_get(X509_get_notAfter(x)) - (long int)time(NULL) );
     return timeleft;
 }

/*************************************************************************
	private method:	converts ASN1_UTCTIME to time_t
*************************************************************************/
time_t glite::ce::cream_client_api::certUtil::ASN1_UTCTIME_get(const ASN1_UTCTIME *s)
{
  int offset;
  struct tm _tm;
  memset(&_tm,'\0',sizeof(struct tm));
#define g2(p) (((p)[0]-'0')*10+(p)[1]-'0')
  _tm.tm_year=g2(s->data);
  if(_tm.tm_year < 50)
    _tm.tm_year+=100;
  _tm.tm_mon=g2(s->data+2)-1;
  _tm.tm_mday=g2(s->data+4);
  _tm.tm_hour=g2(s->data+6);
  _tm.tm_min=g2(s->data+8);
  _tm.tm_sec=g2(s->data+10);
  if(s->data[12] == 'Z')
    offset=0;
  else
    {
      offset=g2(s->data+13)*60+g2(s->data+15);
      if(s->data[12] == '-')
 	offset= -offset;
    }
#undef g2
  
  return timegm(&_tm)-offset*60;
}

//___________________________________________________________________________________________
void glite::ce::cream_client_api::certUtil::generateUniqueID(std::string& target) throw()
{
  struct timeval Tv;
  struct timezone Tz;
  gettimeofday(&Tv, &Tz);
  char hname[1024];
  char* H;
  if(gethostname(hname, 1024)==-1)
    H = "";
  else
    H = hname;
   
  target = boost::str( boost::format("%d.%d-%d-%d-%s") % Tv.tv_sec % Tv.tv_usec % ::getuid() % ::getpid() % H); 
    
  SHA_CTX ctx;
  SHA1_Init( &ctx );
  //while ( ( nread = read( fd, buffer, 1024 ) ) > 0 ) {
  SHA1_Update( &ctx, target.c_str(), target.length() );
  //}
  unsigned char bin_sha1_digest[SHA_DIGEST_LENGTH];
  SHA1_Final( bin_sha1_digest, &ctx );
  
  
  target = "";
  bintostring( bin_sha1_digest, SHA_DIGEST_LENGTH, target );//std::string((char *)bin_sha1_digest);
  CREAM_SAFE_LOG(glite::ce::cream_client_api::util::creamApiLogger::instance()->getLogger()->infoStream() 
		   << "certUtil::generateUniqueID() - Generated DelegationID: ["
		   << target << "]"
		   );
}

//___________________________________________________________________________________________
void glite::ce::cream_client_api::certUtil::bintostring( unsigned char* buf, size_t len, std::string& result )
{
  const char alpha[] = "0123456789abcdef";
        
  for ( size_t i=0; i<len; ++i ) {
    result.push_back( alpha[ ( buf[i] >> 4 ) & 0x0f ] );
    result.push_back( alpha[ buf[i] & 0x0f ] );
  }
  
};
