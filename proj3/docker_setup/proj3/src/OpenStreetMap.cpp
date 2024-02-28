#include <memory>
#include <vector>
#include <unordered_map>
#include "StreetMap.h"
#include "OpenStreetMap.h"
#include "XMLReader.h"

using namespace std;

// Full definition of SNode struct
struct SNode : public CStreetMap::SNode {
    CStreetMap::TNodeID id;
    CStreetMap::TLocation location;

    SNode(CStreetMap::TNodeID id, CStreetMap::TLocation location) : id(id), location(location) {}

    CStreetMap::TNodeID ID() const noexcept override { return id; }
    CStreetMap::TLocation Location() const noexcept override { return location; }
    std::size_t AttributeCount() const noexcept override { return 0; }
    std::string GetAttributeKey(std::size_t index) const noexcept override { return ""; }
    bool HasAttribute(const std::string &key) const noexcept override { return false; }
    std::string GetAttribute(const std::string &key) const noexcept override { return ""; }
};

// Full definition of SWay struct
struct SWay : public CStreetMap::SWay {
    CStreetMap::TWayID id;
    std::vector<CStreetMap::TNodeID> NodeIDs; // Added NodeIDs member

    SWay(CStreetMap::TWayID id) : id(id) {}

    CStreetMap::TWayID ID() const noexcept override { return id; }
    std::size_t NodeCount() const noexcept override { return NodeIDs.size(); }
    CStreetMap::TNodeID GetNodeID(std::size_t index) const noexcept override {
        return index < NodeIDs.size() ? NodeIDs[index] : CStreetMap::InvalidNodeID;
    }
    std::size_t AttributeCount() const noexcept override { return 0; }
    std::string GetAttributeKey(std::size_t index) const noexcept override { return ""; }
    bool HasAttribute(const std::string &key) const noexcept override { return false; }
    std::string GetAttribute(const std::string &key) const noexcept override { return ""; }
};

// Definition of COpenStreetMap class and its implementation
class COpenStreetMap : public CStreetMap {
public:
    // Constructor
    COpenStreetMap(std::shared_ptr<CXMLReader> src);

    // Destructor
    ~COpenStreetMap() override;

    // Implementation of virtual functions
    std::size_t NodeCount() const noexcept override;
    std::size_t WayCount() const noexcept override;
    std::shared_ptr<CStreetMap::SNode> NodeByIndex(std::size_t index) const noexcept override;
    std::shared_ptr<CStreetMap::SNode> NodeByID(TNodeID id) const noexcept override;
    std::shared_ptr<CStreetMap::SWay> WayByIndex(std::size_t index) const noexcept override;
    std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const noexcept override;

private:
    struct SImplementation {
        std::vector<std::shared_ptr<CStreetMap::SNode>> Nodes;
        std::unordered_map<CStreetMap::TNodeID, std::shared_ptr<CStreetMap::SNode>> NodesById;
        std::vector<std::shared_ptr<CStreetMap::SWay>> Ways;
        std::unordered_map<CStreetMap::TWayID, std::shared_ptr<CStreetMap::SWay>> WaysById;
        std::shared_ptr<CXMLReader> XMLReader;
    };

    std::unique_ptr<SImplementation> DImplementation;
};

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
                CStreetMap::TNodeID id = std::stoul(Entity.DNameData);
                double lat, lon;
                for (size_t i = 0; i < currentAttributes.size(); i += 2) {
                    if (currentAttributes[i] == "lat") {
                        lat = std::stod(currentAttributes[i + 1]);
                    } else if (currentAttributes[i] == "lon") {
                        lon = std::stod(currentAttributes[i + 1]);
                    }
                }
                auto newNode = std::make_shared<SNode>(id, CStreetMap::TLocation(lat, lon));
                DImplementation->Nodes.push_back(newNode);
                DImplementation->NodesById[id] = newNode;
            } else if (currentNodeName == "way") {
                // Parse way data and add to Ways vector and WaysById map
                CStreetMap::TWayID id = std::stoul(Entity.DNameData);
                std::vector<CStreetMap::TNodeID> nodeIDs;
                for (const auto& attr : currentAttributes) {
                    if (attr.substr(0, 5) == "node_") {
                        nodeIDs.push_back(std::stoul(attr.substr(5)));
                    }
                }
                auto newWay = std::make_shared<SWay>(id);
                newWay->NodeIDs = nodeIDs;
                DImplementation->Ways.push_back(newWay);
                DImplementation->WaysById[id] = newWay;
            }
        }
    }
}

COpenStreetMap::~COpenStreetMap() = default;

std::size_t COpenStreetMap::NodeCount() const noexcept {
    return DImplementation->Nodes.size();
}

std::size_t COpenStreetMap::WayCount() const noexcept {
    return DImplementation->Ways.size();
}

std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByIndex(std::size_t index) const noexcept {
    return index < DImplementation->Nodes.size() ? DImplementation->Nodes[index] : nullptr;
}

std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByID(CStreetMap::TNodeID id) const noexcept {
    auto it = DImplementation->NodesById.find(id);
    return it != DImplementation->NodesById.end() ? it->second : nullptr;
}

std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByIndex(std::size_t index) const noexcept {
    return index < DImplementation->Ways.size() ? DImplementation->Ways[index] : nullptr;
}

std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByID(CStreetMap::TWayID id) const noexcept {
    auto it = DImplementation->WaysById.find(id);
    return it != DImplementation->WaysById.end() ? it->second : nullptr;
}
