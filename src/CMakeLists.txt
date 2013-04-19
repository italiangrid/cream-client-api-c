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

add_subdirectory(pkgconfig)

if(NOT DEFINED WSDL_PATH)
    message("Undefined variable WSDL_PATH, used /usr/share/wsdl/cream-ce")
    set(WSDL_PATH /usr/share/wsdl/cream-ce)
endif(NOT DEFINED WSDL_PATH)

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

link_directories(${VOMS_LIBRARY_DIRS}
                 ${GSOAP_LIBRARY_DIRS}
                 ${GRIDSITE_OPENSSL_LIBRARY_DIRS})

include_directories(${CLASSAD_INCLUDE_DIRS}
                    ${VOMS_INCLUDE_DIRS}
                    ${GSOAP_INCLUDE_DIRS}
                    ${LOG4CPP_INCLUDE_DIRS}
                    ${Boost_INCLUDE_DIRS}
                    ${GLOBUS_GSSAPI_GSI_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/interface
                    ${CMAKE_CURRENT_BINARY_DIR}/${AUTODIR})


add_custom_command(OUTPUT ${AUTODIR}/CREAM_CLIENTClient.cpp ${AUTODIR}/CREAM_CLIENTC.cpp
                   DEPENDS ${WSDL_PATH}/org.glite.ce-cream2_service.wsdl 
                           ${WSDL_PATH}/www.gridsite.org-delegation-2.0.0.wsdl
                   COMMAND mkdir -p ${AUTODIR}/glite/ce/cream-client-api-c
                   COMMAND wsdl2h -o ${AUTODIR}/glite/ce/cream-client-api-c/cream_service.h 
                                  -t ${CMAKE_CURRENT_SOURCE_DIR}/typemap.dat
                                  ${WSDL_PATH}/org.glite.ce-cream2_service.wsdl 
                                  ${WSDL_PATH}/www.gridsite.org-delegation-2.0.0.wsdl
                   COMMAND soapcpp2 -I/usr/include -I/usr/include/gsoap -I/usr/share/gsoap/import
                                    -p CREAM_CLIENT -n -d ${AUTODIR} ${AUTODIR}/glite/ce/cream-client-api-c/cream_service.h
                   COMMAND sed 's|CREAM_CLIENTH.h|glite/ce/cream-client-api-c/cream_client_soapH.h|g' ${AUTODIR}/CREAM_CLIENT.nsmap 
                           > ${AUTODIR}/glite/ce/cream-client-api-c/CREAM_CLIENT.nsmap
                   COMMAND cp ${AUTODIR}/CREAM_CLIENTStub.h ${AUTODIR}/glite/ce/cream-client-api-c/cream_client_soapStub.h
                   COMMAND sed 's|CREAM_CLIENTStub.h|glite/ce/cream-client-api-c/cream_client_soapStub.h|g' ${AUTODIR}/CREAM_CLIENTH.h
                           > ${AUTODIR}/glite/ce/cream-client-api-c/cream_client_soapH.h)

add_custom_target(cream_stubs ALL DEPENDS ${AUTODIR}/CREAM_CLIENTClient.cpp ${AUTODIR}/CREAM_CLIENTC.cpp)

add_library(glite_ce_cream_client_soap SHARED ${AUTODIR}/CREAM_CLIENTClient.cpp
                                              ${AUTODIR}/CREAM_CLIENTC.cpp
                                              ExceptionFactory.cpp
                                              JobInfoWrapper.cpp
                                              JobIdWrapper.cpp
                                              JobFilterWrapper.cpp
                                              JobCommandWrapper.cpp
                                              JobDescriptionWrapper.cpp
                                              JobStatusWrapper.cpp
                                              ServiceInfoWrapper.cpp
                                              ResultWrapper.cpp
                                              EventWrapper.cpp
                                              AbsCreamProxy.cpp
                                              CreamProxy_Register.cpp
                                              CreamProxy_Delegate.cpp
                                              CreamProxy_ProxyRenew.cpp
                                              CreamProxy_Start.cpp
                                              CreamProxy_Lease.cpp
                                              CreamProxy_LeaseInfo.cpp
                                              CreamProxy_Status.cpp
                                              CreamProxy_Info.cpp
                                              CreamProxy_Purge.cpp
                                              CreamProxy_Cancel.cpp
                                              CreamProxy_Suspend.cpp
                                              CreamProxy_Resume.cpp
                                              CreamProxy_List.cpp
                                              CreamProxy_ServiceInfo.cpp
                                              CreamProxy_AcceptNewJobSubmissions.cpp
                                              CreamProxy_QueryEvent.cpp)

set_target_properties(glite_ce_cream_client_soap PROPERTIES VERSION 0.0.0 SOVERSION 0)

target_link_libraries(glite_ce_cream_client_soap ${CLASSAD_LIBRARIES}
                                                 ${VOMS_LIBRARIES}
                                                 ${GSOAP_LIBRARIES}
                                                 ${LOG4CPP_LIBRARIES}
                                                 ${GRIDSITE_OPENSSL_LIBRARIES}
                                                 ${Boost_LIBRARIES})


add_library(glite_ce_cream_client_util SHARED CEUrl.cpp
                                              creamApiLogger.cpp
                                              job_statuses.cpp
                                              ConfigurationManager.cpp
                                              certUtil.cpp
                                              scoped_timer.cpp
                                              VOMSWrapper.cpp)

set_target_properties(glite_ce_cream_client_util PROPERTIES VERSION 0.0.0 SOVERSION 0)

target_link_libraries(glite_ce_cream_client_util ${CLASSAD_LIBRARIES}
                                                 ${VOMS_LIBRARIES}
                                                 ${GSOAP_LIBRARIES}
                                                 ${LOG4CPP_LIBRARIES}
                                                 ${GRIDSITE_OPENSSL_LIBRARIES}
                                                 ${Boost_LIBRARIES})

install(TARGETS glite_ce_cream_client_soap glite_ce_cream_client_util
        LIBRARY DESTINATION usr/${LIBSUBDIR})

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${AUTODIR}/glite/ce/cream-client-api-c/
        DESTINATION usr/include/glite/ce/cream-client-api-c
        FILES_MATCHING PATTERN "*.h")
        
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${AUTODIR}/glite/ce/cream-client-api-c/
        DESTINATION usr/include/glite/ce/cream-client-api-c
        FILES_MATCHING PATTERN "*.nsmap")

      
