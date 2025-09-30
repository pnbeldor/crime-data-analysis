#ifndef CRIME_DATA_ANALYZER_HPP
#define CRIME_DATA_ANALYZER_HPP

#include "Data.h"
#include "DataLoaderInterface.h"


class CrimeDataAnalyzer
{
public:
    CrimeDataAnalyzer(const DataConfig& config);
    ~CrimeDataAnalyzer();

    bool LoadAllData();

    DataCollection* getCollection()
    {
        return &collection_;
    }

private:
    std::unique_ptr<DataCollection> crime_data_;
    DataConfig config_;
    DataCollection collection_;

};

#endif // CRIME_DATA_ANALYZER_HPP
