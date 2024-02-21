# CBusSystem
The CBusSystem class manages bus stop and route information using data in DSV format. It relies on the CDSVReader class to read data.
## Constructor
```cpp
CCSVBusSystem(std::shared_ptr<CDSVReader> stopsrc, std::shared_ptr<CDSVReader> routesrc);
```
### Parameters
stopsrc: A shared pointer to a CDSVReader object responsible for reading stop data.
routesrc: A shared pointer to a CDSVReader object responsible for reading route data.
## Destructor
```cpp
~CCSVBusSystem();
```
## Member Function
### StopCount
```cpp
std::size_t StopCount() const noexcept override;
```
Returns the number of stops in the system.

### RouteCount
```cpp
std::size_t RouteCount() const noexcept override;
```
Returns the number of routes in the system.

### StopByIndexc
```cpp
std::shared_ptr<SStop> StopByIndex(std::size_t index) const noexcept override;
```
Returns the stop specified by the index. Returns nullptr if the index is out of range.

### StopByID
```cpp
std::shared_ptr<SStop> StopByID(TStopID id) const noexcept override;
```
Returns the stop specified by the stop ID. Returns nullptr if the ID is not found.

### RouteByIndex
```cpp
std::shared_ptr<SRoute> RouteByIndex(std::size_t index) const noexcept override;
```
Returns the route specified by the index. Returns nullptr if the index is out of range.

### RouteByName
```cpp
std::shared_ptr<SRoute> RouteByName(const std::string &name) const noexcept override;
```
Returns the route specified by the name. Returns nullptr if the name is not found.

## Bus System Stop Member Functions
### ID
```cpp
TStopID ID() const noexcept override;
```
Returns the ID of the stop.

### NodeID
```cpp
CStreetMap::TNodeID NodeID() const noexcept override;
```
Returns the node ID of the bus stop.

## Bus System Route Member Functions
### Name
```cpp
std::string Name() const noexcept override;
```
Returns the name of the route.

### StopCount
```cpp
std::size_t StopCount() const noexcept override;
```
Returns the number of stops on the route.

### GetStopID
```cpp
TStopID GetStopID(std::size_t index) const noexcept override;
```
Returns the stop ID specified by the index. Returns InvalidStopID if the index is out of range.

