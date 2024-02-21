# OpenStreetMap
The OpenStreetMap class inherits from the CStreetMap class and is responsible for managing street map data obtained from OpenStreetMap sources. It relies on the XMLReader class for reading XML data and the StreetMap class for storing street map information.
## Constructor
```cpp
COpenStreetMap(std::shared_ptr<CXMLReader> src);
```
### Parameters
Initializes an OpenStreetMap object with a shared pointer to a CXMLReader instance for reading OpenStreetMap data.
## Destructor
```cpp
~COpenStreetMap();
```
## Member Function
### NodeCount
```cpp
std::size_t NodeCount() const noexcept override;
```
Returns the number of nodes in the street map.

### WayCount
```cpp
std::size_t WayCount() const noexcept override;
```
Returns the number of ways in the street map.

### NodeByIndex
```cpp
std::shared_ptr<CStreetMap::SNode> NodeByIndex(std::size_t index) const noexcept override;
```
Returns the node specified by the index. Returns nullptr if the index is out of range.

### NodeByID
```cpp
std::shared_ptr<CStreetMap::SNode> NodeByID(TNodeID id) const noexcept override;
```
Returns the node specified by the node ID. Returns nullptr if the ID is not found.

### WayByIndex
```cpp
std::shared_ptr<CStreetMap::SWay> WayByIndex(std::size_t index) const noexcept override;
```
Returns the way specified by the index. Returns nullptr if the index is out of range.

### WayByID
```cpp
std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const noexcept override;
```
Returns the way specified by the way ID. Returns nullptr if the ID is not found.

