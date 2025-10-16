#include "CSVDataLoader.h"

#include <sstream>

#include <iostream>

CSVDataLoader::CSVDataLoader()
{

}

CSVDataLoader::CSVDataLoader(DataSource& source,
                             std::string& location):
                             source(source), location(location)
{

}

std::string CSVDataLoader::LoadData()
{
    return "";    
}

bool CSVDataLoader::ValidateData([[maybe_unused]] const std::string& data_str)
{
    if (source == DataSource::LOCAL_FILE)
        return true;

    return false;
}

std::vector<std::vector<std::string>> CSVDataLoader::ParseCSVData(const std::string& data_str)
{
    std::stringstream ss(data_str);
    std::string line;
    std::vector<std::vector<std::string>> data;

    while (std::getline(ss, line))
    {
        std::vector<std::string> row;
        std::stringstream ss1(line);
        std::string cell;

        //sprlit the line byu comma delimiter
        while (std::getline(ss1, cell, ','))
        {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    for (auto i = 0; i < 10; i++)
    {
        std::vector<std::string> temp = data[i];

        for(const auto& val : temp)
        {
            std::cout << val << "  ";
        }

        std::cout << "\n";
    }

    return data;
}

void CSVDataLoader::SetDataCollection([[maybe_unused]]const std::string& dataStr)
{

}
