
#include "CrimeDataAnalyzer.h"
#include "Data.h"
#include "DataLoaderFactory.h"

CrimeDataAnalyzer::CrimeDataAnalyzer(const DataConfig& config) :
                                     config_(config)
{
    [[maybe_unused]] bool isValidData = LoadAllData();

}

CrimeDataAnalyzer::~CrimeDataAnalyzer()
{

}

bool CrimeDataAnalyzer::LoadAllData()
{
    DataLoaderFactory factory;
    bool isValid = false;

    auto dataLoader  = factory.CreateDataLoader(this->config_);
    std::string data_str = dataLoader->LoadData();
    
    if (dataLoader->ValidateData(data_str)) {
        isValid = true;
        Data data;

        collection_ = data.setDataCollection(data_str);
    }

    return isValid;
}