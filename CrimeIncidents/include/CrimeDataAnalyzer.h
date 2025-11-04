#ifndef CRIME_DATA_ANALYZER_HPP
#define CRIME_DATA_ANALYZER_HPP

#include <algorithm>
#include <cmath>
#include <optional>
#include <vector>

#include "Data.h"
#include "DataLoaderInterface.h"

class CrimeDataAnalyzer
{
public:
    CrimeDataAnalyzer(const DataConfig& config);
    ~CrimeDataAnalyzer();

    std::optional<std::map<std::string, int>> GetCrimesCountBy(std::string keyStr) const;

    double CalculateClearanceRate() const;
    std::vector<DataFeature> FindCrimesInRadius(double center_lat, double center_lon, double radius_km) const;
    size_t FindCrimesInRadius2(double center_lat, double center_lon, const  double radiusKm) const;

    void PrintCollection() const;

    Data& GetCrimeDataPtr()
    {
        return *crimeDataPtr;
    }

private:
    bool LoadAllData();
    double CalculateDistance(const double lat1, const double lon1, const double lat2, const double lon2) const;

    void ParseDateTime(const std::string& date);

private:
    std::unique_ptr<DataCollection> crime_data_;
    std::unique_ptr<Data> crimeDataPtr;
    DataConfig coonfig;
    bool IsDataLoaded;
};

#endif // CRIME_DATA_ANALYZER_HPP
