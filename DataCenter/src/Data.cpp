/* --- Data.cpp --- */

/* ------------------------------------------
author: Pnbeldor
date: 9/17/2025
------------------------------------------ */

#include "Data.h"

#include <cmath>
#include <iostream>

Data::Data() : collection_ptr(nullptr)
{
    collection_ptr = std::make_unique<DataCollection>();
}

Data::~Data()
{
    // Destructor
}

const DataProperties Data::setDataProperties(const Json::Value& data) const
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

const std::vector<DataFeature> Data::setDataFeature(const Json::Value& data_feature)
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

void Data::SetDataCollection(const std::string& data_str)
{
    Json::Value data;
    Json::Reader jsonReader;

    if (!jsonReader.parse(data_str, data))
    {
        std::cout << "Error passing dat string to json!\n";
        std::cout << "Data was: " << data_str << "\n\n";
    }
    else
    {
        this->collection_ptr->type = data.get("type", "").asString();
        this->collection_ptr->name = data.get("name", "").asString();

        if (data.isMember("crs"))
        {
            this->collection_ptr->crs_type = data["crs"].get("type", "").asString();

            if (data["crs"].isMember("properties"))
            {
                this->collection_ptr->crs_property_name = data["crs"]["properties"].get("name", "").asString();
            }
        }

        if (data.isMember("features"))
        {
            this->collection_ptr->features = std::make_unique<std::vector<DataFeature>>(setDataFeature(data["features"]));
        }
    }
}

/*
DataCollection Data::setDataCollection(const Json::Value& data)
{
    DataCollection collection;
    this->collection_.type = data.get("type", "").asString();
    this->collection_.name = data.get("name", "").asString();
    
    if (data.isMember("crs"))
    {
        this->collection_.crs_type = data["crs"].get("type", "").asString();
        if (data["crs"].isMember("properties"))
        {
            this->collection_.crs_property_name = data["crs"]["properties"].get("name", "").asString();
        }
    }
    if (data.isMember("features")) {
        this->collection_.features = std::make_unique<std::vector<DataFeature>>(setDataFeature(data["features"]));
    }

    return collection;
}
*/

void Data::printFeature(const DataFeature& record) const
{
    std::cout << "Report Date: " << record.properties_ptr->report_date << "\n";
    std::cout << "Offense: " << record.properties_ptr->offense << "\n";
    std::cout << "Method: " << record.properties_ptr->method << "\n";
    std::cout << "Neighborhood Cluster: " << record.properties_ptr->neighborHood_cluster << "\n";
    std::cout << "ANC: " << record.properties_ptr->anc << "\n";
    std::cout << "Ward: " << record.properties_ptr->ward << "\n";
    std::cout << "Block: " << record.properties_ptr->block << "\n";
    std::cout << "Block Group: " << record.properties_ptr->block_group << "\n";
    std::cout << "Shift: " << record.properties_ptr->shift << "\n";
    std::cout << "District: " << record.properties_ptr->district << "\n";
    std::cout << "Latitude: " << record.properties_ptr->latitude << "\n";
    std::cout << "Longitude: " << record.properties_ptr->longitude<< "\n";
    std::cout << "PSA: " << record.properties_ptr->psa << "\n\n";
}

void Data::printCollection() const
{
    std::cout << "Type = " << this->collection_ptr->type <<"\n";
    std::cout << "Name = " << this->collection_ptr->name << "\n";
    std::cout << "crs type = " << this->collection_ptr->crs_type <<"\n";
    std::cout << "CRS Properties Name = " << this->collection_ptr->crs_property_name << "\n";
    
    if (this->collection_ptr->features != nullptr)
    {
        for (const auto& record : (*this->collection_ptr->features))
        {
            printFeature(record);
        }
    }
}
