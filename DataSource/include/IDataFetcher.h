#ifndef I_DATA_FETCHER_H
#define I_DATA_FETCHER_H

#include <string>

class IDataFetcher {
public:
    virtual ~IDataFetcher() = default;
    
    /**
     * Fetches data from the source
     * The source identifier (file path or URL)
     */
    virtual std::string fetchData(const std::string& source) = 0;
    
    /**
     * Checks if this fetcher can handle the given source
     */
    virtual bool canHandle(const std::string& source) const = 0;
};

#endif //I_DATA_FETCHER_H