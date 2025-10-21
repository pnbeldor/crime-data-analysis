

#include "DataLoaderFactory.h"

#include "AbstractDataFetcher.h"
#include "JsonDataLoader.h"
#include "CSVDataLoader.h"

/*
* Create a specific type of loader according tho the format
*/
std::unique_ptr<DataLoaderInterface> DataLoaderFactory::CreateDataLoader(DataConfig& config)
{
    switch (config.format)
    {
        case DataFormat::JSON:
            return std::make_unique<JsonDataLoader>(config.source, config.location);
        case DataFormat::CSV:
            return std::make_unique<CSVDataLoader>(config.source, config.location);
        default:
            return nullptr;
    }
}
