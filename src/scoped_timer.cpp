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
 
#include "glite/ce/cream-client-api-c/scoped_timer.h"
#include "glite/ce/cream-client-api-c/creamApiLogger.h"
#include "boost/format.hpp"

using namespace glite::ce::cream_client_api::util;

scoped_timer::scoped_timer( const std::string& name ) :
    m_name( name ),
    m_log_dev( creamApiLogger::instance()->getLogger() )
{
    gettimeofday( &m_start_time, 0 );
}

scoped_timer::~scoped_timer( )
{
    struct timeval m_end_time;
    gettimeofday( &m_end_time, 0 );
    
    double tstart = (double)m_start_time.tv_sec + (double)m_start_time.tv_usec/(double)1000000.0;

    double tend = (double)m_end_time.tv_sec + (double)m_end_time.tv_usec/(double)1000000.0;

    double elapsed = tend - tstart;
    
    CREAM_SAFE_LOG(m_log_dev->infoStream()
                   << boost::format( "scoped_timer %s %f %f %f" ) % m_name % tstart % tend % elapsed
                   );
    
};

