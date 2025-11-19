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
#include <string_view>

#include "DataFetchConfig.h"

#include "CrimeDataAnalyzer.h"
#include "JsonDataLoader.h"
#include "URLDataLoader.h"
#include "DataLoaderFactory.h"

#include "LocalFileDataLoader.h"

#include "simdjson/internal/tape_type.h"

#include "Utils.h"

using namespace simdjson;
using namespace simdjson::internal;



void debug_json_structure(const dom::element& element, const std::string& prefix = "", int depth = 0) {
    std::string indent(depth * 2, ' ');
    
    switch (element.type()) {
        case dom::element_type::OBJECT: {
            std::cout << indent << prefix << "OBJECT {" << std::endl;
            for (auto field : element.get_object()) {
                std::cout << indent << "  \"" << field.key << "\": ";
                debug_json_structure(field.value, "", depth + 1);
            }
            std::cout << indent << "}" << std::endl;
            break;
        }
        case dom::element_type::ARRAY: {
            std::cout << indent << prefix << "ARRAY [" << std::endl;
            size_t index = 0;
            for (auto elem : element.get_array()) {
                debug_json_structure(elem, "[" + std::to_string(index++) + "]: ", depth + 1);
            }
            std::cout << indent << "]" << std::endl;
            break;
        }
        case dom::element_type::STRING:
            std::cout << indent << prefix << "STRING: \"" << element.get_string().value() << "\"" << std::endl;
            break;
        case dom::element_type::INT64:
            std::cout << indent << prefix << "INT64: " << element.get_int64().value() << std::endl;
            break;
        case dom::element_type::UINT64:
            std::cout << indent << prefix << "UINT64: " << element.get_uint64().value() << std::endl;
            break;
        case dom::element_type::DOUBLE:
            std::cout << indent << prefix << "DOUBLE: " << element.get_double().value() << std::endl;
            break;
        case dom::element_type::BOOL:
            std::cout << indent << prefix << "BOOL: " << (element.get_bool().value() ? "true" : "false") << std::endl;
            break;
        case dom::element_type::NULL_VALUE:
            std::cout << indent << prefix << "NULL" << std::endl;
            break;
        default:
            std::cout << indent << prefix << "UNKNOWN" << std::endl;
            break;
    }
}

void Example() {
    std::string json_data = R"({"name": "Alice", "age": 30, "is_student": false, "grades": [90, 85, 92]})";

    simdjson::dom::parser parser;
    simdjson::dom::element doc;
    simdjson::error_code error = parser.parse(json_data).get(doc);

    if (error) {
        std::cerr << "Parsing error: " << error << std::endl;
    }

    // Accessing and printing data
    std::cout << "Name: " << std::string(doc["name"]) << std::endl;
    std::cout << "Age: " << (int64_t)doc["age"] << std::endl;
    std::cout << "Is Student: " << (bool)doc["is_student"] << std::endl;

    std::cout << "Grades: ";
    for (simdjson::dom::element grade_elem : doc["grades"]) {
        std::cout << (int64_t)grade_elem << " ";
    }
    std::cout << std::endl;
}

void print_all_keys(const simdjson::dom::element& element) {
    if (element.type() != simdjson::dom::element_type::OBJECT) {
        std::cout << "Root element is not an object" << std::endl;
        return;
    }
    
    simdjson::dom::object obj = element.get_object();
    for (auto field : obj) {
        std::cout << field.key << std::endl;
    }
}

void print_type(const dom::element& element) {
    switch (element.type()) {
        case dom::element_type::OBJECT: std::cout << "object"; break;
        case dom::element_type::ARRAY: std::cout << "array"; break;
        case dom::element_type::STRING: std::cout << "string"; break;
        case dom::element_type::INT64: std::cout << "integer"; break;
        case dom::element_type::UINT64: std::cout << "unsigned"; break;
        case dom::element_type::DOUBLE: std::cout << "double"; break;
        case dom::element_type::BOOL: std::cout << "boolean"; break;
        case dom::element_type::NULL_VALUE: std::cout << "null"; break;
        default: std::cout << "unknown"; break;
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::string resourcePath = RESOURCES_PATH;
    const std::string location1 = resourcePath + "/partialCrash_data.json";

    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8};
    auto processed_numbers = numbers
            | std::views::filter([](int n) {return n % 2 == 0;})
            | std::views::transform([](int n) { return n* 2;});

    for  (int i : processed_numbers)
        std::cout << i << "  ";

    std::cout << "\n========================================================\n";
    
    const std::string location2 = resourcePath + "/Motor_Vehicle_Collisions_-_Crashes.json";
    LocalFileDataLoader loader(location1);

    simdjson::dom::parser parser1;
    simdjson::dom::element doc = parser1.load(location1);

    //std::string jsonString = loader.FetchData();

    //std::cout << jsonString << "\n\n";

    // simdjson::dom::parser parser;
    // simdjson::dom::element doc;
    // simdjson::error_code error = parser.parse(jsonString).get(doc);

    // if (error) {
    //     std::cerr << "Error parsing JSON: " << error << std::endl;
    //     return 1;
    // }

    auto docData = doc["meta"]["view"]["columns"];

    std::cout << "Number of columns = " << docData.get_array().size() << "\n\n";

    std::vector<std::string> fieldName;

    for (const auto& data : docData)
    {
        fieldName.push_back(std::string(data["fieldName"].get_string().value()));
        std::cout << "column name = " << data["name"] << "   Field Name = " << data["fieldName"] << "  Type = " << data["dataTypeName"] <<"\n";
    }

    std::vector<std::vector<std::string>> dataValue(50, std::vector<std::string>(fieldName.size(), ""));

    auto numDataRows = doc["data"].get_array().size();
    std::cout << "Size doc[data]  = " << numDataRows << "\n\n";

    int j = 0;
    dataFeatureMap responseMap;
    Utils utils;

    for (const auto& val : doc["data"])
    {
        {
            simdjson::dom::array jsonArray = val.get_array();
            for (size_t s = 0; s < jsonArray.size(); s++)
            {
                //std::cout << fieldName[s] << " = " << val.at(s)  << "\t";
                responseMap[fieldName[s]].push_back(utils.ParseElement(val.at(s)));

                j++;
            }
        }
    }

    std::cout << "The size of the map is: " << responseMap.at("longitude").size() << "\n\n";

    std::cout << "responseMap  =================================================================================\n";
    for (size_t i = 0; i < numDataRows; i++)
    {
        for (const auto& [key, value] : responseMap)
        {
            std::cout << key << " = " << value[i] << " =>  ";
        }

        std::cout << "\n\n";
    }
    std::cout << "responseMap   ================================================================================================\n\n";
    //std::cout << "Parsed JSON:" << std::endl;
    //std::cout << doc["meta"]["view"] << std::endl; // Prints the entire parsed document

    for (const auto& name : fieldName)
    {
        std::cout << name << "\n";
    }

    std::variant<std::string, simdjson::dom::element> document = loader.FetchData2();

    if (std::holds_alternative<simdjson::dom::element>(document))
    {
        std::cout << "Data Parser Successfuly with simdjson. \n\n";

        auto value = std::get<simdjson::dom::element>(document);
        std::cout << value["meta"]["view"]["columns"] << std::endl; // Prints the entire parsed document


        print_all_keys(value["data"]);

        //simdjson::error_code error;
        std::string raw_json_output = simdjson::to_string(value);
        std::cout << raw_json_output << "\n\n";
    }
 
    //     debug_json_structure(value);
    //     // print_type(value);
    //     // std::cout << value << "\n";

    //     // print_all_keys(value);
    // }

    //         if (data.is_object())
    //         {
    //             simdjson::dom::object obj = data.get_object().value();

    //             for (auto field :: obj)
    //             {
    //                 std::cout << " key " << field.key().value() << "\n";
    //             }
    //         }

    //         // simdjson::dom::element res;
    //         // auto error = value["data"].get(res);
    //         // if (error)
    //         // {
    //         //     std::cout << "===================  " << error << "\n";
    //         // }
    //         // else
    //         // {
    //         //     std::cout << res << "\n";
    //         // }
    //     }
    // }

    /*
    auto start = std::chrono::steady_clock::now();
    DataConfig config;
    config.source = DataSource::LOCAL_FILE;
    config.format = DataFormat::JSON;

    //config.location = "/home/pnbeldor/Downloads/Crime_Incidents_in_the_Last_30_Days.geojson";
    config.location = "/home/pnbeldor/Downloads/Motor_Vehicle_Collisions_-_Crashes.json";
    
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
    */
    return 0;
}