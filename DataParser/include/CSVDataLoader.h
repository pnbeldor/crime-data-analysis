/* --- DataLoaderInterface.cpp --- */

/* ------------------------------------------
author: Pierre Nicolson Beldor
date: 9/24/2025
------------------------------------------ */

#ifndef CSV_DATA_LOADER_H
#define CSV_DATA_LOADER_H

#include "AbstractDataFetcher.h"
#include <string>
#include <vector>

class CSVDataLoader : public AbstractDataFetcher
{
public:
    CSVDataLoader();
    CSVDataLoader(DataSource& source, std::string& location);
    virtual ~CSVDataLoader() {};

    std::string LoadData() override;
    bool ValidateData(const std::string& data_str) override;
    std::vector<std::vector<std::string>> ParseCSVData(const std::string& data_str);
    void SetDataCollection(const std::string& dataStr) override;

private:
    DataSource source;
    std::string location;
};

#endif // CSV_DATA_LOADER_H
