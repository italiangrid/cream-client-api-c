#  See http://www.eu-egee.org/partners/ for details on the copyright
#  holders.
#  
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#  
#     http://www.apache.org/licenses/LICENSE-2.0
#  
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
#  implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#  

message("-- checking for module 'GLiteGridsite'")
find_path(GRIDSITE_INCLUDE_DIR
          NAMES gridsite.h
          PATHS /usr/include)

find_library(GRIDSITE_LIBRARY
             NAMES gridsite
             PATHS /usr/lib /usr/lib64)

set(GRIDSITE_INCLUDE_DIRS ${GRIDSITE_INCLUDE_DIR})
set(GRIDSITE_LIBRARIES ${GRIDSITE_LIBRARY})

if(GRIDSITE_LIBRARIES AND GRIDSITE_INCLUDE_DIRS)
    message("--   found  GLiteGridsite")
    message("--   GRIDSITE_INCLUDE_DIRS: ${GRIDSITE_INCLUDE_DIRS}")
    message("--   GRIDSITE_LIBRARIES: ${GRIDSITE_LIBRARIES}")
    set(GRIDSITE_FOUND TRUE)
else(GRIDSITE_LIBRARIES AND GRIDSITE_INCLUDE_DIRS)
    message("--   GLiteGridsite not found")
    set(GRIDSITE_FOUND FALSE)
endif(GRIDSITE_LIBRARIES AND GRIDSITE_INCLUDE_DIRS)
