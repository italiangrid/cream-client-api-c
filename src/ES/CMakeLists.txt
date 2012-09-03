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

find_package(LibXml2 REQUIRED)

link_directories(${VOMS_LIBRARY_DIRS}
                 ${GSOAP_LIBRARY_DIRS}
                 ${GRIDSITE_OPENSSL_LIBRARY_DIRS})

include_directories(${CLASSAD_INCLUDE_DIRS}
                    ${VOMS_INCLUDE_DIRS}
                    ${GSOAP_INCLUDE_DIRS}
                    ${LOG4CPP_INCLUDE_DIRS}
                    ${Boost_INCLUDE_DIRS}
                    ${LIBXML2_INCLUDE_DIR}
                    ${PROJECT_SOURCE_DIR}/interface
                    ${CMAKE_CURRENT_BINARY_DIR}/${AUTODIR})


add_custom_command(OUTPUT ${AUTODIR}/ES_CLIENTClient.cpp ${AUTODIR}/ES_CLIENTC.cpp
                   DEPENDS ${WSDL_PATH}/es/Creation.wsdl
                           ${WSDL_PATH}/es/Creation.xsd
                           ${WSDL_PATH}/es/ActivityManagement.wsdl
                           ${WSDL_PATH}/es/ActivityManagement.xsd
                           ${WSDL_PATH}/es/ActivityInfo.wsdl
                           ${WSDL_PATH}/es/ActivityInfo.xsd
                           ${WSDL_PATH}/es/Delegation.wsdl
                           ${WSDL_PATH}/es/Delegation.xsd
                           ${WSDL_PATH}/es/ResourceInfo.wsdl
                           ${WSDL_PATH}/es/ResourceInfo.xsd
                           ${WSDL_PATH}/es/es-activity-description.xsd
                           ${WSDL_PATH}/es/es-main.xsd
                           ${WSDL_PATH}/es/GLUE2.xsd
                   COMMAND mkdir -p ${AUTODIR}/glite/ce/es-client-api-c
                   COMMAND wsdl2h -o ${AUTODIR}/glite/ce/es-client-api-c/es_service.h
                                  -t ${CMAKE_CURRENT_SOURCE_DIR}/typemap.dat
                                  ${WSDL_PATH}/es/Creation.wsdl
                                  ${WSDL_PATH}/es/ActivityManagement.wsdl
                                  ${WSDL_PATH}/es/ActivityInfo.wsdl
                                  ${WSDL_PATH}/es/Delegation.wsdl
                                  ${WSDL_PATH}/es/ResourceInfo.wsdl
                   COMMAND soapcpp2 -I/usr/include -I/usr/include/gsoap -I/usr/share/gsoap/import
                                    -p ES_CLIENT -n -d ${AUTODIR} -e ${AUTODIR}/glite/ce/es-client-api-c/es_service.h
                   COMMAND sed 's|ES_CLIENTH.h|glite/ce/es-client-api-c/es_client_soapH.h|g' ${AUTODIR}/ES_CLIENT.nsmap 
                           > ${AUTODIR}/glite/ce/es-client-api-c/ES_CLIENT.nsmap
                   COMMAND cp ${AUTODIR}/ES_CLIENTStub.h ${AUTODIR}/glite/ce/es-client-api-c/es_client_soapStub.h
                   COMMAND sed 's|ES_CLIENTStub.h|glite/ce/es-client-api-c/es_client_soapStub.h|g' ${AUTODIR}/ES_CLIENTH.h
                           > ${AUTODIR}/glite/ce/es-client-api-c/es_client_soapH.h)

add_custom_target(es_stubs ALL DEPENDS ${AUTODIR}/ES_CLIENTClient.cpp ${AUTODIR}/ES_CLIENTC.cpp)

add_library(glite_ce_es_client SHARED ${AUTODIR}/ES_CLIENTClient.cpp
                                      ${AUTODIR}/ES_CLIENTC.cpp
                                      ActivityCreationResponse.cpp
                                      ActivityDescription.cpp
                                      ActivityIdentification.cpp
                                      ActivityStatus.cpp
                                      Application.cpp
                                      ComputingActivityAssociations.cpp
                                      ComputingActivity.cpp
                                      CoprocessorType.cpp
                                      CreateActivities.cpp
                                      CreateActivitiesResponse.cpp
                                      DataStaging.cpp
                                      ExecutableType.cpp
                                      ExtensionsType.cpp
                                      GetActivityInfoResponse.cpp
                                      GetActivityStatusResponse.cpp
                                      InitDelegation.cpp
                                      InputFile.cpp
                                      InternalBaseFault.cpp
                                      ListActivities.cpp
                                      NetworkInfoType.cpp
                                      Notification.cpp
                                      NotifyService.cpp
                                      OperatingSystem.cpp
                                      OutputFile.cpp
                                      ParallelEnvironment.cpp
                                      RemoteLoggingWrapper.cpp
                                      Resources.cpp
                                      RuntimeEnvironment.cpp
                                      SlotRequirement.cpp
                                      Source.cpp
                                      Target.cpp
                                      AbstractCall.cpp
                                      CallFactory.cpp
                                      CancelActivityCall.cpp
                                      CreateActivityCall.cpp
                                      GetActivityInfoCall.cpp
                                      GetActivityStatusCall.cpp
                                      GetDelegationInfoCall.cpp
                                      InitDelegationCall.cpp
                                      ListActivityCall.cpp
                                      ManageActivityCall.cpp
                                      NotifyServiceCall.cpp
                                      PauseActivityCall.cpp
                                      PutDelegationCall.cpp
                                      RestartActivityCall.cpp
                                      ResumeActivityCall.cpp
                                      WipeActivityCall.cpp
                                      util.cpp
                                      XMLGetNodeCount.cpp
                                      XMLGetNodeContent.cpp
                                      XMLGetMultipleNodeContent.cpp
                                      XMLDoc.cpp
                                      DeserializeApplicationPrePostExecutable.cpp
                                      DeserializeApplicationExecutable.cpp
                                      DeserializeApplicationInOutErr.cpp
                                      DeserializeApplicationEnvironment.cpp
                                      DeserializeActivityIdentification.cpp
                                      DeserializeApplicationRemoteLogging.cpp
                                      DeserializeApplicationExpirationTime.cpp
                                      DeserializeApplicationWipeTime.cpp
                                      DeserializeApplicationNotification.cpp
                                      DeserializeResourcesOperatingSystem.cpp
                                      DeserializeApplication.cpp
                                      DeserializeInputFileSource.cpp
                                      DeserializeInputFile.cpp
                                      DeserializeOutputFileTarget.cpp
                                      DeserializeOutputFile.cpp
                                      DeserializeDataStaging.cpp
                                      DeserializeResourcesRuntimeEnvironment.cpp
                                      DeserializeResourcesParallelEnvironment.cpp
                                      DeserializeResourcesSlotRequirement.cpp
                                      DeserializeResources.cpp
                                      CreateActivityDescriptionFromXML.cpp)

set_target_properties(glite_ce_es_client PROPERTIES VERSION 0.0.0 SOVERSION 0)

target_link_libraries(glite_ce_es_client ${CLASSAD_LIBRARIES}
                                         ${VOMS_LIBRARIES}
                                         ${GSOAP_LIBRARIES}
                                         ${LOG4CPP_LIBRARIES}
                                         ${GRIDSITE_OPENSSL_LIBRARIES}
                                         ${Boost_LIBRARIES}
                                         ${LIBXML2_LIBRARIES})


install(TARGETS glite_ce_es_client
        LIBRARY DESTINATION usr/${LIBSUBDIR})

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${AUTODIR}/glite/ce/es-client-api-c/
        DESTINATION usr/include/glite/ce/es-client-api-c
        FILES_MATCHING PATTERN "*.h")

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${AUTODIR}/glite/ce/es-client-api-c/
        DESTINATION usr/include/glite/ce/es-client-api-c
        FILES_MATCHING PATTERN "*.nsmap")

