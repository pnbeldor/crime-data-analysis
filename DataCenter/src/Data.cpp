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

void Data::SetDataCollection(const std::string& data_str, DataFormat format)
{
    switch(format)
    {
        case DataFormat::JSON:
        {
            std::cout << "JSON collection data is being set\n\n";
            SetCollectionWithJSONData(data_str);
            break;
        }
        case DataFormat::CSV:
        {
            std::cout << "CSV collection data is being set\n\n";
            SetCollectionWithCSVData2(data_str);
            break;
        }
        default:
        {
            std::cout << "Unknown data format\n";
            break;
        }
    }
    // if (format != DataFormat::JSON)
    //     return;

    // Json::Value data;
    // Json::Reader jsonReader;

    // if (!jsonReader.parse(data_str, data))
    // {
    //     std::cout << "Error passing dat string to json!\n";
    //     std::cout << "Data was: " << data_str << "\n\n";
    // }
    // else
    // {
    //     this->collection_ptr->type = data.get("type", "").asString();
    //     this->collection_ptr->name = data.get("name", "").asString();

    //     if (data.isMember("crs"))
    //     {
    //         this->collection_ptr->crs_type = data["crs"].get("type", "").asString();

    //         if (data["crs"].isMember("properties"))
    //         {
    //             this->collection_ptr->crs_property_name = data["crs"]["properties"].get("name", "").asString();
    //         }
    //     }

    //     if (data.isMember("features"))
    //     {
    //         this->collection_ptr->features = std::make_unique<std::vector<DataFeature>>(setDataFeature(data["features"]));
    //     }
    // }
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

    if (data.isMember("features"))
    {
        this->collection_ptr->features = std::make_unique<std::vector<DataFeature>>(setDataFeature(data["features"]));
    }
}


void Data::SetCollectionWithCSVData2(const std::string& data_str)
{
    [[maybe_unused]] std::map<std::string, std::vector<std::string>> parseData = ParseCSVData2(data_str);

    std::vector<DataFeature> features;
    /*
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

    */
    
    auto it = parseData.begin();
    size_t dataSize = it->second.size();

    std::cout << "====================The number of elements is: " << dataSize << "======================================\n\n";

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

void Data::SetCollectionWithCSVData(const std::string& data_str)
{
    std::vector<std::vector<std::string>> parseData = ParseCSVData(data_str);

    std::vector<DataFeature> features;
    for (const auto& data : parseData)
    {
        DataFeature dataFeature;

        dataFeature.properties_ptr->ccn = data[2];
        dataFeature.properties_ptr->report_date = data[3];
        dataFeature.properties_ptr->shift = data[4];
        dataFeature.properties_ptr->method = data[5];
        dataFeature.properties_ptr->offense = data[6];
        dataFeature.properties_ptr->block = data[7];
        try {
        dataFeature.properties_ptr->x_block = std::stod(data[8]);
        dataFeature.properties_ptr->y_blocK = std::stod(data[9]);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " <<data[8] << "  " <<data[9] << "  " << e.what() << std::endl;
        }
        dataFeature.properties_ptr->ward = data[10];
        dataFeature.properties_ptr->anc = data[11];
        dataFeature.properties_ptr->district = data[12];
        dataFeature.properties_ptr->psa = data[13];
        dataFeature.properties_ptr->neighborHood_cluster = data[14];
        dataFeature.properties_ptr->block_group = data[15];
        dataFeature.properties_ptr->census_tract = data[16];
        dataFeature.properties_ptr->voting_precinct = data[17];
        
        try {
            dataFeature.properties_ptr->latitude = std::stod(data[18]);
            dataFeature.properties_ptr->longitude = std::stod(data[19]);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " <<data[18] << "  " <<data[19] << "  " << e.what() << std::endl;
        }

        features.push_back(dataFeature);
    }

    this->collection_ptr->features = std::make_unique<std::vector<DataFeature>>(features);

}

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

std::vector<std::vector<std::string>> Data::ParseCSVData(const std::string& data_str)
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
        for (char c : line) {
            if (c == '"') {
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

    for (auto i = 0; i < 10; i++)
    {
        std::vector<std::string> temp = data[i];

        for(const auto& val : temp)
        {
            std::cout << val << "  ";
        }

        std::cout << "\n";
    }

    return data;
}

std::map<std::string, std::vector<std::string>> Data::ParseCSVData2(const std::string& data_str)
{
    std::stringstream ss(data_str);
    std::string line;
    std::map<std::string, std::vector<std::string>> data;
    std::vector<std::string> headers;

    // Read Header row
    if (std::getline(ss, line))
    {
        std::stringstream ss1(line);
        bool in_quotes = false;
        std::string current_cell;

        //separate the line by comma delimiter
        for (char c : line) {
            if (c == '"') {
                in_quotes = !in_quotes;
            } else if (c == ',' && !in_quotes) {
                headers.push_back(current_cell);
                current_cell.clear();
            } else {
                current_cell += c;
            }
        }

        headers.push_back(current_cell);
    }

    // Read data rows
    while (std::getline(ss, line))
    {
        std::vector<std::string> row;
        std::stringstream ss1(line);
        bool in_quotes = false;
        std::string current_cell;
        int col_index = 0;

        //separate the line by comma delimiter
        for (char c : line) {
            if (c == '"') {
                in_quotes = !in_quotes;
            } else if (c == ',' && !in_quotes) {
                data[headers[col_index]].push_back(current_cell);
                current_cell.clear();
                col_index++;
            } else {
                current_cell += c;
            }
        }

        data[headers[col_index]].push_back(current_cell); // Add the last cell
    }

    for (auto i = 0; i < 2; i++)
    {
        for (const auto& [key, value] : data)
        //for (int j = 0; j < 10; j++) {
        //    std::vector<std::string> temp = data[headers[j]];
            std::cout << "\"" << key << "\"  " << value[i] << "  ";
        //}

        std::cout << "\n";
    }

    return data;
}

