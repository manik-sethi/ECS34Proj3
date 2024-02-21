#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "XMLReader.h"
#include "XMLWriter.h"
#include "StringDataSource.h"
#include "StringDataSink.h"

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


// Test Case 3: XML with CDATA
TEST(XMLReaderTest3, XMLWithCDATA) {
    auto InputStream = std::make_shared<CStringDataSource>("<example><![CDATA[<p>Hello World</p>]]></example>");
    CXMLReader Reader(InputStream);
    SXMLEntity E;

    // Expect a start element
    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);

    // Expect character data
    EXPECT_TRUE(Reader.ReadEntity(E, true));
    EXPECT_EQ(E.DType, SXMLEntity::EType::CharData);
    EXPECT_EQ(E.DNameData, "<p>Hello World</p>");

    // Expect an end element
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


TEST(XMLWriterTest3, XMLWriterExample) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    // Write the example XML
    Writer.WriteEntity({SXMLEntity::EType::StartElement, "three", {{"two", "Hello "}}});
    Writer.WriteEntity({SXMLEntity::EType::EndElement, "three", {}});
    Writer.Flush();

    EXPECT_EQ(OutputStream->String(), "<three two=\"Hello \"></three>");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}