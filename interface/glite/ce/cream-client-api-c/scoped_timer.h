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

#ifndef ICE_SCOPED_TIMER_H
#define ICE_SCOPED_TIMER_H

#include <string>
#include <sys/time.h>

namespace log4cpp {
    class Category;
}

namespace glite {
    namespace ce {
        namespace cream_client_api {
            namespace util {

                /**
                 * @brief Implementation of a scoped timer
                 *
                 * This class implements a "scoped timer", that is,
                 * instances of this class will log into the log file
                 * the time elapsed from their creation to their
                 * description. Thus, this class can be used to have a
                 * rough estimate of the time spent inside a given
                 * scope.
                 *
                 * Example:
                 *
                 * {
                 *   scoped_timer my_timer( "foo" );
                 *   ...
                 *   ...
                 * } // at this point, a message is logged in the log file
                 * // scoped_timer foo xxx
                 * // where xxx is the elapese time in seconds; 
                 * // the elapsed time is a floating point number.
                 */
                class scoped_timer {
                protected:
                    const std::string m_name;
                    struct timeval m_start_time;
                    log4cpp::Category  *m_log_dev;
                public:

                    /**
                     * Creates a scoped timer with a given name. The name
                     * will appear in the log file. The creation time is
                     * set to the current time.
                     *
                     * @param name The name given to this timer. The name
                     * is only used to display the result in the log file,
                     * so no check for uniqueness is performed.
                     */
                    scoped_timer( const std::string& name );
                    
                    /**
                     * The descructor displays in the log file (at
                     * INFO level) the string "scoped_timer", followed
                     * by the timer name (i.e., the string used in the
                     * costructor), followed by the elapsed time since
                     * creation, in seconds.
                     */
                    virtual ~scoped_timer( );
                };

            } // namespace util
        } // namespace cream-client-api-c
    } // namespace ce
}; // namespace glite

#endif
