#include "crime_analyzer.h"

#include <algorithm>
#include <cmath>
#include <curl/curl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <json/json.h>
#include <sstream>
#include <iomanip>
#include <iostream>

namespace crime_analysis {

// CURL write callback for HTTP responses
[[maybe_unused]] static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

CrimeAnalyzer::CrimeAnalyzer() {
    //curl_global_init(CURL_GLOBAL_DEFAULT);
}

CrimeAnalyzer::~CrimeAnalyzer() {
    //curl_global_cleanup();
}

bool CrimeAnalyzer::loadFromJson(const std::string& json_file) {
    std::ifstream file(json_file);
    if (!file.is_open()) {
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return false;
    //return parseJsonData(buffer.str());
}

bool CrimeAnalyzer::loadFromUrl([[maybe_unused]]const std::string& url) {
    // CURL* curl = curl_easy_init();
    // std::string response;
    
    // if (curl) {
    //     curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    //     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    //     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    //     curl_easy_setopt(curl, CURLOPT_USERAGENT, "CrimeAnalyzer/1.0");
        
    //     CURLcode res = curl_easy_perform(curl);
    //     curl_easy_cleanup(curl);
        
    //     if (res == CURLE_OK) {
    //         return parseJsonData(response);
    //     }
    // }
    
    return false;
}

bool CrimeAnalyzer::loadFromCsv(const std::string& csv_file) {
    std::ifstream file(csv_file);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    // Skip header
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        parseCsvRecord(line);
    }
    
    return true;
}

bool CrimeAnalyzer::parseJsonData(const std::string& json_data) {
    Json::CharReaderBuilder readerBuilder;
    Json::Value root;
    std::string errors;
    
    std::istringstream json_stream(json_data);
    if (!Json::parseFromStream(readerBuilder, json_stream, &root, &errors)) {
        std::cerr << "JSON parse error: " << errors << std::endl;
        return false;
    }
    
    if (root.isArray()) {
        for (const auto& item : root) {
            CrimeRecord record;
            if (parseJsonRecord(item, record)) {
                crime_records_.push_back(record);
            }
        }
    } else if (root.isObject() && root.isMember("features")) {
        // GeoJSON format support
        for (const auto& feature : root["features"]) {
            CrimeRecord record;
            if (parseGeoJsonRecord(feature, record)) {
                crime_records_.push_back(record);
            }
        }
    }
    
    return true;
}

bool CrimeAnalyzer::parseJsonRecord(const Json::Value& json, CrimeRecord& record) {
    try {
        if (json.isMember("crime_id")) record.crime_id = json["crime_id"].asString();
        if (json.isMember("crime_type")) record.crime_type = json["crime_type"].asString();
        if (json.isMember("neighborhood")) record.neighborhood = json["neighborhood"].asString();
        if (json.isMember("precinct")) record.precinct = json["precinct"].asString();
        if (json.isMember("weapon_used")) record.weapon_used = json["weapon_used"].asString();
        
        if (json.isMember("arrest_made")) {
            record.arrest_made = json["arrest_made"].asBool();
        }
        
        if (json.isMember("latitude") && json.isMember("longitude")) {
            record.latitude = json["latitude"].asDouble();
            record.longitude = json["longitude"].asDouble();
        }
        
        if (json.isMember("reported_date")) {
            std::tm tm = {};
            std::istringstream ss(json["reported_date"].asString());
            ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
            record.reported_date = std::chrono::system_clock::from_time_t(std::mktime(&tm));
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON record: " << e.what() << std::endl;
        return false;
    }
}

bool CrimeAnalyzer::parseGeoJsonRecord(const Json::Value& feature, CrimeRecord& record) {
    try {
        const auto& properties = feature["properties"];
        const auto& geometry = feature["geometry"];
        
        if (properties.isMember("crime_type")) record.crime_type = properties["crime_type"].asString();
        if (properties.isMember("neighborhood")) record.neighborhood = properties["neighborhood"].asString();
        
        if (geometry.isMember("coordinates") && geometry["coordinates"].isArray()) {
            const auto& coords = geometry["coordinates"];
            if (coords.size() >= 2) {
                record.longitude = coords[0].asDouble();
                record.latitude = coords[1].asDouble();
            }
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing GeoJSON record: " << e.what() << std::endl;
        return false;
    }
}

std::string CrimeAnalyzer::exportToJson() const {
    Json::Value root(Json::arrayValue);
    
    for (const auto& record : crime_records_) {
        Json::Value json_record;
        json_record["crime_id"] = record.crime_id;
        json_record["crime_type"] = record.crime_type;
        json_record["neighborhood"] = record.neighborhood;
        json_record["precinct"] = record.precinct;
        json_record["weapon_used"] = record.weapon_used;
        json_record["arrest_made"] = record.arrest_made;
        json_record["latitude"] = record.latitude;
        json_record["longitude"] = record.longitude;
        
        auto time_t = std::chrono::system_clock::to_time_t(record.reported_date);
        std::tm* tm = std::localtime(&time_t);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);
        json_record["reported_date"] = buffer;
        
        root.append(json_record);
    }
    
    Json::StreamWriterBuilder writer;
    writer["indentation"] = "  ";
    return Json::writeString(writer, root);
}

void CrimeAnalyzer::addCrimeRecord(const CrimeRecord& record) {
    crime_records_.push_back(record);
}

std::map<std::string, int> CrimeAnalyzer::getCrimesByType() const {
    std::map<std::string, int> result;
    for (const auto& record : crime_records_) {
        result[record.crime_type]++;
    }
    return result;
}

std::map<std::string, int> CrimeAnalyzer::getCrimesByNeighborhood() const {
    std::map<std::string, int> result;
    for (const auto& record : crime_records_) {
        if (!record.neighborhood.empty()) {
            result[record.neighborhood]++;
        }
    }
    return result;
}

std::map<int, int> CrimeAnalyzer::getCrimesByHour() const {
    std::map<int, int> result;
    for (const auto& record : crime_records_) {
        auto time_t = std::chrono::system_clock::to_time_t(record.reported_date);
        std::tm* tm = std::localtime(&time_t);
        result[tm->tm_hour]++;
    }
    return result;
}

std::map<int, int> CrimeAnalyzer::getCrimesByMonth() const {
    std::map<int, int> result;
    for (const auto& record : crime_records_) {
        auto time_t = std::chrono::system_clock::to_time_t(record.reported_date);
        std::tm* tm = std::localtime(&time_t);
        result[tm->tm_mon + 1]++; // tm_mon is 0-11
    }
    return result;
}

double CrimeAnalyzer::calculateClearanceRate() const {
    if (crime_records_.empty()) return 0.0;
    
    int arrests = 0;
    for (const auto& record : crime_records_) {
        if (record.arrest_made) arrests++;
    }
    
    return static_cast<double>(arrests) / crime_records_.size();
}

std::vector<CrimeRecord> CrimeAnalyzer::findCrimesInRadius(double center_lat, double center_lon, double radius_km) const {
    std::vector<CrimeRecord> result;
    
    for (const auto& record : crime_records_) {
        double distance = calculateDistance(center_lat, center_lon, record.latitude, record.longitude);
        if (distance <= radius_km) {
            result.push_back(record);
        }
    }
    
    return result;
}

double CrimeAnalyzer::getAverageCrimesPerDay() const {
    if (crime_records_.empty()) return 0.0;
    
    // Find date range
    auto min_date = std::min_element(crime_records_.begin(), crime_records_.end(),
        [](const CrimeRecord& a, const CrimeRecord& b) {
            return a.reported_date < b.reported_date;
        });
    
    auto max_date = std::max_element(crime_records_.begin(), crime_records_.end(),
        [](const CrimeRecord& a, const CrimeRecord& b) {
            return a.reported_date < b.reported_date;
        });
    
    auto duration = max_date->reported_date - min_date->reported_date;
    auto days = std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24.0;
    
    if (days <= 0) return crime_records_.size();
    
    return crime_records_.size() / days;
}

double CrimeAnalyzer::calculateDistance(double lat1, double lon1, double lat2, double lon2) const {
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

// bool CrimeAnalyzer::parseJsonRecord(const std::string& json_str) {
//     // Simplified JSON parsing - in real implementation use a proper JSON library
//     // This is a placeholder implementation
//     CrimeRecord record;
//     // Actual implementation would use nlohmann/json or similar
//     crime_records_.push_back(record);

//     return true;
// }

void CrimeAnalyzer::parseCsvRecord(const std::string& csv_line) {
    std::istringstream ss(csv_line);
    std::string token;
    CrimeRecord record;
    int field_index = 0;
    std::istringstream ds(token);
    // Parse date - simplified
    std::tm tm = {};
    //std::istringstream ds(token);

    while (std::getline(ss, token, ',')) {
        switch (field_index) {
            case 0: record.crime_id = token; break;
            case 1: record.crime_type = token; break;
            case 2: 
                ds >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
                record.reported_date = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                break;
            case 3: record.latitude = std::stod(token); break;
            case 4: record.longitude = std::stod(token); break;
            case 5: record.neighborhood = token; break;
            case 6: record.precinct = token; break;
            case 7: record.arrest_made = (token == "true" || token == "1"); break;
            case 8: record.weapon_used = token; break;
        }
        field_index++;
    }
    
    if (field_index >= 5) { // Basic validation
        crime_records_.push_back(record);
    }
}
}