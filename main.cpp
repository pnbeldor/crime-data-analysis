/*
    Crime Prediction Dashboard: Forecast crime hotspots for resource allocation

    Seasonal Pattern Analysis: Identify recurring patterns for preventive measures

    Clearance Rate Optimization: Analyze factors affecting arrest rates

    Community Safety App: Real-time crime mapping and alerts

    Policy Impact Analysis: Measure effect of interventions on crime rates
*/

#include <chrono>
#include <iostream>
#include <ranges>

#include "DataFetchConfig.h"

#include "CrimeDataAnalyzer.h"
#include "JsonDataLoader.h"
#include "URLDataLoader.h"
#include "DataLoaderFactory.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{

    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8};
    auto processed_numbers = numbers
            | std::views::filter([](int n) {return n % 2 == 0;})
            | std::views::transform([](int n) { return n* 2;});

    for  (int i : processed_numbers)
        std::cout << i << "  ";

    std::cout << "\n========================================================\n";
    auto start = std::chrono::steady_clock::now();
    DataConfig config;
    config.source = DataSource::LOCAL_FILE;
    //config.format = DataFormat::JSON;

    //config.location = "/home/pnbeldor/Downloads/Crime_Incidents_in_the_Last_30_Days.geojson";
    
    config.format = DataFormat::CSV;
    config.location = "/home/pnbeldor/Downloads/Crime_Incidents_in_the_Last_30_Days.csv";
    //config.location = "/home/pnbeldor/Downloads/Motor_Vehicle_Collisions_-_Crashes.json";
    //config.location = "/home/pnbeldor/Downloads/Chicago_Public_Schools_-_School_Progress_Reports_SY2324.csv";
    //config.location = "/home/pnbeldor/Downloads/Chicago_Public_Schools_-_School_Progress_Reports_SY2324.json";
    CrimeDataAnalyzer crimeDataAnalyzer(config);

    //crimeDataAnalyzer.PrintCollection();

    std::string keyStr;
    std::cout << " =================== Crime By Type ==================\n\n";
    keyStr = "OFFENSE";
    auto resultByType = crimeDataAnalyzer.SortByValue(crimeDataAnalyzer.GetCrimesCountBy(keyStr).value());

    for (const auto& value : resultByType)
    {
        std::cout << value.second << ": " << value.first << "\n";
    }

    std::cout << " ================= Crime by Neighborhood cluster ====================\n\n";
    keyStr = "NEIGHBORHOOD_CLUSTER";
    auto resultByNeighborhood = crimeDataAnalyzer.SortByValue(crimeDataAnalyzer.GetCrimesCountBy(keyStr).value());

    for (const auto& value : resultByNeighborhood)
    {
        std::cout << value.second << ": " << value.first << "\n";
    }

    std::cout << " =============== Crime by District ======================\n\n";
    keyStr = "DISTRICT";
    if (auto resultByDistrict = crimeDataAnalyzer.GetCrimesCountBy(keyStr))
    {
        auto sortedResultByDistrict = crimeDataAnalyzer.SortByValue(resultByDistrict.value());
        
        for (const auto& value : sortedResultByDistrict)
        {
            std::cout << value.second << ": " << value.first << "\n";
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
        auto sortedResultByVotingPrecinct = crimeDataAnalyzer.SortByValue(resultByVotingPrecinct.value());
        for (const auto& value : sortedResultByVotingPrecinct)
        {
            std::cout << value.second << ": " << value.first << "\n";
        }
    }
    else
    {
        std::cerr << "Error: Key \"" << keyStr << "\" not found: ";
    }

    std::cout << " =============== Crime within a radius ======================\n\n";

    const auto radiusKm = 5;
    auto result = crimeDataAnalyzer.FindTotalCrimesInRadius(38.8439, -76.9780, radiusKm);

    std::cout << "The number of crime within " << radiusKm  << " kilometers is: " << result  << "\n\n";

    auto end = std::chrono::steady_clock::now();

    auto duration = end - start;

    auto milliseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);

    std::cout << " The time taken  to run the program is:  " << milliseconds.count() << " us\n";
    return 0;
}