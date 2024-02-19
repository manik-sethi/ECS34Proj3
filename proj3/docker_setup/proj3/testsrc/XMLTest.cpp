#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "XMLReader.h"
#include "XMLWriter.h"
#include "StringDataSource.h"
#include "StringDataSink.h"

/*
// Tests go here:
// Tests for CXMLReader
TEST(CXMLReaderTest, Constructor) {
    auto dataSource = std::make_shared<CStringDataSource>("test.xml");
    CXMLReader xmlReader(dataSource);

    // Add assertions if needed
    ASSERT_TRUE(xmlReader.End());
}

TEST(CXMLReaderTest, ReadEntity) {
    auto dataSource = std::make_shared<CStringDataSource>("test.xml");
    CXMLReader xmlReader(dataSource);

    SXMLEntity entity;
    bool result = xmlReader.ReadEntity(entity);

    auto InputStream = std::make_shared<CStringDataSource>("<example attr=\"Hello World\"></example>");
    CXMLReader Reader(InputStream);
    SXMLEntity E;

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.AttributeValue("attr"), "Hello World");

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
}

// Tests for CXMLWriter
TEST(CXMLWriterTest, Constructor) {
    auto dataSink = std::make_shared<CStringDataSink>();
    CXMLWriter xmlWriter(dataSink);

    // Add assertions if needed
    ASSERT_FALSE(xmlWriter.Flush());  // Assuming Flush returns false in your current implementation
}

TEST(CXMLWriterTest, WriteEntity) {
    auto dataSink = std::make_shared<CStringDataSink>();
    CXMLWriter xmlWriter(dataSink);

    SXMLEntity entity;
    // Set up the entity with necessary data

    bool result = xmlWriter.WriteEntity(entity);

    // Add assertions based on your expectations
    ASSERT_FALSE(result);
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "example", {{"attr","Hello World"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "example", {}}));

    EXPECT_EQ(OutputStream->String(), "<example attr=\"Hello World\"></example>");
}
*/
// Test Case 1: XMLReader Example
TEST(XMLReaderTest1, XMLReaderExample) {
    auto InputStream = std::make_shared<CStringDataSource>("<example attr=\"Hello World\"></example>");
    CXMLReader Reader(InputStream);
    SXMLEntity E;

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.AttributeValue("attr"), "Hello World");

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
}

// Test Case 2: XMLWriter Example
TEST(XMLWriterTest2, XMLWriterExample) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    // Write the example XML
    Writer.WriteEntity({SXMLEntity::EType::StartElement, "example", {{"attr", "Hello World"}}});
    Writer.WriteEntity({SXMLEntity::EType::EndElement, "example", {}});
    Writer.Flush();

    EXPECT_EQ(OutputStream->String(), "<example attr=\"Hello World\"></example>");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}