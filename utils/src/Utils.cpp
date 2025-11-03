#include "Utils.h"

#include <sstream>

Utils::Utils()
{

}

Utils::~Utils()
{

}

std::vector<std::string> Utils::ParseCSVDataLine(const std::string& dataLine)
{
    std::vector<std::string> row;
    bool in_quotes = false;
    std::string current_cell;

    //separate the line by comma delimiter
    for (char c : dataLine)
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

    return row;
}


std::vector<std::vector<std::string>> Utils::ParseCSVData(const std::string& data_str)
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
