#include "DSVWriter.h"
#include "StringUtils.h"
#include "StringDataSink.h"

// Implementation struct definition
struct CDSVWriter::SImplementation {
    std::shared_ptr<CDataSink> DDataSink;
    char DDelimiter;
    bool DQuoteAll;

    SImplementation(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall)
        : DDataSink(sink), DDelimiter(delimiter), DQuoteAll(quoteall) {

    }
};

// Constructor
CDSVWriter::CDSVWriter(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall)
    : DImplementation(std::make_unique<SImplementation>(sink, delimiter, quoteall)) {

}

// Destructor
CDSVWriter::~CDSVWriter() {

}

// WriteRow function
bool CDSVWriter::WriteRow(const std::vector<std::string> &row) {
    // Check if data sink is initialized
    if (!DImplementation->DDataSink) {
        return false; // Data sink is not initialized
    }

    // Temporary storage for building the row string
    std::string rowString;

    // Flag to determine if quoting is needed
    bool quoteNeeded = DImplementation->DQuoteAll;

    // Iterate through the row vector
    for (size_t i = 0; i < row.size(); ++i) {
        // If not the first field, add delimiter
        if (i > 0) {
            rowString += DImplementation->DDelimiter;
        }

        // Get the current field
        std::string field = row[i];

        // Check if quoting is needed for the current field
        if (!DImplementation->DQuoteAll) {
            // Quoting is needed if the field contains the delimiter or newline character
            if (field.find(DImplementation->DDelimiter) != std::string::npos ||
                field.find('\n') != std::string::npos) {
                quoteNeeded = true;
            }
        }

        // If quoting is needed, enclose the field in quotes
        if (quoteNeeded) {
            rowString += "\"" + field + "\"";
        } else {
            rowString += field;
        }
    }

    // Write the row string to the data sink
    std::vector<char> buffer(rowString.begin(), rowString.end());
    if (!DImplementation->DDataSink->Write(buffer)) {
        return false; // Failed to write to data sink
    }

    // Write newline character to indicate end of row
    char newline = '\n';
    if (!DImplementation->DDataSink->Write(std::vector<char>{newline})) {
        return false; // Failed to write newline character
    }

    // Return true to indicate success
    return true;
}
