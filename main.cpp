/*
    Crime Prediction Dashboard: Forecast crime hotspots for resource allocation

    Seasonal Pattern Analysis: Identify recurring patterns for preventive measures

    Clearance Rate Optimization: Analyze factors affecting arrest rates

    Community Safety App: Real-time crime mapping and alerts

    Policy Impact Analysis: Measure effect of interventions on crime rates
*/

#include <iostream>

#include "CrimeDataAnalyzer.h"
#include "JsonDataLoader.h"
#include "URLDataLoader.h"
#include "DataLoaderFactory.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    DataConfig config;
    config.source = DataSource::LOCAL_FILE;
    //config.format = DataFormat::JSON;
    //const std::string file_path = "/home/pnbeldor/Downloads/Crime_Incidents_in_the_Last_30_Days.geojson";

    //config.location = "/home/pnbeldor/Downloads/Crime_Incidents_in_the_Last_30_Days.geojson";
    
    config.format = DataFormat::CSV;
    config.location = "/home/pnbeldor/Downloads/Crime_Incidents_in_the_Last_30_Days.csv";

    CrimeDataAnalyzer crimeDataAnalyzer(config);

    //crimeDataAnalyzer.PrintCollection();

    std::cout << " =================== Crime By Type ==================\n\n";
    auto resultByType = crimeDataAnalyzer.GetCrimesByType();

    for (const auto& value : resultByType)
    {
        std::cout << value.first << ": " << value.second << "\n";
    }

    std::cout << " ================= Crime by Neighborhood cluster ====================\n\n";
    auto resultByNeighborhood = crimeDataAnalyzer.GetCrimesByNeighborhoodCluster();

    for (const auto& value : resultByNeighborhood)
    {
        std::cout << value.first << ": " << value.second << "\n";
    }

    std::cout << " =============== Crime by District ======================\n\n";
    auto resultByDistrict = crimeDataAnalyzer.GetCrimesByDistrict();

    for (const auto& value : resultByDistrict)
    {
        std::cout << value.first << ": " << value.second << "\n";
    }

    std::cout << " =============== Crime by voting precinct ======================\n\n";
    auto resultByVotingPrecinct  = crimeDataAnalyzer.GetCrimesByVotingPrecinct();

    for (const auto& value : resultByVotingPrecinct)
    {
        std::cout << value.first << ": " << value.second << "\n";
    }

    std::cout << " =============== Crime within a radius ======================\n\n";

    const auto radius_km = 5;
    auto result = crimeDataAnalyzer.FindCrimesInRadius(38.8439, -76.9780, radius_km);

    std::cout << "The number of crime within " << radius_km  << " kilometers is: " << result.size()  <<"\n\n";

    return 0;
}