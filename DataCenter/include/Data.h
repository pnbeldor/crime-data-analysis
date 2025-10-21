/* --- Data.h --- */

/* ------------------------------------------
Author: Pnbeldor
Date: 9/17/2025
------------------------------------------ */

#ifndef DATA_H
#define DATA_H

#include <memory>
#include <unordered_map>
#include <vector>

#include <jsoncpp/json/json.h>

#include "DataConfig.h"

struct DataProperties
{
    std::string ccn;
    std::string report_date;
    std::string shift;
    std::string method;
    std::string offense;
    std::string block;
    double x_block;
    double y_blocK;
    std::string ward;
    std::string anc;
    std::string district;
    std::string psa;
    std::string neighborHood_cluster;
    std::string block_group;
    std::string census_tract;
    std::string voting_precinct;
    double latitude;
    double longitude;
    std::string bid;
    std::string start_date;
    std::string end_date;
    double object_id;
    std::string octo_record_id;
    //Add value for geometry
    // if geometry type is point: lat and long
};

struct DataFeature {
    std::string type;
    std::unique_ptr<DataProperties> properties_ptr;

    DataFeature() : type(""), properties_ptr(nullptr)
    {
        properties_ptr = std::make_unique<DataProperties>();
    }

    ~DataFeature(){}

    DataFeature(const DataFeature& other)
    {
        this->type = other.type;
        this->properties_ptr = std::make_unique<DataProperties>(*other.properties_ptr);
    }
    
    DataFeature(DataFeature&& other) noexcept :type(other.type),
    properties_ptr(std::move(other.properties_ptr))
    {
        //*this = std::move(other);
    }

    DataFeature& operator=(DataFeature&& other) noexcept
    {
        if (this != &other)
        {
            type = other.type;
            properties_ptr = std::make_unique<DataProperties>(*other.properties_ptr);
        }

        return *this;
    }
};

struct DataCollection
{
    std::string type;
    std::string name;
    std::string crs_type;
    std::string crs_property_name;
    std::unique_ptr<std::vector<DataFeature>> features;

    explicit DataCollection()
    :type(""), name(""), crs_type(""), crs_property_name(""), features(nullptr)
    {
        features = std::make_unique<std::vector<DataFeature>>();
    }

    ~DataCollection() = default;

    DataCollection(const DataCollection& other) = default;
    DataCollection& operator=(DataCollection& other) = default;
    DataCollection(DataCollection&& other) = default;
    DataCollection& operator=(DataCollection&& other) = default;

};

class Data {
public:
    Data();
    virtual ~Data();

    void printCollection() const;
    void printFeature(const DataFeature& record) const;
    const std::vector<DataFeature> setDataFeature(const Json::Value& data);
    const DataCollection setDataCollection(const Json::Value& data);
    void SetDataCollection(const std::string& data_str, DataFormat format = DataFormat::JSON);
    const DataProperties setDataProperties(const Json::Value& data) const;
    const DataProperties setDataProperties(const std::string& data) const;

    DataCollection& GetCollectionPtr()
    {
        return *collection_ptr;
    }

    DataCollection* GetDataCollection()
    {
        return collection_ptr.get();
    }

private:
    Json::Value ParseJsonData(const std::string& data_str);
    std::vector<std::vector<std::string>> ParseCSVData(const std::string& data_str);
    std::map<std::string, std::vector<std::string>> ParseCSVData2(const std::string& data_str);

    void SetCollectionWithJSONData(const std::string& data_str);
    void SetCollectionWithCSVData(const std::string& data_str);
    void SetCollectionWithCSVData2(const std::string& data_str);


private:
    std::unique_ptr<DataCollection> collection_ptr;
};

#endif // DATA_H
