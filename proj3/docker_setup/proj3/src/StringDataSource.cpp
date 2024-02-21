#include "StringDataSource.h"

// Constructor with string parameter
CStringDataSource::CStringDataSource(const std::string &str) : DString(str), DIndex(0){

}

// Check if end of string is reached
bool CStringDataSource::End() const noexcept{
    return DIndex >= DString.length();
}

// Get the next character from the string
bool CStringDataSource::Get(char &ch) noexcept{
    if(DIndex < DString.length()){
        ch = DString[DIndex];
        DIndex++;
        return true;
    }
    return false;
}

// Peek at the next character in the string
bool CStringDataSource::Peek(char &ch) noexcept{
    if(DIndex < DString.length()){
        ch = DString[DIndex];
        return true;
    }
    return false;
}

// Read characters into a buffer from the string
bool CStringDataSource::Read(std::vector<char> &buf, std::size_t count) noexcept{
    buf.clear();
    while(buf.size() < count){
        char TempChar;
        if(Get(TempChar)){
            buf.push_back(TempChar);
        }
        else{
            break;
        }
    }
    return !buf.empty();
}
