

#include "JsonDataLoader.h"

#include <iostream>
#include <cmath>

#include "LocalFileDataLoader.h"
#include "URLDataLoader.h"

JsonDataLoader::JsonDataLoader()
{

}

JsonDataLoader::JsonDataLoader(const DataSource& source,
                               const std::string& location): AbstractDataFetcher(source, location)//,
                //source(source), location(location)
{
//    AbstractDataFetcher(source, location);
}

/*
std::string JsonDataLoader::LoadData()
{
    IDataFetcher* loader;

    const DataSource source = GetSource();
    const std::string& location = GetLocation();

    if (source == DataSource::LOCAL_FILE)
    {
        loader = new LocalFileDataLoader(location);
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
*/

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

DataProperties JsonDataLoader::setDataProperties(const Json::Value& data)
{
    DataProperties properties;

    properties.ccn = data.get("CCN", "").asString();
    properties.report_date = data.get("REPORT_DAT", "").asString();
    properties.shift = data.get("SHIFT", "").asString();
    properties.method = data.get("METHOD", "").asString();
    properties.offense = data.get("OFFENSE", "").asString();
    properties.block = data.get("BLOCK", "").asString();
    properties.x_block = data.get("X_BLOCK", NAN).asDouble();
    properties.y_blocK = data.get("Y_BLOCK", NAN).asDouble();
    properties.ward = data.get("WARD", "").asString();
    properties.anc = data.get("ANC", "").asString();
    properties.district = data.get("DISTRICT", "").asString();
    properties.psa = data.get("PSA", "").asString();
    properties.neighborHood_cluster = data.get("NEIGHBORHOOD_CLUSTER", "").asString();
    properties.block_group = data.get("BLOCK_GROUP", "").asString();
    properties.census_tract = data.get("CENSUS_TRACT", "").asString();
    properties.voting_precinct = data.get("VOTING_PRECINCT", "").asString();
    properties.latitude = data.get("LATITUDE", NAN).asDouble();
    properties.longitude = data.get("LONGITUDE", NAN).asDouble();
    properties.start_date = data.get("START_DATE", "").asString();
    properties.end_date = data.get("END_DATE", "").asString();
    properties.object_id = data.get("OBJECT_ID", NAN).asDouble();

    return properties;
}

std::vector<DataFeature> JsonDataLoader::setDataFeature(const Json::Value& data_feature)
{
    std::vector<DataFeature> feature_coll;

    DataFeature feature;

    for (const auto& object : data_feature)
    {
        feature.type = object.get("type", "").asString();

        DataProperties properties = setDataProperties(object["properties"]);
        feature.properties_ptr = std::make_unique<DataProperties>(properties);

        feature_coll.push_back(feature);
    }

    return feature_coll;
}

/* void JsonDataLoader::SetDataCollection(const std::string& dataStr)
{
    DataCollection* collection_ = this->data_->GetCollection();

    
    Json::Value data = ParseJsonData(dataStr);
    if (data != Json::nullValue)
    {
        collection_->type = data.get("type", "").asString();
        collection_->name = data.get("name", "").asString();

        if (data.isMember("crs"))
        {
            collection_->crs_type = data["crs"].get("type", "").asString();

            if (data["crs"].isMember("properties"))
            {
                collection_->crs_property_name = data["crs"]["properties"].get("name", "").asString();
            }
        }

        if (data.isMember("features"))
        {
            collection_->features = std::make_unique<std::vector<DataFeature>>(setDataFeature(data["features"]));
        }
    }
} */

void JsonDataLoader::SetDataCollection(const std::string& dataStr)
{
    //DataCollection* collection_ = this->data_->GetCollection();

    DataCollection& collectionPtr = this->data_->GetCollectionPtr();

    
    Json::Value data = ParseJsonData(dataStr);
    if (data != Json::nullValue)
    {
        collectionPtr.type = data.get("type", "").asString();
        collectionPtr.name = data.get("name", "").asString();

        if (data.isMember("crs"))
        {
            collectionPtr.crs_type = data["crs"].get("type", "").asString();

            if (data["crs"].isMember("properties"))
            {
                collectionPtr.crs_property_name = data["crs"]["properties"].get("name", "").asString();
            }
        }

        if (data.isMember("features"))
        {
            collectionPtr.features = std::make_unique<std::vector<DataFeature>>(setDataFeature(data["features"]));
        }
    }
}
