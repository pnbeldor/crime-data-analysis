#pragma once

#include "Data.h"
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <json/json.h>

namespace crime_analysis {

struct CrimeRecord {
    std::string crime_id;
    std::string crime_type;
    std::chrono::system_clock::time_point reported_date;
    double latitude;
    double longitude;
    std::string neighborhood;
    std::string precinct;
    bool arrest_made;
    std::string weapon_used;
};

class CrimeAnalyzer {
public:
    CrimeAnalyzer();
    virtual ~CrimeAnalyzer(); // = default;

    // Data ingestion
    bool loadFromJson(const std::string& json_file);
    bool loadFromCsv(const std::string& csv_file);
    void addCrimeRecord(const CrimeRecord& record);
    bool loadFromUrl(const std::string& url);

    // Analysis methods
    std::map<std::string, int> getCrimesByType() const;
    std::map<std::string, int> getCrimesByNeighborhood() const;
    std::map<int, int> getCrimesByHour() const;
    std::map<int, int> getCrimesByMonth() const;
    
    double calculateClearanceRate() const;
    std::vector<CrimeRecord> findCrimesInRadius(double center_lat, double center_lon, double radius_km) const;
    
    // Statistical methods
    double getAverageCrimesPerDay() const;
    std::map<std::string, double> getCrimeRatesByArea() const;

    // Utility methods
    size_t getTotalRecords() const { return crime_records_.size(); }
    void clearData() { crime_records_.clear(); }

private:
    std::vector<CrimeRecord> crime_records_;
    std::unique_ptr<DataCollection> crime_data_;
    
    bool parseGeoJsonRecord(const Json::Value& feature, CrimeRecord& record);
    double calculateDistance(double lat1, double lon1, double lat2, double lon2) const;
    bool parseJsonRecord(const Json::Value& json, CrimeRecord& record);
    bool parseJsonData(const std::string& json_str);
    std::string exportToJson() const;

    void parseCsvRecord(const std::string& csv_line);
};

} // namespace crime_analysis