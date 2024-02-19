#include "DSVReader.h"
#include "DSVWriter.h"
#include "StringDataSink.h"
#include "StringDataSource.h"
#include <gtest/gtest.h>

// Tests for CDSVReader and CDSVWriter

TEST(DSVReaderWriterTest, WriteAndReadRow) {
    // Writer test
    auto sink = std::make_shared<CStringDataSink>();
    CDSVWriter writer(sink, '&');
    std::vector<std::string> input = {"Hello", "World!"};

    EXPECT_TRUE(writer.WriteRow(input));

    // Reader test
    auto source = std::make_shared<CStringDataSource>("Hello&World!");
    CDSVReader reader(source, '&');
    std::vector<std::string> output;

    EXPECT_TRUE(reader.ReadRow(output));
    EXPECT_EQ(output.size(), 2);
    EXPECT_EQ(output[0], "Hello");
    EXPECT_EQ(output[1], "World!");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}