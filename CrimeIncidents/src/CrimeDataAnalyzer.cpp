
#include "CrimeDataAnalyzer.h"

#include <iostream>

#include "Data.h"
#include "AbstractDataFetcher.h"
#include "DataLoaderFactory.h"
#include "JsonDataLoader.h"

CrimeDataAnalyzer::CrimeDataAnalyzer(const DataConfig& config) :
                                     config_(config)
{
    crimeDataPtr_ = std::make_unique<Data>();
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
    
    if (dataLoader->ValidateData(data_str))
    {
        isValid = true;

        crimeDataPtr_->SetDataCollection(data_str);
    }

    return isValid;
}

std::map<std::string, int> CrimeDataAnalyzer::GetCrimesByType() const 
{
    std::map<std::string, int> result;

     const DataCollection& collection = crimeDataPtr_->GetCollectionPtr();

    for (const auto& record : (*collection.features))
    {
        result[record.properties_ptr->offense]++;
    }
    
    for (const auto& value : result)
    {
        std::cout << value.first << ": " << value.second << "\n";
    }

    return result;
}

std::map<std::string, int> CrimeDataAnalyzer::GetCrimesByNeighborhoodCluster() const
{
    std::map<std::string, int> result;
    const DataCollection& collection = crimeDataPtr_->GetCollectionPtr();

    for (const auto& record : (*collection.features))
    {
        if (!record.properties_ptr->neighborHood_cluster.empty())
        {
            result[record.properties_ptr->neighborHood_cluster]++;
        }
    }

    for (const auto& value : result)
    {
        std::cout << value.first << ": " << value.second << "\n";
    }
    return result;
}

std::map<std::string, int> CrimeDataAnalyzer::GetCrimesByVotingPrecinct() const
{
    std::map<std::string, int> result;
    const DataCollection& collection = crimeDataPtr_->GetCollectionPtr();

    for (const auto& record : (*collection.features))
    {
        if (!record.properties_ptr->voting_precinct.empty())
        {
            result[record.properties_ptr->voting_precinct]++;
        }
    }

    for (const auto& value : result)
    {
        std::cout << value.first << ": " << value.second << "\n";
    }

    return result;
}

std::map<std::string, int> CrimeDataAnalyzer::GetCrimesByDistrict() const
{
    std::map<std::string, int> result;
    const DataCollection& collection = crimeDataPtr_->GetCollectionPtr();

    for (const auto& record : (*collection.features)) {
        if (!record.properties_ptr->district.empty()) {
            result[record.properties_ptr->district]++;
        }
    }

    for (const auto& value : result)
    {
        std::cout << value.first << ": " << value.second << "\n";
    }

    return result;
}

std::vector<DataFeature> CrimeDataAnalyzer::FindCrimesInRadius(double center_lat, double center_lon, double radius_km) const 
{
    std::vector<DataFeature> result;
    const DataCollection& collection = crimeDataPtr_->GetCollectionPtr();

    for (const auto& record : (*collection.features))
    {
        double distance = CalculateDistance(center_lat, center_lon, record.properties_ptr->latitude, record.properties_ptr->longitude);
        
        if (distance <= radius_km)
        {
            result.push_back(record);
        }
    }
    
    std::cout << "The number of crime within " << radius_km  << " kilometers is: " << result.size()  <<"\n\n";

    return result;
}

double CrimeDataAnalyzer::CalculateDistance(double lat1, double lon1, double lat2, double lon2) const
{
    // Haversine formula
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    
    lat1 = lat1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;
    
    double a = std::sin(dLat/2) * std::sin(dLat/2) +
               std::sin(dLon/2) * std::sin(dLon/2) * std::cos(lat1) * std::cos(lat2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1-a));
    
    return 6371.0 * c; // Earth radius in km
}

