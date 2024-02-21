# StreetMap
The CStreetMap class is an abstract base class responsible for managing street map data. It defines interfaces for accessing nodes and ways in the street map.  

## Member Function
### NodeCount
```cpp
virtual std::size_t NodeCount() const noexcept = 0;
```
Returns the number of nodes in the street map.

### WayCount
```cpp
virtual std::size_t WayCount() const noexcept = 0;
```
Returns the number of ways in the street map.

### NodeByIndex
```cpp
virtual std::shared_ptr<CStreetMap::SNode> NodeByIndex(std::size_t index) const noexcept = 0;
```
Returns the node specified by the index. Returns nullptr if the index is out of range.

### NodeByID
```cpp
virtual std::shared_ptr<CStreetMap::SNode> NodeByID(TNodeID id) const noexcept = 0;
```
Returns the node specified by the node ID. Returns nullptr if the ID is not found.

### WayByIndex
```cpp
virtual std::shared_ptr<CStreetMap::SWay> WayByIndex(std::size_t index) const noexcept = 0;
```
Returns the way specified by the index. Returns nullptr if the index is out of range.

### WayByID
```cpp
virtual std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const noexcept = 0;
```
Returns the way specified by the way ID. Returns nullptr if the ID is not found.

## SWay
The SWay struct defines interfaces for accessing information about ways in the street map.
### ID
```cpp
virtual TWayID ID() const noexcept = 0;
```
Returns the ID of the way.

### NodeCount
```cpp
virtual std::size_t NodeCount() const noexcept = 0;
```
Returns the number of nodes in the way.

### GetNodeID
```cpp
virtual TNodeID GetNodeID(std::size_t index) const noexcept = 0;
```
Returns the ID of the node at the specified index in the way.
### AttributeCount
```cpp
virtual std::size_t AttributeCount() const noexcept = 0;
```
Returns the number of attributes associated with the way.

### GetAttributeKey
```cpp
virtual std::string GetAttributeKey(std::size_t index) const noexcept = 0;
```
Returns the key of the attribute at the specified index in the way.

### HasAttribute
```cpp 
virtual bool HasAttribute(const std::string &key) const noexcept = 0;
```
Checks if the way has the specified attribute.

### GetAttribute
```cpp
virtual std::string GetAttribute(const std::string &key) const noexcept = 0;
```
Returns the value of the attribute with the specified key in the way.

## SNode
The SNode struct defines interfaces for accessing information about nodes in the street map.

### ID
```cpp
virtual TNodeID ID() const noexcept = 0;
```
Returns the ID of the node.

### Location
```cpp
virtual TLocation Location() const noexcept = 0;
```
Returns the location (latitude and longitude) of the node.

### AttributeCount
```cpp 
virtual std::size_t AttributeCount() const noexcept = 0;
```
Returns the number of attributes associated with the node.

### GetAttributeKey
```cpp
virtual std::string GetAttributeKey(std::size_t index) const noexcept = 0;
```
Returns the key of the attribute at the specified index in the node.

### HasAttribute
```cpp
virtual bool HasAttribute(const std::string &key) const noexcept = 0;
```
Checks if the node has the specified attribute.

### GetAttribute
```cpp
virtual std::string GetAttribute(const std::string &key) const noexcept = 0;
```
Returns the value of the attribute with the specified key in the node.