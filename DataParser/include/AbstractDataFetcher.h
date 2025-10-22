/* --- AbstractDataFetcher.h --- */

/* ------------------------------------------
Author: Pierre Nicolson Beldor
Date: 9/26/2025
------------------------------------------ */

#ifndef ABSTRACT_DATA_FETCHER_H
#define ABSTRACT_DATA_FETCHER_H

#include <vector>

#include "Data.h"
#include "DataLoaderInterface.h"

class AbstractDataFetcher : public DataLoaderInterface {
public:
    AbstractDataFetcher();
    AbstractDataFetcher(const DataSource& source, const std::string& location);
    virtual ~AbstractDataFetcher() {}

    std::string LoadData() override;

    std::string formatToString(DataFormat format);
    std::string sourceToString(DataSource source);
    std::vector<std::string> splitString(const std::string& str, char delimiter);
    std::string trim(const std::string& str);

    const DataSource& GetSource()
    {
        return source;
    }

    const std::string& GetLocation()
    {
        return location;
    }

    Data* getDataPtr()
    {
        return data_.get();
    }

private:
    DataSource source;
    std::string location;
    std::unique_ptr<Data> data_;
};

#endif // ABSTRACT_DATA_FETCHER_H
