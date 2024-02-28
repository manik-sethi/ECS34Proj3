#include <stdexcept>
#include <memory>
#include <vector>
#include <unordered_map>
#include "OpenStreetMap.h"
#include "XMLReader.h"
#include "StreetMap.h"


using namespace std;

// Define the struct SNode
struct COpenStreetMap::SNode : public CStreetMap::SNode {
    TNodeID id;
    TLocation location;

    SNode(TNodeID id, TLocation location) : id(id), location(location) {}

    TNodeID ID() const noexcept override { return id; }
    TLocation Location() const noexcept override { return location; }
    std::size_t AttributeCount() const noexcept override { return 0; }
    std::string GetAttributeKey(std::size_t index) const noexcept override { return ""; }
    bool HasAttribute(const std::string &key) const noexcept override { return false; }
    std::string GetAttribute(const std::string &key) const noexcept override { return ""; }

};

// Define the struct SWay
struct COpenStreetMap::SWay : public CStreetMap::SWay {
    TWayID id;
    std::vector<TNodeID> NodeIDs;

    SWay(TWayID id) : id(id) {}

    TWayID ID() const noexcept override { return id; }
    std::size_t NodeCount() const noexcept override { return NodeIDs.size(); }
    TNodeID GetNodeID(std::size_t index) const noexcept override {
        return index < NodeIDs.size() ? NodeIDs[index] : CStreetMap::InvalidNodeID;
    }
    std::size_t AttributeCount() const noexcept override { return 0; }
    std::string GetAttributeKey(std::size_t index) const noexcept override { return ""; }
    bool HasAttribute(const std::string &key) const noexcept override { return false; }
    std::string GetAttribute(const std::string &key) const noexcept override { return ""; }
};

// Constructor
COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src) : DImplementation(std::make_unique<SImplementation>()) {
    // Ensure src is not null
    if (!src) {
        throw std::invalid_argument("Null XML reader provided");
    }

    // Initialize XML reader
    DImplementation->XMLReader = src;

    // Parse the XML data and populate Nodes and Ways
    SXMLEntity Entity;
    std::string currentNodeName;
    std::vector<std::string> currentAttributes;

    // Loop to read XML entities until end of data source
    while (DImplementation->XMLReader->ReadEntity(Entity, false)) {
        // Check the entity type
        if (Entity.DType == SXMLEntity::EType::StartElement) {
            // Start element encountered
            currentNodeName = Entity.DNameData;
            currentAttributes.clear();
            for (const auto& attr : Entity.DAttributes) {
                currentAttributes.push_back(attr.first);
                currentAttributes.push_back(attr.second);
            }
        } else if (Entity.DType == SXMLEntity::EType::EndElement) {
            // End element encountered
            currentNodeName.clear();
            currentAttributes.clear();
        } else if (Entity.DType == SXMLEntity::EType::CharData && !currentNodeName.empty()) {
            // Character data encountered (inside an element)
            if (currentNodeName == "node") {
                // Parse node data and add to Nodes vector and NodesById map
                TNodeID id = std::stoul(Entity.DNameData);
                double lat, lon;
                for (size_t i = 0; i < currentAttributes.size(); i += 2) {
                    if (currentAttributes[i] == "lat") {
                        lat = std::stod(currentAttributes[i + 1]);
                    } else if (currentAttributes[i] == "lon") {
                        lon = std::stod(currentAttributes[i + 1]);
                    }
                }
                auto newNode = std::make_shared<SNode>(id, TLocation(lat, lon));
                DImplementation->Nodes.push_back(newNode);
                DImplementation->NodesById[id] = newNode;
            } else if (currentNodeName == "way") {
                // Parse way data and add to Ways vector and WaysById map
                TWayID id = std::stoul(Entity.DNameData);
                std::vector<TNodeID> nodeIDs;
                for (const auto& attr : currentAttributes) {
                    if (attr.substr(0, 5) == "node_") {
                        nodeIDs.push_back(std::stoul(attr.substr(5)));
                    }
                }
                auto newWay = std::make_shared<SWay>(id);

                DImplementation->Ways.push_back(newWay);
                DImplementation->WaysById[id] = newWay;
            }
        }
    }
}

// Destructor
COpenStreetMap::~COpenStreetMap() = default;

// Returns the number of nodes in the map
std::size_t COpenStreetMap::NodeCount() const noexcept {
    return DImplementation->Nodes.size();
}

// Returns the number of ways in the map
std::size_t COpenStreetMap::WayCount() const noexcept {
    return DImplementation->Ways.size();
}

// Returns the SNode associated with index, returns nullptr if index is larger than or equal to NodeCount()
std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByIndex(std::size_t index) const noexcept {
    return index < DImplementation->Nodes.size() ? DImplementation->Nodes[index] : nullptr;
}

// Returns the SNode with the id of id, returns nullptr if doesn't exist
std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByID(TNodeID id) const noexcept {
    auto it = DImplementation->NodesById.find(id);
    return it != DImplementation->NodesById.end() ? it->second : nullptr;
}

// Returns the SWay associated with index, returns nullptr if index is larger than or equal to WayCount()
std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByIndex(std::size_t index) const noexcept {
    return index < DImplementation->Ways.size() ? DImplementation->Ways[index] : nullptr;
}

// Returns the SWay with the id of id, returns nullptr if doesn't exist
std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByID(TWayID id) const noexcept {
    auto it = DImplementation->WaysById.find(id);
    return it != DImplementation->WaysById.end() ? it->second : nullptr;
}
