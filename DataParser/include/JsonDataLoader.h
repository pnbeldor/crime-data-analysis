/* --- JsonDataLoader.h --- */

/* ------------------------------------------
Author: Pnbeldor
Date: 9/24/2025
------------------------------------------ */

#ifndef JSON_DATA_LOADER_H
#define JSON_DATA_LOADER_H

#include "AbstractDataFetcher.h"

#include <jsoncpp/json/json.h>

#include "Data.h"

class JsonDataLoader : public AbstractDataFetcher {
public:
    JsonDataLoader();
    JsonDataLoader(const DataSource& source, const std::string& location);
    bool ValidateData(const std::string& data_str) override;
    DataProperties setDataProperties(const Json::Value& data);
    std::vector<DataFeature> setDataFeature(const Json::Value& data_feature);
    void SetDataCollection(const std::string& dataStr) override;

    virtual ~JsonDataLoader() {};

private:

Json::Value ParseJsonData(const std::string& data_str);

};

#endif // JSON_DATA_LOADER_H
