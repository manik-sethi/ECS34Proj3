#include "DSVReader.h"
#include "StringUtils.h"
#include "StringDataSource.h"

#include <sstream>

// Implementation struct definition
struct CDSVReader::SImplementation {
    std::shared_ptr<CDataSource> DDataSource;
    char DDelimiter;

    SImplementation(std::shared_ptr<CDataSource> src, char delimiter)
        : DDataSource(src), DDelimiter(delimiter) {
    }
};

// Constructor
CDSVReader::CDSVReader(std::shared_ptr<CDataSource> src, char delimiter) 
    : DImplementation(std::make_unique<SImplementation>(src, delimiter)) {
}

// Destructor
CDSVReader::~CDSVReader() {
}

// End function
bool CDSVReader::End() const {
    return DImplementation->DDataSource->End();
}

// ReadRow function
bool CDSVReader::ReadRow(std::vector<std::string> &row) {
    // Clear the row vector
    row.clear();

    // Temporary storage for read characters
    char ch;

    // Temporary storage for building a field
    std::string field;

    // Read characters until the end of line or end of data source
    while (!DImplementation->DDataSource->End() && DImplementation->DDataSource->Get(ch)) {
        // Check for end of line
        if (ch == '\n') {
            // Add the field to the row vector
            row.push_back(field);
            return true; // Row read successfully
        }
        // Check for delimiter
        else if (ch == DImplementation->DDelimiter) {
            // Add the field to the row vector
            row.push_back(field);
            // Clear the field for the next one
            field.clear();
        }
        // Normal character, add to the field
        else {
            field += ch;
        }
    }

    // Add the last field to the row vector if it's not empty
    if (!field.empty()) {
        row.push_back(field);
    }

    // Return true if at least one field was read, false otherwise
    return !row.empty();
}
