

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
        throw std::runtime_error("Failed to open the file.");
    }
}

LocalFileDataLoader::~LocalFileDataLoader()
{
    if (inputFile.is_open())
    {
        inputFile.close(); // Close the file
    }
}

std::string LocalFileDataLoader::FetchData()
{
    std::cout << "Fetching Data string\n";
    std::ostringstream ss; // Create a stringstream
    ss << inputFile.rdbuf(); // Read the entire file buffer into the stringstream

    // std::string line;
    // std::stringstream sss(ss.str());
    // for (int i = 0; i < 150; i++)
    // {
    //     std::getline(sss, line);
    //     std::cout << line << "\n\n";
    // }
    std::cout << "End fetching data string\n";
    return ss.str();
}

std::variant<std::string, simdjson::dom::element>  LocalFileDataLoader::FetchData2()
{
    std::cout << "Fetching Data 2 Parsing the data\n";

    std::string jsonString = FetchData();

    simdjson::dom::parser parser;
    simdjson::dom::element doc;
    simdjson::error_code error = parser.parse(jsonString).get(doc);

    std::cout << "End parsing the data\n";
    if (!error) {
        return doc;
    }
    std::cerr << error << std::endl;

    return jsonString;

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

bool LocalFileDataLoader::fileExists(const std::string& path)
{
    std::ifstream file(path);
    return file.good();
}
