#ifndef CRIME_DATA_ANALYZER_HPP
#define CRIME_DATA_ANALYZER_HPP

#include <algorithm>
#include <cmath>
#include <vector>

#include "Data.h"
#include "DataLoaderInterface.h"


class CrimeDataAnalyzer
{
public:
    CrimeDataAnalyzer(const DataConfig& config);
    ~CrimeDataAnalyzer();

    std::map<std::string, int> GetCrimesByType() const;
    std::map<std::string, int> GetCrimesByNeighborhoodCluster() const;
    std::map<std::string, int> GetCrimesByVotingPrecinct() const;
    std::map<std::string, int> GetCrimesByDistrict() const;
    double CalculateClearanceRate() const;
    std::vector<DataFeature> FindCrimesInRadius(double center_lat, double center_lon, double radius_km) const;
 
    void PrintCollection() const;

    Data& GetCrimeDataPtr()
    {
        return *crimeDataPtr_;
    }

private:
    bool LoadAllData();
    double CalculateDistance(const double lat1, const double lon1, const double lat2, const double lon2) const;

    void ParseDateTime(const std::string& date);

private:
    std::unique_ptr<DataCollection> crime_data_;
    DataConfig config_;
    std::unique_ptr<Data> crimeDataPtr_;
};

#endif // CRIME_DATA_ANALYZER_HPP
