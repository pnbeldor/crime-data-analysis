#include "CSVDataLoader.h"

#include <sstream>
#include <iostream>

#include "DataConfig.h"

CSVDataLoader::CSVDataLoader()
{

}

CSVDataLoader::CSVDataLoader(DataSource& source, const std::string& location)
    : AbstractDataFetcher(source, location)
{
}

bool CSVDataLoader::ValidateData([[maybe_unused]] const std::string& data_str)
{
    return true;
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
        bool in_quotes = false;
        std::string current_cell;

        //separate the line by comma delimiter
        for (char c : line)
        {
            if (c == '"'){
                in_quotes = !in_quotes;
            } else if (c == ',' && !in_quotes) {
                row.push_back(current_cell);
                current_cell.clear();
            } else {
                current_cell += c;
            }
        }

        row.push_back(current_cell); // Add the last cell
        data.push_back(row);
    }

    return data;
}

void CSVDataLoader::SetDataCollection(const std::string& dataStr)
{
    this->getDataPtr()->SetDataCollection(dataStr, DataFormat::CSV);
}
