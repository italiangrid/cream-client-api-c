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

if(NOT DEFINED WSDL_PATH)
    message(FATAL_ERROR "Missing wsdl path, please specify -DWSDL_PATH:string definition")
endif(NOT DEFINED WSDL_PATH)

if(NOT DEFINED PVER)
    message(WARNING "Undefined version number, selected 9.9.9")
    set(PVER "9.9.9")
endif(NOT DEFINED PVER)

if( ${CMAKE_VERSION} VERSION_LESS "2.8.2" )
    if( IS_DIRECTORY "/usr/lib64" )
        set(LIBSUBDIR "lib64")
    else( IS_DIRECTORY "/usr/lib64" )
        set(LIBSUBDIR "lib")
    endif( IS_DIRECTORY "/usr/lib64" )
else( ${CMAKE_VERSION} VERSION_LESS "2.8.2" )
    if( IS_DIRECTORY "/usr/lib64" AND NOT IS_SYMLINK "/usr/lib64" )
        set(LIBSUBDIR "lib64")
    else( IS_DIRECTORY "/usr/lib64" AND NOT IS_SYMLINK "/usr/lib64" )
        set(LIBSUBDIR "lib")
    endif( IS_DIRECTORY "/usr/lib64" AND NOT IS_SYMLINK "/usr/lib64" )
endif( ${CMAKE_VERSION} VERSION_LESS "2.8.2" )

if( NOT DEFINED BOOST_LIBRARYDIR AND IS_DIRECTORY "/usr/lib64" )
    set(BOOST_LIBRARYDIR "/usr/lib64")
endif( NOT DEFINED BOOST_LIBRARYDIR AND IS_DIRECTORY "/usr/lib64" )

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
set(AUTODIR "autogen")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSOAP gsoapssl++)
pkg_check_modules(LOG4CPP log4cpp)
pkg_check_modules(VOMS voms-2.0)
pkg_check_modules(GRIDSITE_OPENSSL emi-gridsite-openssl)
pkg_check_modules(CLASSAD emi-classad-ns)
pkg_check_modules(GLOBUS_GSSAPI_GSI globus-gssapi-gsi)

set(Boost_USE_MULTITHREADED ON)
find_package( Boost COMPONENTS date_time filesystem regex thread)

add_definitions( -pipe -DWANT_NAMESPACES -DWANT_CLASSAD_NAMESPACE )

add_subdirectory(src)
add_subdirectory(interface)
