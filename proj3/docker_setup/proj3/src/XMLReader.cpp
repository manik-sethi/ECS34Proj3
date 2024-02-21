#include "XMLReader.h"
#include "StringDataSource.h"
#include <expat.h>
#include <queue>
#include <iostream>

// Structure to hold implementation details
struct CXMLReader::SImplementation {
    std::shared_ptr<CDataSource> DDataSource;
    XML_Parser DXMLParser;
    std::queue<SXMLEntity> DEntityQueue;

    // Constructor
    SImplementation(std::shared_ptr<CDataSource> src) : DDataSource(src) {
        DXMLParser = XML_ParserCreate(NULL);
        XML_SetStartElementHandler(DXMLParser, StartElementHandlerCallback);
        XML_SetEndElementHandler(DXMLParser, EndElementHandlerCallback);
        XML_SetCharacterDataHandler(DXMLParser, CharacterDataHandlerCallback);
        XML_SetUserData(DXMLParser, this);
    }

    // Destructor
    ~SImplementation() {
        XML_ParserFree(DXMLParser);
    }

    // Handler for XML start elements
    void StartElementHandler(const std::string &name, const std::vector<std::string> &attrs) {
        SXMLEntity TempEntity;
        TempEntity.DNameData = name;
        TempEntity.DType = SXMLEntity::EType::StartElement;

        for (size_t Index = 0; Index < attrs.size(); Index += 2) {
            TempEntity.SetAttribute(attrs[Index], attrs[Index + 1]);
        }

        DEntityQueue.push(TempEntity);
    }

    // Handler for XML end elements
    void EndElementHandler(const std::string &name) {
        SXMLEntity TempEntity;
        TempEntity.DNameData = name;
        TempEntity.DType = SXMLEntity::EType::EndElement;
        DEntityQueue.push(TempEntity);
    }

    // Handler for XML character data
    void CharacterDataHandler(const std::string &cdata, bool skipcdata) {
		if (!skipcdata) {
			SXMLEntity TempEntity;
			TempEntity.DNameData = cdata;
			TempEntity.DType = SXMLEntity::EType::CharData;
			DEntityQueue.push(TempEntity);
		}
	}

    // Static callback for XML start element handler
    static void StartElementHandlerCallback(void *context, const XML_Char *name, const XML_Char **atts) {
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);
        std::vector<std::string> Attributes;
        auto AttrPtr = atts;
        while (*AttrPtr) {
            Attributes.push_back(*AttrPtr);
            AttrPtr++;
        }
        ReaderObject->StartElementHandler(name, Attributes);
    };

    // Static callback for XML end element handler
    static void EndElementHandlerCallback(void *context, const XML_Char *name) {
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);
        ReaderObject->EndElementHandler(name);
    };

    // Static callback for XML character data handler
    static void XMLCALL CharacterDataHandlerCallback(void *context, const XML_Char *s, int len) {
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);
        ReaderObject->CharacterDataHandler(std::string(s,len), false);
    }

    // Check if end of data source is reached
    bool End() const {
        return DEntityQueue.empty();
    }

    // Read XML entity from data source
    bool ReadEntity(SXMLEntity &entity, bool skipcdata);
};

// Read XML entity from data source
bool CXMLReader::SImplementation::ReadEntity(SXMLEntity &entity, bool skipcdata) {
    std::vector<char> DataBuffer;
    while (DEntityQueue.empty()) {
        if (DDataSource->Read(DataBuffer, 256)) {
            XML_Parse(DXMLParser, DataBuffer.data(), DataBuffer.size(), DataBuffer.size() < 256);
        } else {
            XML_Parse(DXMLParser, DataBuffer.data(), 0, true);
        }
    }

    if (!DEntityQueue.empty()) {
        entity = DEntityQueue.front();

        // Check for the end of CDATA and adjust accordingly
        if (entity.DType == SXMLEntity::EType::EndElement && !skipcdata) {
            if (!DEntityQueue.empty() && DEntityQueue.front().DType == SXMLEntity::EType::CharData) {
                DEntityQueue.pop();
                entity = DEntityQueue.front();
            }
        } else {
            DEntityQueue.pop();
        }

        return true;
    }

    return false;
}

// Constructor
CXMLReader::CXMLReader(std::shared_ptr<CDataSource> src) {
    DImplementation = std::make_unique<SImplementation>(src);
}

// Destructor
CXMLReader::~CXMLReader() {
}

// Check if end of data source is reached
bool CXMLReader::End() const {
    return DImplementation->End();
}

// Read XML entity from data source
bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata) {
    return DImplementation->ReadEntity(entity, skipcdata);
}
