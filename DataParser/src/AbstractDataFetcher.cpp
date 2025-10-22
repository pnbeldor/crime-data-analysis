/* --- AbstractDataFetcher.cpp --- */

/* ------------------------------------------
author: Pnbeldor
date: 9/26/2025
------------------------------------------ */

#include "AbstractDataFetcher.h"

#include "LocalFileDataLoader.h"
#include "URLDataLoader.h"

AbstractDataFetcher::AbstractDataFetcher()
{
}

AbstractDataFetcher::AbstractDataFetcher(const DataSource& source,
                               const std::string& location)
                : source(source), location(location)
{
    //data_ = std::make_unique<Data>();
}

std::string AbstractDataFetcher::formatToString(DataFormat format)
{
    switch (format) {
        case DataFormat::JSON:
            return "JSON";
        case DataFormat::CSV:
            return "CSV";
        default:
            return "UNKNOWN";
    }
}

std::string AbstractDataFetcher::sourceToString(DataSource source)
{
    switch (source)
    {
        case DataSource::LOCAL_FILE:
            return "LOCAL_FILE";
        case DataSource::HTTP_REQUEST:
            return "HTTP_REQUEST";
        default:
            return "UNKNOWN";
    }
}
std::vector<std::string> AbstractDataFetcher::splitString(const std::string& str, [[maybe_unused]]char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    
    return tokens;
}
std::string AbstractDataFetcher::trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    
    if (start == std::string::npos)
        return "";

    return str.substr(start, end - start + 1);
}

std::string AbstractDataFetcher::LoadData()
{
    IDataFetcher* loader = nullptr;
    std::string fetchedData;

    if (source == DataSource::LOCAL_FILE)
        loader = new LocalFileDataLoader(location);
    else if (source == DataSource::HTTP_REQUEST)
        loader = new URLDataLoader();

    if (loader != nullptr)
        fetchedData = loader->fetchData(location);

    return fetchedData;
}
