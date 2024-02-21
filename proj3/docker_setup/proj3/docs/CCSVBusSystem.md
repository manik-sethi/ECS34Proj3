# CCSVBusSystem
The CSVBusRoute class extends the functionality of the BusSystem class to manage bus routes specifically from data provided in delimited-separated values (DSV) format. It utilizes the DSVReader class for reading data from the specified sources.
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

