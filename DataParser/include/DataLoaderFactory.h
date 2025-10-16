
#ifndef DATA_LOADER_FACTORY_HPP
#define DATA_LOADER_FACTORY_HPP

#include "DataLoaderInterface.h"

#include <memory>
#include <vector>

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

private:
    std::vector<std::unique_ptr<DataLoaderInterface>> loaders_;
//    std::unique_ptr<Data> data_;

};

#endif // DATALOADERFACTORY_HPP
