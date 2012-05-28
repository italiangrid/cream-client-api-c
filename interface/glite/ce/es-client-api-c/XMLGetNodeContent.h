#ifndef EMIES_CLIENTLIB_XML_GETNODECONTENT_H
#define EMIES_CLIENTLIB_XML_GETNODECONTENT_H

#include <string>

namespace emi_es {
  namespace client {
    namespace xml {
      
      class XMLDoc;

      class XMLGetNodeContent {

        friend class DeserializeActivityIdentification;
        friend class DeserializeApplicationExecutable;
        friend class DeserializeApplicationNotification;
        friend class DeserializeApplicationPrePostExecutable;
        friend class DeserializeApplicationInOutErr;
        friend class DeserializeApplicationEnvironment;
        friend class DeserializeResourcesOperatingSystem;
	friend class DeserializeResourcesRuntimeEnvironment;
	friend class DeserializeResourcesParallelEnvironment;
	friend class DeserializeResources;
	friend class DeserializeResourcesSlotRequirement;
        friend class DeserializeApplicationRemoteLogging;
        friend class DeserializeApplicationExpirationTime;
        friend class DeserializeApplicationWipeTime;
	friend class DeserializeInputFileSource;
	friend class DeserializeOutputFileTarget;
	friend class DeserializeInputFile;
	friend class DeserializeOutputFile;
        friend class DeserializeDataStaging;

      protected:
	static std::string* get(XMLDoc* doc, const char* xpath_expr );
      };
      
    }
  }
}


#endif
