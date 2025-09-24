/* --- Data.cpp --- */

/* ------------------------------------------
author: Pnbeldor
date: 9/17/2025
------------------------------------------ */

#include "Data.h"

#include <cmath>

Data::Data() {
    // Constructor
}

Data::~Data() {
    // Destructor
}

DataProperties Data::setDataProperties(const Json::Value& data)
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
    properties.neighboHood_cluster = data.get("NEIGHBORHOOD_CLUSTER", "").asString();
    properties.block_group = data.get("BLOCK_GROUP", "").asString();
    properties.census_tract = data.get("CENSUS_TRACT", "").asString();
    properties.voting_precint = data.get("VOTING_PRECINCT", "").asString();
    properties.latitude = data.get("LATITUDE", NAN).asDouble();
    properties.longitute = data.get("LONGITUDE", NAN).asDouble();
    properties.start_date = data.get("START_DATE", "").asString();
    properties.end_date = data.get("END_DATE", "").asString();
    properties.object_id = data.get("OBJECT_ID", NAN).asDouble();

    return properties;
}

std::vector<DataFeature> Data::setDataFeature(const Json::Value& data_feature)
{
    std::vector<DataFeature> feature_coll;

    DataFeature feature;

    for (const auto& object : data_feature)
    {
        feature.type = object.get("type", "").asString();

        feature.properties = setDataProperties(object["properties"]);

        feature_coll.push_back(feature);
    }

    return feature_coll;
}

DataCollection Data::setDataCollection(const Json::Value& data)
{
    DataCollection collection;
    collection.type = data.get("type", "").asString();
    collection.name = data.get("name", "").asString();

    if (data.isMember("crs"))
    {
        collection.crs_type = data["crs"].get("type", "").asString();

        if (data["crs"].isMember("properties"))
        {
            collection.crs_property_name = data["crs"]["properties"].get("name", "").asString();
        }
    }

    if (data.isMember("features")) {
        collection.features = std::make_unique<std::vector<DataFeature>>(setDataFeature(data["features"]));
    }

    return collection;
}
