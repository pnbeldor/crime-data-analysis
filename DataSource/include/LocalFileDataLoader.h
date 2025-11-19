/* --- LocalFileDataLoader.h --- */

/* ------------------------------------------
Author: Pierre Nicolson Beldor
Date: 9/26/2025
------------------------------------------ */

#ifndef DATA_SOURCE_LOCAL_FILE_DATA_LOADER_H
#define DATA_SOURCE_LOCAL_FILE_DATA_LOADER_H

#include <fstream>
#include <variant>

#include "IDataFetcher.h"
#include "simdjson.h"

class LocalFileDataLoader : public IDataFetcher {
public:
    LocalFileDataLoader(const std::string& filePath);
    virtual ~LocalFileDataLoader();

    //std::string fetch_data(const std::string& path) override;
    std::string FetchData() override;
    std::variant<std::string, simdjson::dom::element> FetchData2();
    bool canHandle(const std::string& source) const override;
    

private:
    bool fileExists(const std::string& path);

    std::ifstream inputFile;
};

#endif // DATA_SOURCE_LOCAL_FILE_DATA_LOADER_H
