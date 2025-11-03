/* --- Data.cpp --- */

/* ------------------------------------------
author: Pnbeldor
date: 9/17/2025
------------------------------------------ */

#include "Data.h"

#include <cmath>
#include <iostream>

#include "Utils.h"

Data::Data() : collection_ptr(nullptr)
{
    datasetPtr = nullptr;
    dataFeatureMapPtr = nullptr;
    collection_ptr = std::make_unique<DataCollection>();
}

Data::Data(const std::string fieldNames, const std::string fieldDatatypes)
{
    Utils utils;

    const auto names = utils.ParseCSVDataLine(fieldNames);
    const auto types = utils.ParseCSVDataLine(fieldDatatypes);

    /* std::vector<std::pair<std::string, std::string>> */ 
    auto fields = utils.ZipVectors(names, types);

    datasetPtr = std::make_unique<std::vector<std::pair<std::string, std::string>>>(fields);
}

// void Data::SetDatasetPtr(const std::string fieldNames, const std::string fieldDatatypes)
// {
//     Utils utils;

//     const auto names = utils.ParseCSVDataLine(fieldNames);
//     const auto types = utils.ParseCSVDataLine(fieldDatatypes);

//     /* std::vector<std::pair<std::string, std::string>> */ 
//     auto fields = utils.ZipVectors(names, types);

//     datasetPtr = std::make_unique<std::vector<std::pair<std::string, std::string>>>(fields);
// }

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

const dataFeatureMap Data::SetDataFeatureMap(const Json::Value& dataFeature)
{
    dataFeatureMap responseMap;
    std::vector<std::string> headers;

    for (const auto& object : dataFeature)
    {
        auto keyValuePair = object.getMemberNames();

        for (const auto& val : keyValuePair)
        {
            //std::cout << val << "  ";
            if (!object[val].isObject())
            {
                responseMap[val].push_back(object[val].asString());
            }

            else if (val != "geometry" && val != "meta")
            {
                const Json::Value jValue = object[val];
                auto keyValPair = jValue.getMemberNames();

                for (const auto& kv : keyValPair)
                {
                    responseMap[kv].push_back(jValue[kv].asString());
                }
            }
        }
    }

    dataFeatureMapPtr = std::make_unique<dataFeatureMap>(responseMap);

    // auto it = responseMap.begin();

    // std::advance(it, 10);
    
    // std::cout << it->second.size() << "\n\n";

    // for (int i = 0; i < 10; i++)
    // {
    //     for (const auto& [key, value] : responseMap)
    //     {
    //         std::cout << key << " = " << value[i] << "  ";
    //     }

    //     std::cout << "\n\n";
    // }

    return responseMap;
}

const std::vector<DataFeature> Data::setDataFeature(const Json::Value& data_feature)
{
    SetDataFeatureMap(data_feature);

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

void Data::SetDataCollection(const std::string& data_str, DataFormat format)
{
    switch(format)
    {
        case DataFormat::JSON:
        {
            SetCollectionWithJSONData(data_str);
            break;
        }
        case DataFormat::CSV:
        {
            SetCollectionWithCSVData(data_str);
            break;
        }
        default:
        {
            std::cout << "Unknown data format\n";
            break;
        }
    }
}

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

void Data::SetCollectionWithCSVData(const std::string& data_str)
{
    auto parseData = ParseCSVData(data_str);
    dataFeatureMapPtr = make_unique<dataFeatureMap>(parseData);
/*
    std::vector<DataFeature> features;
    std::vector<std::string> fieldNames;

    if (parseData.size() != 0)
    {
        fieldNames.reserve(parseData.size()); // Reserve memory
        //auto it = parseData.begin();
        //dataSize = it->second.size();
    }

    for (const auto& pair : parseData)
        fieldNames.push_back(pair.first);

    for ( size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < fieldNames.size(); j++)
        {
            std::cout << fieldNames[j] << " = " << parseData[fieldNames[j]][i] << " --- ";
            //std::cout << fieldNames[j] << " = " << parseData.find(fieldNames[j])->second[i] << " --- ";
        }
        std::cout << "\n\n";
    }
        */
}


void Data::SetCollectionWithJSONData(const std::string& data_str)
{
    Json::Value data = ParseJsonData(data_str);

    if (data == Json::nullValue)
    {
        std::cout << "Error passing dat string to json!\n";
        std::cout << "Data was: " << data_str << "\n\n";

        return;
    }

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

    std::vector<std::string> jsonKeys = {"features", "columns", "data"};

    for (const auto& key : jsonKeys)
    {
        //if (data.isMember("features"))
        if (data.isMember(key))
        {
            this->collection_ptr->features = std::make_unique<std::vector<DataFeature>>(setDataFeature(data[key]));
        }
    }
}

/*
void Data::SetCollectionWithCSVData(const std::string& data_str)
{
    std::unordered_map<std::string, std::vector<std::string>> parseData = ParseCSVData(data_str);

    std::vector<DataFeature> features;

    size_t dataSize = 0;

    if (parseData.size() != 0)
    {
        auto it = parseData.begin();
        dataSize = it->second.size();
    }

    for ( size_t i = 0; i < dataSize; i++)
    {
        DataFeature dataFeature;

        dataFeature.properties_ptr->ccn = parseData.find("CCN")->second[i];
        dataFeature.properties_ptr->report_date = parseData.find("REPORT_DAT")->second[i];
        dataFeature.properties_ptr->shift = parseData.find("SHIFT")->second[i];
        dataFeature.properties_ptr->method = parseData.find("METHOD")->second[i];
        dataFeature.properties_ptr->offense = parseData.find("OFFENSE")->second[i];
        dataFeature.properties_ptr->block = parseData.find("BLOCK")->second[i];
        
        try
        {
            dataFeature.properties_ptr->x_block = std::stod(parseData.find("XBLOCK")->second[i]);
            dataFeature.properties_ptr->y_blocK = std::stod(parseData.find("YBLOCK")->second[i]);
            dataFeature.properties_ptr->longitude = std::stod(parseData.find("LONGITUDE")->second[i]);
            dataFeature.properties_ptr->latitude = std::stod(parseData.find("LATITUDE")->second[i]);
            dataFeature.properties_ptr->object_id = std::stod(parseData.find("OBJECTID")->second[i]);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << "  " << e.what() << std::endl;
        }
        dataFeature.properties_ptr->ward = parseData.find("WARD")->second[i];
        dataFeature.properties_ptr->anc = parseData.find("ANC")->second[i];
        dataFeature.properties_ptr->district = parseData.find("DISTRICT")->second[i];
        dataFeature.properties_ptr->psa = parseData.find("PSA")->second[i];
        dataFeature.properties_ptr->neighborHood_cluster = parseData.find("NEIGHBORHOOD_CLUSTER")->second[i];
        dataFeature.properties_ptr->block_group = parseData.find("BLOCK_GROUP")->second[i];
        dataFeature.properties_ptr->census_tract = parseData.find("CENSUS_TRACT")->second[i];
        dataFeature.properties_ptr->voting_precinct = parseData.find("VOTING_PRECINCT")->second[i];
        dataFeature.properties_ptr->start_date = parseData.find("START_DATE")->second[i];
        dataFeature.properties_ptr->end_date = parseData.find("END_DATE")->second[i];

        features.push_back(dataFeature);
    }

    this->collection_ptr->features = std::make_unique<std::vector<DataFeature>>(features);
}
 */
Json::Value Data::ParseJsonData(const std::string& data_str)
{
    Json::Value jsonData;
    Json::Reader jsonReader;

    if (jsonReader.parse(data_str, jsonData))
    {
        return jsonData;
    }

    return Json::nullValue;
}

dataFeatureMap Data::ParseCSVData(const std::string& data_str)
{
    Utils utils;
    std::stringstream ss(data_str);
    std::string line;
    dataFeatureMap data;
    std::vector<std::string> headers;

    // Read Header row
    if (std::getline(ss, line))
    {
        headers = utils.ParseCSVDataLine(line);
    }

    while (std::getline(ss, line))
    {
        auto result = utils.ParseCSVDataLine(line);
        if (result.size() == headers.size())
        {
            for (size_t i = 0; i < result.size(); i++)
                data[headers[i]].push_back(result[i]);
        }
    }

    return data;
}
