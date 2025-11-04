/*
    Crime Prediction Dashboard: Forecast crime hotspots for resource allocation

    Seasonal Pattern Analysis: Identify recurring patterns for preventive measures

    Clearance Rate Optimization: Analyze factors affecting arrest rates

    Community Safety App: Real-time crime mapping and alerts

    Policy Impact Analysis: Measure effect of interventions on crime rates
*/

#include <iostream>

#include "DataFetchConfig.h"

#include "CrimeDataAnalyzer.h"
#include "JsonDataLoader.h"
#include "URLDataLoader.h"
#include "DataLoaderFactory.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    DataConfig config;
    config.source = DataSource::LOCAL_FILE;
    config.format = DataFormat::JSON;

    config.location = "/home/pnbeldor/Downloads/Crime_Incidents_in_the_Last_30_Days.geojson";
    
    //config.format = DataFormat::CSV;
    //config.location = "/home/pnbeldor/Downloads/Crime_Incidents_in_the_Last_30_Days.csv";
    //config.location = "/home/pnbeldor/Downloads/Motor_Vehicle_Collisions_-_Crashes.json";
    //config.location = "/home/pnbeldor/Downloads/Chicago_Public_Schools_-_School_Progress_Reports_SY2324.csv";
    //config.location = "/home/pnbeldor/Downloads/Chicago_Public_Schools_-_School_Progress_Reports_SY2324.json";
    CrimeDataAnalyzer crimeDataAnalyzer(config);

    //crimeDataAnalyzer.PrintCollection();

    std::string keyStr;
    std::cout << " =================== Crime By Type ==================\n\n";
    keyStr = "OFFENSE";
    auto resultByType = crimeDataAnalyzer.GetCrimesCountBy(keyStr);

    for (const auto& value : *resultByType)
    {
        std::cout << value.first << ": " << value.second << "\n";
    }

    std::cout << " ================= Crime by Neighborhood cluster ====================\n\n";
    keyStr = "NEIGHBORHOOD_CLUSTER";
    auto resultByNeighborhood = crimeDataAnalyzer.GetCrimesCountBy(keyStr);

    for (const auto& value : *resultByNeighborhood)
    {
        std::cout << value.first << ": " << value.second << "\n";
    }

    std::cout << " =============== Crime by District ======================\n\n";
    keyStr = "DISTRICT";
    if (auto resultByDistrict = crimeDataAnalyzer.GetCrimesCountBy(keyStr))
    {
        for (const auto& value : *resultByDistrict)
        {
            std::cout << value.first << ": " << value.second << "\n";
        }
    }
    else
    {
        std::cerr << "Error: Key \"" << keyStr << "\" not found: ";
    }

    std::cout << " =============== Crime by voting precinct ======================\n\n";
    keyStr = "VOTING_PRECINCT";
    if (auto resultByVotingPrecinct  = crimeDataAnalyzer.GetCrimesCountBy(keyStr))
    {
        for (const auto& value : *resultByVotingPrecinct)
        {
            std::cout << value.first << ": " << value.second << "\n";
        }
    }
    else
    {
        std::cerr << "Error: Key \"" << keyStr << "\" not found: ";
    }

    std::cout << " =============== Crime within a radius ======================\n\n";

    const auto radius_km = 5;
    auto result = crimeDataAnalyzer.FindCrimesInRadius(38.8439, -76.9780, radius_km);

    std::cout << "The number of crime within " << radius_km  << " kilometers is: " << result.size()  <<"\n\n";

    return 0;
}