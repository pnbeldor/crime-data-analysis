#include "Utils.h"

#include <sstream>

Utils::Utils()
{

}

Utils::~Utils()
{

}

std::string Utils::ParseElement(const simdjson::dom::element& element)
{
    std::string result;

    switch (element.type())
    {
        case simdjson::dom::element_type::STRING:
            result = element.get_string().value();
            break;
        case simdjson::dom::element_type::INT64:
            result = std::to_string(element.get_int64().value());
            break;
        case simdjson::dom::element_type::UINT64:
            result = std::to_string(element.get_uint64().value());
            break;
        case simdjson::dom::element_type::DOUBLE:
            result = std::to_string(element.get_double().value());
            break;
        case simdjson::dom::element_type::BOOL:
            result = (element.get_bool().value() ? "true" : "false");
            break;
        case simdjson::dom::element_type::NULL_VALUE:
            result = "NULL";
            break;
        default:
            result = "UNKNOWN";
            break;
    }

    return result;
}


std::vector<std::string> Utils::ParseCSVDataLine(const std::string& dataLine)
{
    std::vector<std::string> row;
    bool inQuotes = false;
    std::string currentCell;

    //separate the line by comma delimiter
    for (char c : dataLine)
    {
        if (c == '"'){
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            row.push_back(currentCell);
            currentCell.clear();
        } else {
            currentCell += c;
        }
    }

    row.push_back(currentCell); // Add the last cell

    return row;
}


std::vector<std::vector<std::string>> Utils::ParseCSVData(const std::string& dataStr)
{
    std::stringstream ss(dataStr);
    std::string line;
    std::vector<std::vector<std::string>> data;

    while (std::getline(ss, line))
    {
        std::vector<std::string> row;
        std::stringstream ss1(line);
        bool inQuotes = false;
        std::string currentCell;

        //separate the line by comma delimiter
        for (char c : line)
        {
            if (c == '"'){
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                row.push_back(currentCell);
                currentCell.clear();
            } else {
                currentCell += c;
            }
        }

        row.push_back(currentCell); // Add the last cell
        data.push_back(row);
    }

    return data;
}
