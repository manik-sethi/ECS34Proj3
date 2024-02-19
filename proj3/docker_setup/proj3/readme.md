# Project 2 README

Student: Manik Sethi (920896983)
Student: Saketh Kotapati (919454378)

## Project Status
The project has been completed, and the repo has our code

## Known Issues
Due to some issues with docker crashing on Manik's mac repeatedly, we have to include a gtest file. We obtained the file from the official googletest github. Also, we weren't able to fully flesh out the DSV Reader section.

## Code References
* [How to use XML](https://www.w3schools.com/xml/xml_usedfor.asp)
* [Gtest reference](https://google.github.io/googletest/primer.html#simple-tests)

## Generative AI Use
I used ChatGPT for Prompt 1 and Prompt 2

### Prompt 1
I am writing an XML parser that has two file components, an XML reader and XML writer in C++. I am using the google test library to write testcases. Please wait a moment until I provide my current test file.
```cpp
#include "XMLReader.h"
#include "XMLWriter.h"
#include "XMLEntity.h"
#include "DataSink.h"
#include "DataSource.h"
#include <gtest/gtest.h>


// Tests go here:
// Tests for CXMLReader
TEST(CXMLReaderTest, Constructor) {
    auto dataSource = std::make_shared<CDataSink>();
    CXMLReader xmlReader(dataSource);

    // Add assertions if needed
    ASSERT_TRUE(xmlReader.End());
}

TEST(CXMLReaderTest, ReadEntity) {
    auto dataSource = std::make_shared<CDataSource>();
    CXMLReader xmlReader(dataSource);

    SXMLEntity entity;
    bool result = xmlReader.ReadEntity(entity);

    // Add assertions based on your expectations
    ASSERT_TRUE(result);
    // ASSERT_EQ(entity.DType, ...);
    // ASSERT_EQ(entity.DNameData, ...);
    // ASSERT_EQ(entity.DAttributes.size(), ...);
}

// Tests for CXMLWriter
TEST(CXMLWriterTest, Constructor) {
    auto dataSink = std::make_shared<CDataSink>();
    CXMLWriter xmlWriter(dataSink);

    // Add assertions if needed
    ASSERT_FALSE(xmlWriter.Flush());  // Assuming Flush returns false in your current implementation
}

TEST(CXMLWriterTest, WriteEntity) {
    auto dataSink = std::make_shared<CDataSink>();
    CXMLWriter xmlWriter(dataSink);

    SXMLEntity entity;
    // Set up the entity with necessary data

    bool result = xmlWriter.WriteEntity(entity);

    // Add assertions based on your expectations
    ASSERT_FALSE(result);  // Assuming WriteEntity returns false in your current implementation
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```
### Response 1
Thank you for providing your updated test file. It looks like you have set up test cases for both the XML reader and XML writer components. Here are a few suggestions and improvements you might consider:

Mock Objects: Since your tests involve interactions with CDataSource and CDataSink, which are presumably external dependencies, consider using mock objects to isolate the unit under test. This allows you to control the behavior of the dependencies and focus solely on testing the functionality of the XML reader and writer.

Assertions: While your current test cases have assertions to verify basic functionality, consider adding more detailed assertions to thoroughly test the behavior of your XML reader and writer. For example, you could verify the content of the entities read/written, the handling of edge cases, etc.

Edge Cases: Make sure to test edge cases such as empty XML files, XML files with malformed syntax, large XML files, etc. This ensures that your XML parser behaves correctly under various conditions.

Parameterized Tests: If applicable, consider using parameterized tests to test your XML reader and writer with different inputs or configurations. This can help increase test coverage and identify potential issues with different scenarios.

Error Handling: Test how your XML reader and writer handle errors, such as invalid XML input or I/O errors when reading/writing to the data source/sink.

Memory Management: Ensure proper memory management in your tests, especially when dealing with shared pointers. Make sure objects are destructed appropriately and there are no memory leaks.

Test Naming: Consider using more descriptive names for your test cases to clearly indicate what behavior or functionality they are testing.

Documentation: Add comments or documentation to your test cases to explain the purpose of each test and any assumptions being made.

Applying these suggestions can help you improve the robustness and effectiveness of your test suite for the XML parser. If you need further assistance with any specific aspect of your tests or implementation, feel free to ask!

### Changes 1
We utilized this prompt to help with troubleshooting and suggesting improvements for the xmltest file. Overall, we ended up keeping these suggestions in mind to come up with this testfile:
```cpp
...
//Previous Tests
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
//Proceeding Tests
...
```

