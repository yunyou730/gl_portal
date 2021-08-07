#include "../headers/AYYIO.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace ayy
{
void ReadFile(const std::string& filePath,std::string& outString)
{
    std::ifstream file;
    // ensure ifstream objects can throw exceptions:
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(filePath);
        std::stringstream fileStream;
        fileStream << file.rdbuf();
        file.close();
        outString = fileStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR::READFILE::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}
}

