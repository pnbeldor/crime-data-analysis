

#include "JsonDataLoader.h"
#include "LocalFileDataLoader.h"
#include "URLDataLoader.h"

#include <iostream>

JsonDataLoader::JsonDataLoader()
{

}

JsonDataLoader::JsonDataLoader(DataSource& source,
                                std::string& location):
                source(source), location(location)
{
}

std::string JsonDataLoader::LoadData()
{
    IDataFetcher* loader;
    if (source == DataSource::LOCAL_FILE)
    {
        loader = new LocalFileDataLoader();
        return loader->fetchData(location);
    }
    else if (source == DataSource::HTTP_REQUEST)
    {
        loader = new URLDataLoader();
        return loader->fetchData(location);
    }

    std::cout << "Cannot load data from Json\n\n";

    return "";
}

bool JsonDataLoader::ValidateData([[maybe_unused]] const std::string& data_str)
{
    return true;
}

Json::Value JsonDataLoader::ParseJsonData(const std::string& data_str)
{
    Json::Value jsonData;
    Json::Reader jsonReader;

    if (jsonReader.parse(data_str, jsonData))
    {
        return jsonData;
    }

    return Json::nullValue;
}
