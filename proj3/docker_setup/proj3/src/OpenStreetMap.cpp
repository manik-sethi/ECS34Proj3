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

#include "OpenStreetMap.h"
#include <unordered_map>

struct COpenStreetMap::SImplementation {
    std::vector<std::shared_ptr<CStreetMap::SNode>> Nodes;
    std::unordered_map<CStreetMap::TNodeID, std::shared_ptr<CStreetMap::SNode>> NodesById;
    std::vector<std::shared_ptr<CStreetMap::SWay>> Ways;
    std::unordered_map<CStreetMap::TWayID, std::shared_ptr<CStreetMap::SWay>> WaysById;

    struct SNode : public CStreetMap::SNode {
        CStreetMap::TNodeID id; 
        CStreetMap::TNodeID nodeID; 

        // Constructor
        SNode(CStreetMap::TNodeID id, CStreetMap::TNodeID nodeID) : id(id), nodeID(nodeID) {}

        // Methods to retrieve stop information
        CStreetMap::TNodeID ID() const noexcept override { return id; }

        // Implement other methods as needed
        CStreetMap::TLocation Location() const noexcept override { 
            // Implement according to your data structure
        }

        std::size_t AttributeCount() const noexcept override {
            // Implement according to your data structure
        }

        std::string GetAttributeKey(std::size_t index) const noexcept override {
            // Implement according to your data structure
        }

        bool HasAttribute(const std::string &key) const noexcept override {
            // Implement according to your data structure
        }

        std::string GetAttribute(const std::string &key) const noexcept override {
            // Implement according to your data structure
        }
    };


    // Struct representing a route
    // Struct representing a way
    struct SWay : public CStreetMap::SWay {
        CStreetMap::TWayID id; 
        // Add any additional members as needed

        // Constructor
        SWay(CStreetMap::TWayID id) : id(id) {}

        // Methods to retrieve way information
        CStreetMap::TWayID ID() const noexcept override { return id; }
        std::size_t NodeCount() const noexcept override {
            // Implement according to your data structure
        }

        CStreetMap::TNodeID GetNodeID(std::size_t index) const noexcept override {
            // Implement according to your data structure
        }

        std::size_t AttributeCount() const noexcept override {
            // Implement according to your data structure
        }

        std::string GetAttributeKey(std::size_t index) const noexcept override {
            // Implement according to your data structure
        }

        bool HasAttribute(const std::string &key) const noexcept override {
            // Implement according to your data structure
        }

        std::string GetAttribute(const std::string &key) const noexcept override {
            // Implement according to your data structure
        }
    };

};


// Constructor
COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src) : DImplementation(std::make_unique<SImplementation>(std::move(src))) {}

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
