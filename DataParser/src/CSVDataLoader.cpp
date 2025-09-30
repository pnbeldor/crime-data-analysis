#include "CSVDataLoader.h"

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
    return true;
}

std::string CSVDataLoader::ParseCSVData(const std::string& data_str)
{
    return data_str;
}
