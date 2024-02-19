# CDSVReader
The CDSVReader class enables reading data in delimited-separated values (DSV) format from a specified data source.
## Constructor
```cpp
CDSVReader(std::shared_ptr<CDataSource> src, char delimiter);
```
### Parameters
src: A shared pointer to a data source object (CDataSource) from which data will be read.
delimiter: The character used as a delimiter in the DSV format.
## Destructor
```cpp
~CDSVReader();
```
## Member Function
### End
```cpp
bool End() const;
```
Checks if the end of DSV file has been reached. If it has, then returns true, false otherwise.
### ReadRow
```cpp
bool ReadRow(std::vector<std::string> &row);
```
Reads a row of data from given file
#### Parameters:
row: Reference to a vector where the read row will be stored.
Returns:
true if a row is successfully read, false if the end of the file is reached.
# CDSVWriter
The CDSVWriter class helps writing DSV data into a data sink
## Constructor 
```cpp
CDSVWriter(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall = false);
```
### Parameters:
Sink: Shared pointer to data sink object (CDataSink). Data will be written there.
Delimiter: The character used as a delimited.
Quoteall: Optional. If true, all values will be enclosed in quotes.
## Destructor
```cpp
~CDSVWriter();
```
## Member Functions
### WriteRow
```cpp
bool WriteRow(const std::vector<std::string> &row);
```
Writes a row of data to the DSV file
#### Parameters:
Row: A vector of strings representing a single row in the file
Return Value:
If row is succesfully written, then true, else false

# CXMLReader
The CXMLReader class is designed for reading XML entities from a specified data source.

## Constructor
```cpp
CXMLReader(std::shared_ptr<CDataSource> src);
```
### Parameters:
src: A pointer to where XML entities will be read form
## Destructor
```cpp
~CXMLReader();
```
## Member Functions
### End
```cpp
bool End() const;
```
Will check if the end of the XML file has been reached. If it has, will return true, else false.
### ReadEntity
```cpp
bool ReadEntity(SXMLEntity &entity, bool skipcdata = false);
```
Reads an XML entity from the XML file.
#### Parameters:
entity: where read entity will be stored
skipcdata: Optional. If true: skips reading CDATA sections.
Returns: true if  successfully read, false if the end of the file is reached.

# CXMLWriter
The CXMLWriter class provides functionality to write XML entities to a specified data sink.

## Constructor
```cpp
CXMLWriter(std::shared_ptr<CDataSink> sink);
```
### Parameters:
sink: A pointer to DataSink where data will be written
## Destructor
```cpp
~CXMLWriter();
```
## Member Functions
### Flush
```cpp
bool Flush();
```
Flushes output buffer data sink.
Returns true if is successful, false otherwise.
### WriteEntity
```cpp
bool WriteEntity(const SXMLEntity &entity);
```
Writes an XML entity to the XML file.
## Parameters:
entity: object referencing what will be written
Returns: true if successfully written, else false
