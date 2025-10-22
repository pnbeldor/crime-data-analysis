
#ifndef DATA_LOADER_FACTORY_H
#define DATA_LOADER_FACTORY_H

#include <memory>
#include <vector>

#include "DataLoaderInterface.h"

class DataLoaderFactory
{
public:
    virtual ~DataLoaderFactory(){};

    std::unique_ptr<DataLoaderInterface> CreateDataLoader(DataConfig& config);

    void RegisterLoader(std::unique_ptr<DataLoaderInterface> loader)
    {
        loaders_.push_back(std::move(loader));
    }

private:
    std::vector<std::unique_ptr<DataLoaderInterface>> loaders_;

};

#endif // DATA_LOADER_FACTORY_H
