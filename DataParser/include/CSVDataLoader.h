/* --- DataLoaderInterface.cpp --- */

/* ------------------------------------------
author: Pierre Nicolson Beldor
date: 9/24/2025
------------------------------------------ */

#ifndef CSV_DATA_LOADER_H
#define CSV_DATA_LOADER_H

#include "AbstractDataFetcher.h"

class CSVDataLoader : public AbstractDataFetcher
{
public:
    CSVDataLoader();
    CSVDataLoader(DataSource& source, std::string& location);
    virtual ~CSVDataLoader() {};

    std::string LoadData() override;
    bool ValidateData(const std::string& data_str) override;
    std::string ParseCSVData(const std::string& data_str);

private:
    DataSource source;
    std::string location;
};

#endif // CSV_DATA_LOADER_H
