#ifndef CRIME_DATA_ANALYZER_HPP
#define CRIME_DATA_ANALYZER_HPP

#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <iostream>

#include "Data.h"
#include "DataLoaderInterface.h"


class CrimeDataAnalyzer
{
public:
    CrimeDataAnalyzer(const DataConfig& config);
    ~CrimeDataAnalyzer();

    bool LoadAllData();

    std::map<std::string, int> GetCrimesByType() const;
    std::map<std::string, int> GetCrimesByNeighborhoodCluster() const;
    std::map<std::string, int> GetCrimesByVotingPrecinct() const;
    std::map<std::string, int> GetCrimesByDistrict() const;
    double CalculateClearanceRate() const;
    std::vector<DataFeature> FindCrimesInRadius(double center_lat, double center_lon, double radius_km) const;
 
    const DataCollection* GetCollection() const
    {
        return &collection_;
    }

    Data& GetCrimeDataPtr()
    {
        return *crimeDataPtr_;
    }

private:
    double CalculateDistance(double lat1, double lon1, double lat2, double lon2) const;

    void ParseDateTime(const std::string& date);

private:
    std::unique_ptr<DataCollection> crime_data_;
    DataConfig config_;
    DataCollection collection_;
    std::unique_ptr<Data> crimeDataPtr_;
};

#endif // CRIME_DATA_ANALYZER_HPP
