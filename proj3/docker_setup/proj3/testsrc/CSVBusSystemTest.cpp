#include <CSVBusSystem.h>
#include <gtest/gtest.h>
#include <StringDataSink.h>
#include <StringDataSource.h>

// Tests for CSVBusSystem

// Test case for checking the count of stops and routes when there is only one stop
TEST(CSVBusSystem, SingleStopCountTest) {
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id\n1,1001");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes,',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    EXPECT_EQ(BusSystem.StopCount(), 1);
    EXPECT_EQ(BusSystem.RouteCount(), 0);
}

// Test case for checking properties of the first stop
TEST(CSVBusSystem, SingleStopPropertiesTest) {
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id\n1,1001");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes,',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    auto stop = BusSystem.StopByIndex(0);
    ASSERT_NE(stop, nullptr); // Ensure stop is not null

    EXPECT_EQ(stop->ID(), 1);
    EXPECT_EQ(stop->NodeID(), 1001);
}

// Test case for checking properties of multiple stops
TEST(CSVBusSystem, MultipleStopsPropertiesTest) {
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id\n1,1001\n2,1002\n3,1003");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes,',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    EXPECT_EQ(BusSystem.StopCount(), 3); // We expect 3 stops in this case
    EXPECT_EQ(BusSystem.RouteCount(), 0); // No routes yet

    auto stop1 = BusSystem.StopByIndex(0);
    auto stop2 = BusSystem.StopByIndex(1);
    auto stop3 = BusSystem.StopByIndex(2);

    // Check properties of each stop
    ASSERT_NE(stop1, nullptr);
    EXPECT_EQ(stop1->ID(), 1);
    EXPECT_EQ(stop1->NodeID(), 1001);

    ASSERT_NE(stop2, nullptr);
    EXPECT_EQ(stop2->ID(), 2);
    EXPECT_EQ(stop2->NodeID(), 1002);

    ASSERT_NE(stop3, nullptr);
    EXPECT_EQ(stop3->ID(), 3);
    EXPECT_EQ(stop3->NodeID(), 1003);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
