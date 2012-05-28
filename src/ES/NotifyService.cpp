#include "glite/ce/es-client-api-c/NotifyService.h"
#include <boost/lexical_cast.hpp>
#include "glite/ce/es-client-api-c/util.h"


using namespace std;

namespace wr = emi_es::client::wrapper;
namespace util = emi_es::client::util;

/**
 *
 *
 *
 *
 *
 *
 */
wr::NotifyService::NotifyService( const vector<NotifyRequestItemType>& items )
{
  vector<NotifyRequestItemType>::const_iterator it = items.begin( );
  for( ; it != items.end( ); ++it ) {
    NotifyRequestItemType *item = new NotifyRequestItemType( );
    item->ActivityIDField = it->ActivityIDField;
    item->NotifyMessage = it->NotifyMessage;
    NotifyRequestItemField.push_back( item );
  }
}

/**
 *
 *
 *
 *
 *
 *
 */
void
wr::NotifyService::set( const NotifyService& src ) {
  vector<NotifyRequestItemType*>::const_iterator it = src.NotifyRequestItemField.begin( );
  for( ; it != src.NotifyRequestItemField.end( ); ++it ) {
    NotifyRequestItemType *item = new NotifyRequestItemType( );
    item->ActivityIDField = (*it)->ActivityIDField;
    item->NotifyMessage = (*it)->NotifyMessage;
    NotifyRequestItemField.push_back( item );
  }
}

/**
 *
 *
 *
 *
 *
 *
 */
void
wr::NotifyService::free( ) {
  vector<NotifyRequestItemType*>::const_iterator it = NotifyRequestItemField.begin( );
  for( ; it != NotifyRequestItemField.end( ); ++it ) {
    delete *it;
  }
  NotifyRequestItemField.clear( );
}
