

#include "LocalFileDataLoader.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

LocalFileDataLoader::LocalFileDataLoader(const std::string& filePath)
{
    inputFile.open(filePath);

    if (!inputFile.is_open()) { // Check if the file opened successfully
        std::cerr << "Error: Could not open file " << filePath << std::endl;
    }
}

LocalFileDataLoader::~LocalFileDataLoader()
{
    if (inputFile.is_open())
    {
        inputFile.close(); // Close the file
    }
}

std::string LocalFileDataLoader::fetchData(const std::string& filePath)
{
    //file_stream.open(file_path, std::ios::binary);

    //std::ifstream inputFile(filePath); // Open the file
    std::string fileContent;

    if (inputFile.is_open()) { // Check if the file opened successfully
        std::ostringstream ss; // Create a stringstream
        ss << inputFile.rdbuf(); // Read the entire file buffer into the stringstream
        fileContent = ss.str(); // Get the string from the stringstream
        inputFile.close(); // Close the file
    } else {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
    }
    return fileContent;
}

bool LocalFileDataLoader::canHandle(const std::string& source) const
{
    if (source.empty())
        return false;

    // Check for common URL schemes
    if (source.find("://") != std::string::npos) {
        return false;
    }
    
    // Check if file exists and is readable
    std::error_code ec;
    return std::filesystem::exists(source, ec) && 
            std::filesystem::is_regular_file(source, ec);
}

bool LocalFileDataLoader::fileExists(const std::string& path) {
    std::ifstream file(path);
    return file.good();
}
