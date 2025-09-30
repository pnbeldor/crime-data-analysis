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

    CrimeDataAnalyzer crime_data(config);
    crime_data.LoadAllData();
    DataCollection* collection = crime_data.getCollection();

    std::cout << "Type = " << collection->type <<"\n";
    std::cout << "Name = " << collection->name << "\n";
    std::cout << "crs type = " << collection->crs_type <<"\n";
    std::cout << "CRS Properties Name = " << collection->crs_property_name << "\n";

    std::cout << "\nThe first 50 crime data\n\n";
    for (auto i = 0; i < 50; i++) {
        std::cout << "Report Date: " << (*collection->features)[i].properties.report_date << "\n";
        std::cout << "Offense: " << (*collection->features)[i].properties.offense << "\n";

        std::cout << "Method: " << (*collection->features)[i].properties.method << "\n";
        std::cout << "Neighborhood Cluster: " << (*collection->features)[i].properties.neighborHood_cluster << "\n";
        std::cout << "ANC: " << (*collection->features)[i].properties.anc << "\n";
        std::cout << "PSA: " << (*collection->features)[i].properties.psa << "\n";    
    }

    DataLoaderFactory factory;
    [[maybe_unused]] std::unique_ptr data = factory.CreateDataLoader(config);
    data->LoadData();


    config.source = DataSource::HTTP_REQUEST;
    config.format = DataFormat::CSV;

    [[maybe_unused]] std::unique_ptr data2 = factory.CreateDataLoader(config);
    data2->LoadData();
    
    std::cout << "Data analysis project\n\n";

    return 0;
}