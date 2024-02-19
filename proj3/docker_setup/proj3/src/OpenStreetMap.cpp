#include <OpenStreetMap.h>
#include <BusSystem.h>
#include <CSVBusSystem.h>
#include <DataSink.h>
#include <DataSource.h>
#include <DSVReader.h>
#include <DSVWriter.h>
#include <StreetMap.h>
#include <StringDataSink.h>
#include <StringDataSource.h>
#include <StringUtils.h>
#include <XMLEntity.h>
#include <XMLReader.h>
#include <XMLWriter.h>
#include <stdlib.h>

// OSM File
class COpenStreetMap

{
    public:
    // COpenStreetMap member functions
    // Constructor for the Open Street Map
    COpenStreetMap(std::shared_ptr<CXMLReader> src);
    // Destructor for the Open Street Map
    ~COpenStreetMap();
    // Returns the number of nodes in the map
    std::size_t NodeCount() const noexcept override;
    // Returns the number of ways in the map
    std::size_t WayCount() const noexcept override;
    // Returns the SNode associated with index, returns nullptr if index is
    // larger than or equal to NodeCount()
    std::shared_ptr<SNode> NodeByIndex(std::size_t index) const noexcept override;
    // Returns the SNode with the id of id, returns nullptr if doesn't exist
    std::shared_ptr<SNode> NodeByID(TNodeID id) const noexcept override;
    // Returns the SWay associated with index, returns nullptr if index is
    // larger than or equal to WayCount()
    std::shared_ptr<SWay> WayByIndex(std::size_t index) const noexcept override;
    // Returns the SWay with the id of id, returns nullptr if doesn't exist
    std::shared_ptr<SWay> WayByID(TWayID id) const noexcept override;
    // Street Map Node member functions
    // Returns the id of the SNode
    TNodeID ID() const noexcept override;
    // Returns the lat/lon location of the SNode
    TLocation Location() const noexcept override;
    // Returns the number of attributes attached to the SNode
    std::size_t AttributeCount() const noexcept override;
    // Returns the key of the attribute at index, returns empty string if index
    // is greater than or equal to AttributeCount()
    std::string GetAttributeKey(std::size_t index) const noexcept override;
    // Returns if the attribute is attached to the SNode
    bool HasAttribute(const std::string &key) const noexcept override;
    // Returns the value of the attribute specified by key, returns empty string
    // if key hasn't been attached to SNode
    std::string GetAttribute(const std::string &key) const noexcept override;
    // Street Map Way
    // Returns the id of the SWay
    TWayID ID() const noexcept override;
    // Returns the number of nodes in the way
    std::size_t NodeCount() const noexcept override;
    // Returns the node id of the node at index, returns InvalidNodeID if index
    // is greater than or equal to NodeCount()
    TNodeID GetNodeID(std::size_t index) const noexcept override;
    // Returns the number of attributes attached to the SWay
    std::size_t AttributeCount() const noexcept override;
    // Returns the key of the attribute at index, returns empty string if index
    // is greater than or equal to AttributeCount()
    std::string GetAttributeKey(std::size_t index) const noexcept override;
    // Returns if the attribute is attached to the SWay
    bool HasAttribute(const std::string &key) const noexcept override;
    // Returns the value of the attribute specified by key, returns empty string
    // if key hasn't been attached to SWay
    std::string GetAttribute(const std::string &key) const noexcept override;
};