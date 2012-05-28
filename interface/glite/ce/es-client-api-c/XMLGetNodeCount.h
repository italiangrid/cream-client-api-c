#ifndef EMIES_CLIENTLIB_XML_GETNODECOUNT_H
#define EMIES_CLIENTLIB_XML_GETNODECOUNT_H

namespace emi_es {
  namespace client {

    class CreateActivityDescriptionFromXML;

    namespace xml {
      
      class XMLDoc;

      class XMLGetNodeCount {

	friend class emi_es::client::CreateActivityDescriptionFromXML;
	friend class DeserializeApplication;
	friend class DeserializeApplicationEnvironment;
	friend class DeserializeApplicationExecutable;
	friend class DeserializeApplicationNotification;
	friend class DeserializeApplicationPrePostExecutable;
	friend class DeserializeApplicationRemoteLogging;
	friend class DeserializeResourcesOperatingSystem;
	friend class DeserializeResourcesRuntimeEnvironment;
	friend class DeserializeResourcesParallelEnvironment;
	friend class DeserializeActivityIdentification;
	friend class DeserializeInputFileSource;
	friend class DeserializeOutputFileTarget;
	friend class DeserializeInputFile;
	friend class DeserializeOutputFile;
	friend class DeserializeDataStaging;	
	friend class DeserializeResources;
	friend class DeserializeResourcesSlotRequirement;
	
      protected:
	static int get(XMLDoc* doc, const char* xpath_expr );
      };
      
    }
  }
}


#endif
