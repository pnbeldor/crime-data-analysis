/* --- AbstractDataFetcher.h --- */

/* ------------------------------------------
Author: Pierre Nicolson Beldor
Date: 9/26/2025
------------------------------------------ */

#ifndef ABSTRACT_DATA_FETCHER_HPP
#define ABSTRACT_DATA_FETCHER_HPP

#include <vector>

#include "DataLoaderInterface.h"

class AbstractDataFetcher : public DataLoaderInterface {
public:
    AbstractDataFetcher();
    virtual ~AbstractDataFetcher() {}

    //virtual void LoadData(DataSource& source, std::string& location, std::string& dataValue) override;
    //virtual std::string LoadData() ;
    std::string formatToString(DataFormat format);
    std::string sourceToString(DataSource source);
    std::vector<std::string> splitString(const std::string& str, char delimiter);
    std::string trim(const std::string& str);

private:

};

#endif // ABSTRACT_DATA_FETCHER_HPP
