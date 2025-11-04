
#include "CrimeDataAnalyzer.h"

#include <cassert>
#include <iostream>

#include "DataLoaderFactory.h"

CrimeDataAnalyzer::CrimeDataAnalyzer(const DataConfig& config)
                                     : coonfig(config), IsDataLoaded(false)
{
    crimeDataPtr = std::make_unique<Data>();
    [[maybe_unused]] bool isValidData = LoadAllData();
}

CrimeDataAnalyzer::~CrimeDataAnalyzer()
{
}

bool CrimeDataAnalyzer::LoadAllData()
{
    DataLoaderFactory factory;
    bool isValid = false;

    auto dataLoader  = factory.CreateDataLoader(this->coonfig);
    std::string dataStr = dataLoader->LoadData();
    
    if (dataLoader->ValidateData(dataStr))
    {
        isValid = true;
        crimeDataPtr->SetDataCollection(dataStr, this->coonfig.format);
        IsDataLoaded = true;
    }

    return isValid;
}

std::optional<std::map<std::string, int>> CrimeDataAnalyzer::GetCrimesCountBy(std::string keyStr) const 
{
    std::map<std::string, int> result;

    auto mapPtr = crimeDataPtr->GetDataFeatureMapPtr();

   //if ((*mapPtr).find(keyStr) != (*mapPtr).end())
    if ((*mapPtr).contains(keyStr))
    {

        auto crimeVec = mapPtr->at(keyStr);

        for (const auto& record : crimeVec)
        {
            result[record]++;
        }

        return result;
    }

    return std::nullopt;

    // try {
    //     auto crimeVec = mapPtr->at(keyStr);

    //     for (const auto& record : crimeVec)
    //     {
    //         result[record]++;
    //     }
    // } catch (const std::out_of_range& error)
    // {
    //     std::cerr << "Error: Key \"" << keyStr << "\" not found: " << error.what() << "\n";
    // }

    // return result;
}

/*
std::map<std::string, int> CrimeDataAnalyzer::GetCrimesCountBy(std::string keyStr) const 
{
    std::map<std::string, int> result;

    auto mapPtr = crimeDataPtr->GetDataFeatureMapPtr();

//    //if ((*mapPtr).find(keyStr) != (*mapPtr).end())
//     if ((*mapPtr).contains(keyStr))
//     {

//         auto crimeVec = mapPtr->at(keyStr);

//         for (const auto& record : crimeVec)
//         {
//             result[record]++;
//         }
//     }

    try {
        auto crimeVec = mapPtr->at(keyStr);

        for (const auto& record : crimeVec)
        {
            result[record]++;
        }
    } catch (const std::out_of_range& error)
    {
        std::cerr << "Error: Key \"" << keyStr << "\" not found: " << error.what() << "\n";
    }

    return result;
}
*/
/*
size_t CrimeDataAnalyzer::FindCrimesInRadius2(double centerLat, double centerLon, const  double radiusKm) const
{
    auto mapPtr = crimeDataPtr->GetDataFeatureMapPtr();
    size_t count = 0;

    const auto& latitude = (*mapPtr).at("LATITUDE");
    const auto& longitude = (*mapPtr).at("LONGITUDE");

    assert(latitude.size() == longitude.size() && "Longitude and Latitude size are not equal");

    for (size_t i = 0; i < latitude.size(); i++)
    {
        auto lat = std::stod(latitude[i]);
        auto lon = std::stod(longitude[i]);
        double distance = CalculateDistance(centerLat, centerLon, lat, lon);

        if (distance <= radiusKm)
            count++;
    }

    return count;
}
*/
size_t CrimeDataAnalyzer::FindCrimesInRadius2(double centerLat, double centerLon, const  double radiusKm) const
{
    auto mapPtr = crimeDataPtr->GetDataFeatureMapPtr();
    size_t count = 0;

    const auto& latitude = (*mapPtr).at("LATITUDE");
    const auto& longitude = (*mapPtr).at("LONGITUDE");

    assert(latitude.size() == longitude.size() && "Longitude and Latitude size are not equal");

    for (size_t i = 0; i < latitude.size(); i++)
    {
        auto lat = std::stod(latitude[i]);
        auto lon = std::stod(longitude[i]);
        double distance = CalculateDistance(centerLat, centerLon, lat, lon);

        if (distance <= radiusKm)
            count++;
    }

    return count;
}

std::vector<DataFeature> CrimeDataAnalyzer::FindCrimesInRadius(double centerLat, double centerLon, const  double radiusKm) const
{
    std::vector<DataFeature> result;
    const DataCollection& collection = crimeDataPtr->GetCollectionPtr();

    for (const auto& record : (*collection.features))
    {
        double distance = CalculateDistance(centerLat, centerLon, record.properties_ptr->latitude, record.properties_ptr->longitude);
        
        if (distance <= radiusKm)
        {
            result.push_back(record);
        }
    }
    
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

void CrimeDataAnalyzer::PrintCollection() const
{
    std::cout << "Type = " << crimeDataPtr->GetDataCollection()->type <<"\n";
    std::cout << "Name = " << crimeDataPtr->GetDataCollection()->name << "\n";
    std::cout << "crs type = " << crimeDataPtr->GetDataCollection()->crs_type <<"\n";
    std::cout << "CRS Properties Name = " << crimeDataPtr->GetDataCollection()->crs_property_name << "\n";

    for (const auto& feature : (*(crimeDataPtr->GetDataCollection())->features))
    {
        crimeDataPtr->printFeature(feature);
    }
}
