/*
    Crime Prediction Dashboard: Forecast crime hotspots for resource allocation

    Seasonal Pattern Analysis: Identify recurring patterns for preventive measures

    Clearance Rate Optimization: Analyze factors affecting arrest rates

    Community Safety App: Real-time crime mapping and alerts

    Policy Impact Analysis: Measure effect of interventions on crime rates
*/

#include <iostream>

#include "CrimeDataAnalyzer.h"
#include "Data.h"
#include "JsonDataLoader.h"
#include "URLDataLoader.h"
#include "DataLoaderFactory.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    DataConfig config;
    config.source = DataSource::LOCAL_FILE;
    config.format = DataFormat::JSON;
    //    const std::string file_path = "/home/pnbeldor/Downloads/Crime_Incidents_in_the_Last_30_Days.geojson";

    config.location = "/home/pnbeldor/Downloads/Crime_Incidents_in_the_Last_30_Days.geojson";

    CrimeDataAnalyzer crimeDataAnalyzer(config);
    crimeDataAnalyzer.LoadAllData();

    Data& data = crimeDataAnalyzer.GetCrimeDataPtr();

    std::cout << "Type = " << data.collection_ptr->type <<"\n";
    std::cout << "Name = " << data.collection_ptr->name << "\n";
    std::cout << "crs type = " << data.collection_ptr->crs_type <<"\n";
    std::cout << "CRS Properties Name = " << data.collection_ptr->crs_property_name << "\n";

    std::cout << "\nThe first 50 crime data\n\n";
    for (auto i = 0; i < 5; i++) {
        data.printFeature((*(data.collection_ptr)->features)[i]);
    }

    std::cout << " =================== Crime By Type ==================\n\n";
    crimeDataAnalyzer.GetCrimesByType();

    std::cout << " ================= Crime by Neighborhood cluster ====================\n\n";
    crimeDataAnalyzer.GetCrimesByNeighborhoodCluster();

    std::cout << " =============== Crime by District ======================\n\n";
    crimeDataAnalyzer.GetCrimesByDistrict();

    std::cout << " =============== Crime by voting precinct ======================\n\n";
    crimeDataAnalyzer.GetCrimesByVotingPrecinct();

    std::cout << " =============== Crime within a radius ======================\n\n";

    crimeDataAnalyzer.FindCrimesInRadius(38.8439, -76.9780, 5);

    return 0;
}