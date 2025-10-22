

#include "JsonDataLoader.h"

#include <iostream>
#include <cmath>

#include "LocalFileDataLoader.h"
#include "URLDataLoader.h"
#include "DataConfig.h"

JsonDataLoader::JsonDataLoader()
{
}

JsonDataLoader::JsonDataLoader(const DataSource& source,
                               const std::string& location)
    : AbstractDataFetcher(source, location)
{
}

bool JsonDataLoader::ValidateData([[maybe_unused]] const std::string& data_str)
{
    return true;
}

void JsonDataLoader::SetDataCollection([[maybe_unused]]const std::string& dataStr)
{
    this->getDataPtr()->SetDataCollection(dataStr, DataFormat::JSON);
}
