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

class JsonDataLoader : public AbstractDataFetcher
{
public:
JsonDataLoader();
    JsonDataLoader(const DataSource source, const std::string location);
    virtual ~JsonDataLoader() {};

    bool ValidateData(const std::string& data_str) override;
    void SetDataCollection(const std::string& dataStr) override;

private:

};

#endif // JSON_DATA_LOADER_H
