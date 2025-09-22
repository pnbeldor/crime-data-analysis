#include "CrimeIncidents.h"


 CrimeIncidents:: CrimeIncidents(std::string file_name) : file_path(file_name)
{
    file_stream.open(file_path, std::ios::binary);

    Json::CharReaderBuilder readerBuilder;
    std::string errs;

    //Json::Value data_;

    if (Json::parseFromStream(readerBuilder, file_stream, &data, &errs))
    {
        std::cout << "JSon string parse successfully!\n";
    }
    else
    {
        data = Json::nullValue;
        std::cout << "Error passing JSON: " << errs << "\n";
    }
}

 CrimeIncidents::~ CrimeIncidents()
{
    if (file_stream.is_open())
    {
        file_stream.close();
    }

    // if (data != nullptr)
    // {
    //     delete data;
    //     data = nullptr;
    // }
}

void  CrimeIncidents::SetCollection()
{
    Data collectionData;
    collection = std::make_unique<DataCollection>(collectionData.setDataCollection(data));
}


