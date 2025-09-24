/* --- Data.h --- */

/* ------------------------------------------
Author: Pnbeldor
Date: 9/17/2025
------------------------------------------ */

#ifndef DATA_H
#define DATA_H

#include <memory>
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>

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
    std::string neighboHood_cluster;
    std::string block_group;
    std::string census_tract;
    std::string voting_precint;
    double latitude;
    double longitute;
    std::string bid;
    std::string start_date;
    std::string end_date;
    double object_id;
    std::string octo_record_id;
    //Add value for geometry
    // if geometry type is point: lat and long
};

struct DataFeature{
    std::string type;
    //std::unique_ptr<DataProperties> properties_ptr;
    DataProperties properties;
};

struct DataCollection
{
    std::string type;
    std::string name;
    std::string crs_type;
    std::string crs_property_name;
    std::unique_ptr<std::vector<DataFeature>> features;
};

class Data {
public:
    Data();
    ~Data();
    void print() const;
    std::vector<DataFeature> setDataFeature(const Json::Value& data);
    DataCollection setDataCollection(const Json::Value& data);
    DataProperties setDataProperties(const Json::Value& data);

private:
    std::unique_ptr<Json::Value> data;

};

#endif // DATA_H
