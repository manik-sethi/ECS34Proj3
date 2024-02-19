#include "XMLWriter.h"
#include "XMLEntity.h"
#include "DataSink.h"
#include "DataSource.h"
#include "expat.h"
#include <queue>

// Define the implementation struct
struct CXMLWriter::SImplementation {
    std::shared_ptr<CDataSink> DDataSink;
    std::shared_ptr<CDataSource> DDataSource;
    XML_Parser DXMLParser;
    using EntityQueue = std::queue<SXMLEntity>; // Define the queue type using using directive
    EntityQueue DEntityQueue;

    // Start element handler function
    void StartElementHandler(const std::string &name, const std::vector<std::string> &attrs) {
        SXMLEntity TempEntity;
        TempEntity.DNameData = name;
        TempEntity.DType = SXMLEntity::EType::StartElement;
        for (size_t Index = 0; Index < attrs.size(); Index += 2) {
            TempEntity.SetAttribute(attrs[Index], attrs[Index + 1]);
        }
        DEntityQueue.push(TempEntity);
    }

    // End element handler function
    void EndElementHandler(const std::string &name) {
        SXMLEntity TempEntity;
        TempEntity.DNameData = name;
        TempEntity.DType = SXMLEntity::EType::EndElement;
        DEntityQueue.push(TempEntity);
    }

    // Character data handler callback function
    static void XMLCALL CharacterDataHandlerCallback(void *context, const XML_Char *s, int len) {
        SImplementation *WriterObject = static_cast<SImplementation *>(context);
        std::string data(s, len);
        SXMLEntity TempEntity;
        TempEntity.DNameData = data;
        TempEntity.DType = SXMLEntity::EType::CharData;
        WriterObject->DEntityQueue.push(TempEntity);
    }

    // Constructor
    SImplementation(std::shared_ptr<CDataSink> sink)
        : DDataSink(sink), DXMLParser(XML_ParserCreate(NULL)) {
        XML_SetStartElementHandler(DXMLParser, StartElementHandlerCallback);
        XML_SetEndElementHandler(DXMLParser, EndElementHandlerCallback);
        XML_SetCharacterDataHandler(DXMLParser, CharacterDataHandlerCallback);
        XML_SetUserData(DXMLParser, this);
    }

    // Destructor
    ~SImplementation() {
        XML_ParserFree(DXMLParser);
    }

    // Start element handler callback function
    static void XMLCALL StartElementHandlerCallback(void *context, const XML_Char *name, const XML_Char **atts) {
        SImplementation *WriterObject = static_cast<SImplementation *>(context);
        std::vector<std::string> Attributes;
        auto AttrPtr = atts;
        while (*AttrPtr) {
            Attributes.push_back(*AttrPtr);
            AttrPtr++;
        }
        WriterObject->StartElementHandler(name, Attributes);
    }

    // End element handler callback function
    static void XMLCALL EndElementHandlerCallback(void *context, const XML_Char *name) {
        SImplementation *WriterObject = static_cast<SImplementation *>(context);
        WriterObject->EndElementHandler(name);
    }
};

// Constructor
CXMLWriter::CXMLWriter(std::shared_ptr<CDataSink> sink)
    : DImplementation(std::make_unique<SImplementation>(sink)) {
    // Initialize your XML writer
}

// Destructor
CXMLWriter::~CXMLWriter() = default;

// Flush function
bool CXMLWriter::Flush() {
    // No need to flush if the data sink is not open
    if (!DImplementation->DDataSink) {
        return false;
    }
    // Retrieve any remaining data from the XML writer using the stored data source
    std::vector<char> remainingDataBuffer(256); // Assuming a buffer size of 1024 bytes

    while (DImplementation->DDataSource && !DImplementation->DDataSource->End()) {
        if (!DImplementation->DDataSource->Read(remainingDataBuffer, remainingDataBuffer.size())) {
            // Error reading from data source
            return false;
        }
        // Write the read data to the data sink
        if (!DImplementation->DDataSink->Write(remainingDataBuffer)) {
            // Error writing to data sink
            return false;
        }
    }

    // Return true to indicate success
    return true;
}

// Write entity function
bool CXMLWriter::WriteEntity(const SXMLEntity &entity) {
    // Check if data sink is initialized
    if (!DImplementation->DDataSink) {
        return false; // Data sink is not initialized
    }

    // Initialize XML parser
    XML_Parser parser = XML_ParserCreate(NULL);
    if (!parser) {
        return false; // Failed to create XML parser
    }

    // Set character data handler
    XML_SetCharacterDataHandler(parser, SImplementation::CharacterDataHandlerCallback);

    // Start element tag
    if (entity.DType == SXMLEntity::EType::StartElement) {
        std::string startTag = "<" + entity.DNameData;
        for (const auto &attr : entity.DAttributes) {
            startTag += " " + attr.first + "=\"" + attr.second + "\"";
        }
        startTag += ">";
        // Parse start element tag
        if (!XML_Parse(parser, startTag.c_str(), startTag.size(), 0)) {
            XML_ParserFree(parser);
            return false; // Failed to parse start element tag
        }
    }
    // End element tag
    else if (entity.DType == SXMLEntity::EType::EndElement) {
        std::string endTag = "</" + entity.DNameData + ">";
        // Parse end element tag
        if (!XML_Parse(parser, endTag.c_str(), endTag.size(), 1)) {
            XML_ParserFree(parser);
            return false; // Failed to parse end element tag
        }
    }
    // Complete element tag
    else if (entity.DType == SXMLEntity::EType::CompleteElement) {
        std::string completeTag = "<" + entity.DNameData;
        for (const auto &attr : entity.DAttributes) {
            completeTag += " " + attr.first + "=\"" + attr.second + "\"";
        }
        completeTag += "/>";
        // Parse complete element tag
        if (!XML_Parse(parser, completeTag.c_str(), completeTag.size(), 1)) {
            XML_ParserFree(parser);
            return false; // Failed to parse complete element tag
        }
    }
    // Character data
    else if (entity.DType == SXMLEntity::EType::CharData) {
        // Parse character data
        if (!XML_Parse(parser, entity.DNameData.c_str(), entity.DNameData.size(), 0)) {
            XML_ParserFree(parser);
            return false; // Failed to parse character data
        }
    }

    // Free XML parser
    XML_ParserFree(parser);

    // Return true to indicate success
    return true;
}
