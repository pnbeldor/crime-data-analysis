/* --- DataLoaderInterface.h --- */

/* ------------------------------------------
Author: Pierre Nicolson Beldor
Date: 9/24/2025
------------------------------------------ */

#ifndef DATA_LOADER_INTERFACE_H
#define DATA_LOADER_INTERFACE_H

#include <map>
#include <string>


enum class DataFormat {
    JSON,
    CSV
};

enum class DataSource {
    LOCAL_FILE,
    HTTP_REQUEST
};

struct DataConfig {
    DataSource source;
    DataFormat format;
    std::string location; // file path or URL
    std::map<std::string, std::string> options;
};

/*
Data loader factory interface
*/
class DataLoaderInterface {
public:
    virtual ~DataLoaderInterface() {};

    //virtual void LoadData(DataSource& source, std::string& location, std::string& dataValue) = 0;
    virtual std::string LoadData() = 0;
    virtual bool ValidateData(const std::string& data_str) = 0;
    virtual void SetDataCollection(const std::string& dataStr) = 0;
private:

};

#endif // DATA_LOADER_INTERFACE_H
