#include "glite/ce/es-client-api-c/DeserializeApplication.h"
#include "glite/ce/es-client-api-c/Application.h"
#include "glite/ce/es-client-api-c/XMLDoc.h"
#include "glite/ce/es-client-api-c/XMLGetNodeCount.h"
#include "glite/ce/es-client-api-c/ExecutableType.h"
#include "glite/ce/es-client-api-c/DeserializeApplicationExecutable.h"
#include "glite/ce/es-client-api-c/DeserializeApplicationEnvironment.h"
#include "glite/ce/es-client-api-c/DeserializeApplicationPrePostExecutable.h"
#include "glite/ce/es-client-api-c/DeserializeApplicationRemoteLogging.h"
#include "glite/ce/es-client-api-c/DeserializeApplicationExpirationTime.h"
#include "glite/ce/es-client-api-c/DeserializeApplicationWipeTime.h"
#include "glite/ce/es-client-api-c/DeserializeApplicationNotification.h"
#include "glite/ce/es-client-api-c/DeserializeApplicationInOutErr.h"
#include "glite/ce/es-client-api-c/Notification.h"
#include "glite/ce/es-client-api-c/typedefs.h"

#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
namespace xml = emi_es::client::xml;
namespace wrapper = emi_es::client::wrapper;


/**
 *
 *
 *
 *
 *
 *
 */
wrapper::Application*
xml::DeserializeApplication::get( XMLDoc* doc, const int adIndex )
{
  char* buf = (char*)malloc(1024);
  boost::scoped_ptr< char > buf_safe_ptr( buf );
  /**
   * First must check that the Application tag is there
   */
  memset( (void*)buf, 0, 1024 );
  sprintf( buf, "//ActivityDescription[%d]/Application", adIndex );
  if(!XMLGetNodeCount::get( doc, buf ))
    return 0;

  /**
   * Get Executable tag
   */
  wrapper::ExecutableType *exe = DeserializeApplicationExecutable::get( doc, adIndex );
  boost::scoped_ptr< wrapper::ExecutableType > exe_safe_ptr( exe );

  vector<OptionType> opts;
  DeserializeApplicationEnvironment::get( doc, opts, adIndex );

  vector<wrapper::ExecutableType> PRE;
  vector<wrapper::ExecutableType> POST;
  DeserializeApplicationPrePostExecutable::get( doc, PRE, POST, adIndex );

  vector<wrapper::RemoteLoggingWrapper> RL;
  DeserializeApplicationRemoteLogging::get( doc, RL, adIndex );

  OptionalTime *exp = DeserializeApplicationExpirationTime::get( doc, adIndex );
  OptionalDuration *wipe = DeserializeApplicationWipeTime::get( doc, adIndex );
  boost::scoped_ptr< OptionalTime > exp_safe_ptr( exp );
  boost::scoped_ptr< OptionalDuration > wipe_safe_ptr( wipe );

  vector<wrapper::Notification> notifs;
  DeserializeApplicationNotification::get( doc, notifs, adIndex );
  
  boost::tuple<string*, string*, string*> inouterr = 
    DeserializeApplicationInOutErr::get( doc, adIndex );
  boost::scoped_ptr< string > in_safe_ptr( inouterr.get<0>() );
  boost::scoped_ptr< string > out_safe_ptr( inouterr.get<1>() );
  boost::scoped_ptr< string > err_safe_ptr( inouterr.get<2>() );
  
  return new wrapper::Application( exe, inouterr.get<0>(), inouterr.get<1>(), inouterr.get<2>(), opts, PRE, POST, RL, exp, wipe, notifs );
}
