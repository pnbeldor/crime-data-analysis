/* --- JsonDataLoader.h --- */

/* ------------------------------------------
Author: Pnbeldor
Date: 9/24/2025
------------------------------------------ */

#ifndef JSON_DATA_LOADER_H
#define JSON_DATA_LOADER_H

#include "AbstractDataFetcher.h"

#include <jsoncpp/json/json.h>

class JsonDataLoader : public AbstractDataFetcher {
public:
    JsonDataLoader();
    JsonDataLoader(DataSource& source, std::string& location);
    //void LoadData(DataSource& source, std::string& location, std::string& dataValue) override;
    std::string LoadData() override;
    bool ValidateData(const std::string& data_str) override;

    virtual ~JsonDataLoader() {};

private:

Json::Value ParseJsonData(const std::string& data_str);

private:
    DataSource source;
    std::string location;

};

#endif // JSON_DATA_LOADER_H
