#
#  Copyright (c) Members of the EGEE Collaboration. 2010.
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

project(cream-client-api-c CXX)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

set(PKGNAME glite-ce-cream-client-api-c)
set(PKGVER 1.15.5)
set(PKGREL 1)

set(ITEMS_FOR_SOURCE CMakeLists.txt interface src cmake_modules)

add_custom_target(rpm 
                  COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/BUILD
                                   ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/RPMS
                                   ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/SOURCES
                                   ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/SPECS
                                   ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/SRPMS
                  COMMAND tar -zcf ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/SOURCES/${PKGNAME}.tar.gz ${ITEMS_FOR_SOURCE}
                  COMMAND sed -e 's|@PKGVERSION@|${PKGVER}|g'
                              -e 's|@PKGRELEASE@|${PKGREL}|g' 
                              project/${PKGNAME}.spec.in > ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/SPECS/${PKGNAME}.spec
                  COMMAND rpmbuild -ba --define '_topdir ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild'
                          ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/SPECS/${PKGNAME}.spec
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
if(DEFINED SL6) 
  add_definitions( -DSL6 )
endif(DEFINED SL6)


add_subdirectory(src)
add_subdirectory(interface)
add_subdirectory(cmake_modules)

