#include "../include/StringDataSource.h"
#include "../include/OpenStreetMap.h"
#include <gtest/gtest.h>
#include "../include/StringDataSink.h"

// Tests for COpenStreetMap

// Test case for checking the count of nodes and ways when there is only one node and one way
TEST(COpenStreetMap, SingleNodeWayCountTest) {
    // Prepare sample data for a single node and single way
    auto xmlData = R"(
        <osm>
            <node id="1" lat="52.0" lon="13.0"/>
            <way id="101">
                <nd ref="1"/>
            </way>
        </osm>
    )";
    auto dataSource = std::make_shared<CStringDataSource>(xmlData);
    auto xmlReader = std::make_shared<CXMLReader>(dataSource);
    COpenStreetMap osm(xmlReader);

    // Test assertions
    EXPECT_EQ(osm.NodeCount(), 1);
    EXPECT_EQ(osm.WayCount(), 1);
}

// Test case for checking properties of the first node and way
TEST(COpenStreetMap, SingleNodeWayPropertiesTest) {
    // Prepare sample data for a single node and single way
    auto xmlData = R"(
        <osm>
            <node id="1" lat="52.0" lon="13.0"/>
            <way id="101">
                <nd ref="1"/>
            </way>
        </osm>
    )";
    auto dataSource = std::make_shared<CStringDataSource>(xmlData);
    auto xmlReader = std::make_shared<CXMLReader>(dataSource);
    COpenStreetMap osm(xmlReader);

    // Test assertions for the first node
    auto node = osm.NodeByIndex(0);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->ID(), 1);
    EXPECT_EQ(node->Location().latitude, 52.0);
    EXPECT_EQ(node->Location().longitude, 13.0);

    // Test assertions for the first way
    auto way = osm.WayByIndex(0);
    ASSERT_NE(way, nullptr);
    EXPECT_EQ(way->ID(), 101);
    EXPECT_EQ(way->NodeCount(), 1);
    EXPECT_EQ(way->GetNodeID(0), 1);
}

// Test case for checking properties of multiple nodes and ways
TEST(COpenStreetMap, MultipleNodesWaysPropertiesTest) {
    // Prepare sample data for multiple nodes and ways
    auto xmlData = R"(
        <osm>
            <node id="1" lat="52.0" lon="13.0"/>
            <node id="2" lat="53.0" lon="14.0"/>
            <way id="101">
                <nd ref="1"/>
                <nd ref="2"/>
            </way>
        </osm>
    )";
    auto dataSource = std::make_shared<CStringDataSource>(xmlData);
    auto xmlReader = std::make_shared<CXMLReader>(dataSource);
    COpenStreetMap osm(xmlReader);

    // Test assertions for node count and way count
    EXPECT_EQ(osm.NodeCount(), 2);
    EXPECT_EQ(osm.WayCount(), 1);

    // Test assertions for properties of each node
    auto node1 = osm.NodeByIndex(0);
    ASSERT_NE(node1, nullptr);
    EXPECT_EQ(node1->ID(), 1);
    EXPECT_EQ(node1->Location().latitude, 52.0);
    EXPECT_EQ(node1->Location().longitude, 13.0);

    auto node2 = osm.NodeByIndex(1);
    ASSERT_NE(node2, nullptr);
    EXPECT_EQ(node2->ID(), 2);
    EXPECT_EQ(node2->Location().latitude, 53.0);
    EXPECT_EQ(node2->Location().longitude, 14.0);

    // Test assertions for properties of each way
    auto way = osm.WayByIndex(0);
    ASSERT_NE(way, nullptr);
    EXPECT_EQ(way->ID(), 101);
    EXPECT_EQ(way->NodeCount(), 2);
    EXPECT_EQ(way->GetNodeID(0), 1);
    EXPECT_EQ(way->GetNodeID(1), 2);
}

// Add more test cases as needed

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
