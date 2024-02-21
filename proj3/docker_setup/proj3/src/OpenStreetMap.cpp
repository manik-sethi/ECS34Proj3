#include <StreetMap.h>
#include <OpenStreetMap.h>
#include <XMLReader.h>
#include <XMLWriter.h>
#include <StringDataSink.h>
#include <StringDataSource.h>
#include <StringUtils.h>
#include <stdlib.h>
#include <unordered_map>
#include <iostream>

// Include necessary headers

struct COpenStreetMap::SImplementation {
    std::vector<std::shared_ptr<CStreetMap::SNode>> Nodes;
    std::unordered_map<CStreetMap::TNodeID, std::shared_ptr<CStreetMap::SNode>> NodesById;
    std::vector<std::shared_ptr<CStreetMap::SWay>> Ways;
    std::unordered_map<CStreetMap::TWayID, std::shared_ptr<CStreetMap::SWay>> WaysById;

    // Struct representing a node
    struct SNode : public CStreetMap::SNode {
        CStreetMap::TNodeID id;
        CStreetMap::TLocation Location_;
        std::unordered_map<std::string, std::string> Attributes;

        // Constructor
        SNode(CStreetMap::TNodeID id, CStreetMap::TLocation location) : id(id), Location_(location) {}

        // Methods to retrieve node information
        CStreetMap::TNodeID ID() const noexcept override { return id; }

        CStreetMap::TLocation Location() const noexcept override {
            return Location_;
        }

        std::size_t AttributeCount() const noexcept override {
            return Attributes.size();
        }

        std::string GetAttributeKey(std::size_t index) const noexcept override {
            if (index < Attributes.size()) {
                auto it = std::next(Attributes.begin(), index);
                return it->first;
            }
            return "";
        }

        bool HasAttribute(const std::string &key) const noexcept override {
            return Attributes.find(key) != Attributes.end();
        }

        std::string GetAttribute(const std::string &key) const noexcept override {
            auto it = Attributes.find(key);
            if (it != Attributes.end()) {
                return it->second;
            }
            return "";
        }
    };


    // Struct representing a way
    struct SWay : public CStreetMap::SWay {
        CStreetMap::TWayID id;
        std::vector<CStreetMap::TNodeID> NodeIDs;
        std::unordered_map<std::string, std::string> Attributes;

        // Constructor
        SWay(CStreetMap::TWayID id) : id(id) {}

        // Methods to retrieve way information
        CStreetMap::TWayID ID() const noexcept override { return id; }
        std::size_t NodeCount() const noexcept override {
            return NodeIDs.size();
        }

        CStreetMap::TNodeID GetNodeID(std::size_t index) const noexcept override {
            if (index < NodeIDs.size()) {
                return NodeIDs[index];
            }
            return CStreetMap::InvalidNodeID;
        }

        std::size_t AttributeCount() const noexcept override {
            return Attributes.size();
        }

        std::string GetAttributeKey(std::size_t index) const noexcept override {
            if (index < Attributes.size()) {
                auto it = std::next(Attributes.begin(), index);
                return it->first;
            }
            return "";
        }

        bool HasAttribute(const std::string &key) const noexcept override {
            return Attributes.find(key) != Attributes.end();
        }

        std::string GetAttribute(const std::string &key) const noexcept override {
            auto it = Attributes.find(key);
            if (it != Attributes.end()) {
                return it->second;
            }
            return "";
        }
    };
};

// Constructor
// Constructor
COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src) : DImplementation(std::make_unique<SImplementation>()) {
    // Parse the XML data and populate Nodes and Ways
    SXMLEntity Entity;
    std::string currentNodeName;
    std::vector<std::string> currentAttributes;

    // Loop to read XML entities until end of data source
    while (src->ReadEntity(Entity, false)) {
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


// Destructor
COpenStreetMap::~COpenStreetMap() = default;

// Implementation of virtual functions

std::size_t COpenStreetMap::NodeCount() const noexcept {
    return DImplementation->Nodes.size();
}

std::size_t COpenStreetMap::WayCount() const noexcept {
    return DImplementation->Ways.size();
}

std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByIndex(std::size_t index) const noexcept {
    if (index < DImplementation->Nodes.size()) {
        return DImplementation->Nodes[index];
    }
    return nullptr;
}

std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByID(TNodeID id) const noexcept {
    auto it = DImplementation->NodesById.find(id);
    if (it != DImplementation->NodesById.end()) {
        return it->second;
    }
    return nullptr;
}

std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByIndex(std::size_t index) const noexcept {
    if (index < DImplementation->Ways.size()) {
        return DImplementation->Ways[index];
    }
    return nullptr;
}

std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByID(TWayID id) const noexcept {
    auto it = DImplementation->WaysById.find(id);
    if (it != DImplementation->WaysById.end()) {
        return it->second;
    }
    return nullptr;
}
