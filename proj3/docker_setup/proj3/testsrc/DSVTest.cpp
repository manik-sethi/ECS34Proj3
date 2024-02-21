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


TEST(DSVReaderWriterTest, DelimiterHandling) {
    // Writer test
    auto sink = std::make_shared<CStringDataSink>();
    CDSVWriter writerComma(sink, ',');
    CDSVWriter writerTab(sink, '\t');
    std::vector<std::string> input = {"Delim", "Handling"};

    EXPECT_TRUE(writerComma.WriteRow(input));
    EXPECT_TRUE(writerTab.WriteRow(input));

    // Reader test
    auto sourceComma = std::make_shared<CStringDataSource>("Delim,Handling");
    auto sourceTab = std::make_shared<CStringDataSource>("Delim\tHandling");
    CDSVReader readerComma(sourceComma, ',');
    CDSVReader readerTab(sourceTab, '\t');
    std::vector<std::string> outputComma, outputTab;

    EXPECT_TRUE(readerComma.ReadRow(outputComma));
    EXPECT_TRUE(readerTab.ReadRow(outputTab));
    EXPECT_EQ(outputComma.size(), 2);
    EXPECT_EQ(outputTab.size(), 2);
    EXPECT_EQ(outputComma[0], "Delim");
    EXPECT_EQ(outputComma[1], "Handling");
    EXPECT_EQ(outputTab[0], "Delim");
    EXPECT_EQ(outputTab[1], "Handling");
}

TEST(DSVReaderWriterTest, EmptyRowHandling) {
    // Writer test
    auto sink = std::make_shared<CStringDataSink>();
    CDSVWriter writer(sink, ',');
    std::vector<std::string> input;

    EXPECT_TRUE(writer.WriteRow(input));

    // Reader test
    auto source = std::make_shared<CStringDataSource>("");
    CDSVReader reader(source, ',');
    std::vector<std::string> output;

    EXPECT_FALSE(reader.ReadRow(output));
    EXPECT_TRUE(output.empty());
}

TEST(DSVReaderWriterTest, QuotingTest) {
    // Writer test
    auto sink = std::make_shared<CStringDataSink>();
    CDSVWriter writer(sink, ',', true); // Quote all fields
    std::vector<std::string> input = {"Hello, World!", "Multi\nline"};

    EXPECT_TRUE(writer.WriteRow(input));

    // Reader test
    auto source = std::make_shared<CStringDataSource>("\"Hello, World!\",\"Multi\nline\"");
    CDSVReader reader(source, ',');
    std::vector<std::string> output;

    EXPECT_TRUE(reader.ReadRow(output));
    EXPECT_EQ(output.size(), 2);
    EXPECT_EQ(output[0], "Hello, World!");
    EXPECT_EQ(output[1], "Multi\nline");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}