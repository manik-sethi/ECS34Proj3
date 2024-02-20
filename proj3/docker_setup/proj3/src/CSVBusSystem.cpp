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

// CSVBusSystem File

class CCSVBusSystem

{
    // CCSVBusSystem member functions
    // Constructor for the CSV Bus System
    CCSVBusSystem(std::shared_ptr< CDSVReader > stopsrc, std::shared_ptr<
    CDSVReader > routesrc);
    // Destructor for the CSV Bus System
    ~CCSVBusSystem();
    // Returns the number of stops in the system
    std::size_t StopCount() const noexcept override;
    // Returns the number of routes in the system
    std::size_t RouteCount() const noexcept override;
    // Returns the SStop specified by the index, nullptr is returned if index is
    // greater than equal to StopCount()
    std::shared_ptr<SStop> StopByIndex(std::size_t index) const noexcept
    override;
    // Returns the SStop specified by the stop id, nullptr is returned if id is
    // not in the stops
    std::shared_ptr<SStop> StopByID(TStopID id) const noexcept override;
    // Returns the SRoute specified by the index, nullptr is returned if index is
    // greater than equal to RouteCount()
    std::shared_ptr<SRoute> RouteByIndex(std::size_t index) const noexcept
    override;
    // Returns the SRoute specified by the name, nullptr is returned if name is
    // not in the routes
    std::shared_ptr<SRoute> RouteByName(const std::string &name) const noexcept
    override;
    // Bus System Stop member functions
    // Returns the stop id of the stop
    TStopID ID() const noexcept override;
    // Returns the node id of the bus stop
    CStreetMap::TNodeID NodeID() const noexcept override;
    // Bus System Route member functions
    // Returns the name of the route
    std::string Name() const noexcept override;
    // Returns the number of stops on the route
    std::size_t StopCount() const noexcept override;
    // Returns the stop id specified by the index, returns InvalidStopID if index
    // is greater than or equal to StopCount()
    TStopID GetStopID(std::size_t index) const noexcept override;
};
