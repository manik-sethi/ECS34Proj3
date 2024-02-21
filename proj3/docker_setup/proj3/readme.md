# Project 3 README

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
Hey, I am implementing a DSV parser for bus stops, however I keep getting this error with my makefile. Can you make sense of this message
```
g++ -o ./bin/testcsvbussystem -std=c++17 -I./include  ./obj/CSVBusSystem.o ./obj/CSVBusSystemTest.o
Undefined symbols for architecture arm64:
  "CDSVReader::ReadRow(std::__1::vector<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, std::__1::allocator<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > > >&)", referenced from:
      CCSVBusSystem::CCSVBusSystem(std::__1::shared_ptr<CDSVReader>, std::__1::shared_ptr<CDSVReader>) in CSVBusSystem.o
  "CDSVReader::CDSVReader(std::__1::shared_ptr<CDataSource>, char)", referenced from:
      std::__1::__shared_ptr_emplace<CDSVReader, std::__1::allocator<CDSVReader> >::__shared_ptr_emplace<std::__1::shared_ptr<CStringDataSource>&, char>(std::__1::allocator<CDSVReader>, std::__1::shared_ptr<CStringDataSource>&, char&&) in CSVBusSystemTest.o
  "CDSVReader::~CDSVReader()", referenced from:
      std::__1::__shared_ptr_emplace<CDSVReader, std::__1::allocator<CDSVReader> >::__on_zero_shared() in CSVBusSystemTest.o
  "StringUtils::Lower(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const&)", referenced from:
      CCSVBusSystem::RouteByName(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const&) const in CSVBusSystem.o
  "CCSVBusSystem::~CCSVBusSystem()", referenced from:
      CSVBusSystem_SimpleExampleTest_Test::TestBody() in CSVBusSystemTest.o
  "CStringDataSource::CStringDataSource(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const&)", referenced from:
      std::__1::__shared_ptr_emplace<CStringDataSource, std::__1::allocator<CStringDataSource> >::__shared_ptr_emplace<char const (&) [23]>(std::__1::allocator<CStringDataSource>, char const (&) [23]) in CSVBusSystemTest.o
      std::__1::__shared_ptr_emplace<CStringDataSource, std::__1::allocator<CStringDataSource> >::__shared_ptr_emplace<char const (&) [14]>(std::__1::allocator<CStringDataSource>, char const (&) [14]) in CSVBusSystemTest.o
  "testing::InitGoogleTest(int*, char**)", referenced from:
      _main in CSVBusSystemTest.o
  "testing::AssertionSuccess()", referenced from:
      testing::AssertionResult testing::internal::CmpHelperEQ<unsigned long, int>(char const*, char const*, unsigned long const&, int const&) in CSVBusSystemTest.o
      testing::AssertionResult testing::internal::CmpHelperEQ<unsigned long long, int>(char const*, char const*, unsigned long long const&, int const&) in CSVBusSystemTest.o
  "testing::Test::SetUp()", referenced from:
      vtable for CSVBusSystem_SimpleExampleTest_Test in CSVBusSystemTest.o
  "testing::Test::TearDown()", referenced from:
      vtable for CSVBusSystem_SimpleExampleTest_Test in CSVBusSystemTest.o
  "testing::Test::Test()", referenced from:
      CSVBusSystem_SimpleExampleTest_Test::CSVBusSystem_SimpleExampleTest_Test() in CSVBusSystemTest.o
  "testing::Test::~Test()", referenced from:
      CSVBusSystem_SimpleExampleTest_Test::~CSVBusSystem_SimpleExampleTest_Test() in CSVBusSystemTest.o
  "testing::Message::Message()", referenced from:
      CSVBusSystem_SimpleExampleTest_Test::TestBody() in CSVBusSystemTest.o
  "testing::UnitTest::GetInstance()", referenced from:
      RUN_ALL_TESTS() in CSVBusSystemTest.o
  "testing::UnitTest::Run()", referenced from:
      RUN_ALL_TESTS() in CSVBusSystemTest.o
  "testing::internal::AssertHelper::AssertHelper(testing::TestPartResult::Type, char const*, int, char const*)", referenced from:
      CSVBusSystem_SimpleExampleTest_Test::TestBody() in CSVBusSystemTest.o
  "testing::internal::AssertHelper::~AssertHelper()", referenced from:
      CSVBusSystem_SimpleExampleTest_Test::TestBody() in CSVBusSystemTest.o
  "testing::internal::GetTestTypeId()", referenced from:
      ___cxx_global_var_init in CSVBusSystemTest.o
  "testing::internal::MakeAndRegisterTestInfo(char const*, char const*, char const*, char const*, testing::internal::CodeLocation, void const*, void (*)(), void (*)(), testing::internal::TestFactoryBase*)", referenced from:
      ___cxx_global_var_init in CSVBusSystemTest.o
  "testing::internal::IsTrue(bool)", referenced from:
      testing::internal::SuiteApiResolver<testing::Test>::GetSetUpCaseOrSuite(char const*, int) in CSVBusSystemTest.o
      testing::internal::SuiteApiResolver<testing::Test>::GetTearDownCaseOrSuite(char const*, int) in CSVBusSystemTest.o
  "testing::internal::GTestLog::GTestLog(testing::internal::GTestLogSeverity, char const*, int)", referenced from:
      testing::internal::SuiteApiResolver<testing::Test>::GetSetUpCaseOrSuite(char const*, int) in CSVBusSystemTest.o
      testing::internal::SuiteApiResolver<testing::Test>::GetTearDownCaseOrSuite(char const*, int) in CSVBusSystemTest.o
  "testing::internal::GTestLog::~GTestLog()", referenced from:
      testing::internal::SuiteApiResolver<testing::Test>::GetSetUpCaseOrSuite(char const*, int) in CSVBusSystemTest.o
      testing::internal::SuiteApiResolver<testing::Test>::GetTearDownCaseOrSuite(char const*, int) in CSVBusSystemTest.o
  "testing::internal::EqFailure(char const*, char const*, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const&, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const&, bool)", referenced from:
      testing::AssertionResult testing::internal::CmpHelperEQFailure<unsigned long, int>(char const*, char const*, unsigned long const&, int const&) in CSVBusSystemTest.o
      testing::AssertionResult testing::internal::CmpHelperEQFailure<unsigned long long, int>(char const*, char const*, unsigned long long const&, int const&) in CSVBusSystemTest.o
  "CDSVReader::End() const", referenced from:
      CCSVBusSystem::CCSVBusSystem(std::__1::shared_ptr<CDSVReader>, std::__1::shared_ptr<CDSVReader>) in CSVBusSystem.o
  "testing::internal::AssertHelper::operator=(testing::Message const&) const", referenced from:
      CSVBusSystem_SimpleExampleTest_Test::TestBody() in CSVBusSystemTest.o
  "typeinfo for testing::Test", referenced from:
      typeinfo for CSVBusSystem_SimpleExampleTest_Test in CSVBusSystemTest.o
  "vtable for CCSVBusSystem", referenced from:
      CCSVBusSystem::CCSVBusSystem(std::__1::shared_ptr<CDSVReader>, std::__1::shared_ptr<CDSVReader>) in CSVBusSystem.o
  NOTE: a missing vtable usually means the first non-inline virtual member function has no definition.
ld: symbol(s) not found for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [bin/testcsvbussystem] Error 1
pardan@campus-044-159 proj3 % 
```

### Response 1
The error you're encountering now is related to unresolved symbols during linking. These symbols are typically functions or variables declared in your source files but not defined. Here's a breakdown of the issues:

Undefined symbols for architecture arm64: This error indicates that the linker couldn't find the definitions for certain symbols. These symbols include functions like CDSVReader::ReadRow, CDSVReader::CDSVReader, CDSVReader::~CDSVReader, CStringDataSource::CStringDataSource, and StringUtils::Lower, among others.

No matching constructor for initialization of 'CDSVReader': This error suggests that there's no constructor defined for CDSVReader that matches the arguments provided during its initialization.

Note: a missing vtable usually means the first non-inline virtual member function has no definition: This note indicates that the virtual member functions of a class (CCSVBusSystem, in this case) might not have been defined.

To resolve these issues:

Make sure that all member functions declared in your classes (CDSVReader, CStringDataSource, CCSVBusSystem, etc.) are defined. This includes constructors, destructors, and any other member functions.

Ensure that the necessary source files containing the implementations of these classes are included in your build process.

Check for any typos or mismatches between function declarations and definitions.

If you're using any external libraries, ensure that you're linking against them properly.

By addressing these issues, you should be able to resolve the linking errors and successfully compile your program. If you need further assistance, feel free to provide additional details or code snippets.

### Changes 1
This prompt helped us discover we were not including everything we needed to in the link file. Because of this, we realized we 
were missing $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/DSVReader.o and $(OBJ_DIR)/StringDataSource.o
```cpp
...
## BusSystem
$(BIN_DIR)/testcsvbs: $(OBJ_DIR)/CSVBusSystem.o $(OBJ_DIR)/CSVBusSystemTest.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/DSVReader.o $(OBJ_DIR)/StringUtils.o
	$(CXX) -o $(BIN_DIR)/testcsvbs $(CXXFLAGS) $(OBJ_DIR)/CSVBusSystem.o $(OBJ_DIR)/CSVBusSystemTest.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/DSVReader.o $(OBJ_DIR)/StringUtils.o $(LDFLAGS)

$(OBJ_DIR)/CSVBusSystem.o: $(SRC_DIR)/CSVBusSystem.cpp $(INC_DIR)/CSVBusSystem.h
	$(CXX) -o $(OBJ_DIR)/CSVBusSystem.o -c $(CXXFLAGS) $(SRC_DIR)/CSVBusSystem.cpp

$(OBJ_DIR)/CSVBusSystemTest.o: $(TEST_SRC_DIR)/CSVBusSystemTest.cpp
	$(CXX) -o $(OBJ_DIR)/CSVBusSystemTest.o -c $(CXXFLAGS) $(TEST_SRC_DIR)/CSVBusSystemTest.cpp
```

