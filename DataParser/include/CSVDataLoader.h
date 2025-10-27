/* --- DataLoaderInterface.cpp --- */

/* ------------------------------------------
author: Pierre Nicolson Beldor
date: 9/24/2025
------------------------------------------ */

#ifndef CSV_DATA_LOADER_H
#define CSV_DATA_LOADER_H

#include <string>
#include <vector>

#include "AbstractDataFetcher.h"

class CSVDataLoader : public AbstractDataFetcher
{
public:
    CSVDataLoader(DataSource& source, const std::string& location);
    virtual ~CSVDataLoader() {};

    bool ValidateData(const std::string& data_str) override;
    void SetDataCollection(const std::string& dataStr) override;

private:
    std::vector<std::vector<std::string>> ParseCSVData(const std::string& data_str);
};

#endif // CSV_DATA_LOADER_H
