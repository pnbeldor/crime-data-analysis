/* --- URLDataLoader.h --- */

/* ------------------------------------------
Author: Pnbeldor
Date: 9/24/2025
------------------------------------------ */

#ifndef DATA_SOURCE_URL_DATA_LOADER_H
#define DATA_SOURCE_URL_DATA_LOADER_H

#include "IDataFetcher.h"

class URLDataLoader : public IDataFetcher {
public:
    URLDataLoader();
    virtual ~URLDataLoader();
    
    std::string FetchData() override;
    bool canHandle(const std::string& source) const override;
    
private:
    std::string downloadUrl(const std::string& url);

};

#endif // DATA_SOURCE_URL_DATA_LOADER_H