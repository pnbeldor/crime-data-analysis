/* --- DataLoaderInterface.h --- */

/* ------------------------------------------
Author: Pierre Nicolson Beldor
Date: 9/24/2025
------------------------------------------ */

#ifndef DATA_LOADER_INTERFACE_H
#define DATA_LOADER_INTERFACE_H

#include "DataConfig.h"

/*
Data loader factory interface
*/
class DataLoaderInterface {
public:
    virtual ~DataLoaderInterface() {};

    virtual std::string LoadData() = 0;
    virtual bool ValidateData(const std::string& data_str) = 0;
    virtual void SetDataCollection(const std::string& dataStr) = 0;
private:

};

#endif // DATA_LOADER_INTERFACE_H
