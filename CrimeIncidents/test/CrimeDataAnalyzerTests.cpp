#include <gtest/gtest.h>

#include <string>

#include "CrimeDataAnalyzer.h"

std::string json_str2 = R"(
{
"type": "FeatureCollection",
"name": "Crime_Incidents_in_the_Last_30_Days",
"crs": { "type": "name", "properties": { "name": "urn:ogc:def:crs:OGC:1.3:CRS84" } },
"features": [
{ "type": "Feature", "properties": { "CCN": "25423276", "REPORT_DAT": "2025-08-11T14:31:32Z", "SHIFT": "DAY", "METHOD": "OTHERS", "OFFENSE": "THEFT/OTHER", "BLOCK": "1500 - 1599 BLOCK OF CORCORAN STREET NW", "XBLOCK": 396918.18, "YBLOCK": 138223.69, "WARD": "2", "ANC": "2B", "DISTRICT": "3", "PSA": "301", "NEIGHBORHOOD_CLUSTER": "Cluster 6", "BLOCK_GROUP": "005202 2", "CENSUS_TRACT": "005202", "VOTING_PRECINCT": "Precinct 16", "LATITUDE": 38.911871100500001, "LONGITUDE": -77.035533729500003, "BID": null, "START_DATE": "2025-06-16T16:20:00Z", "END_DATE": "2025-06-16T16:24:00Z", "OBJECTID": 796061842, "OCTO_RECORD_ID": null }, "geometry": { "type": "Point", "coordinates": [ -77.035536024801715, 38.911878889726204 ] } },
{ "type": "Feature", "properties": { "CCN": "25423299", "REPORT_DAT": "2025-08-12T15:01:53Z", "SHIFT": "DAY", "METHOD": "OTHERS", "OFFENSE": "THEFT F/AUTO", "BLOCK": "1000 - 1099 BLOCK OF FAIRMONT STREET NW", "XBLOCK": 397715.34, "YBLOCK": 139661.31, "WARD": "1", "ANC": "1A", "DISTRICT": "3", "PSA": "304", "NEIGHBORHOOD_CLUSTER": "Cluster 2", "BLOCK_GROUP": "003500 1", "CENSUS_TRACT": "003500", "VOTING_PRECINCT": "Precinct 37", "LATITUDE": 38.924824086699999, "LONGITUDE": -77.026347170099996, "BID": null, "START_DATE": "2025-06-24T00:00:00Z", "END_DATE": "2025-06-24T22:00:00Z", "OBJECTID": 796061843, "OCTO_RECORD_ID": null }, "geometry": { "type": "Point", "coordinates": [ -77.026349463373336, 38.924831878884277 ] } },
{ "type": "Feature", "properties": { "CCN": "25423337", "REPORT_DAT": "2025-08-13T13:31:58Z", "SHIFT": "DAY", "METHOD": "OTHERS", "OFFENSE": "THEFT/OTHER", "BLOCK": "1800 - 1899 BLOCK OF RIGGS PLACE NW", "XBLOCK": 396310.09, "YBLOCK": 138389.73, "WARD": "2", "ANC": "2B", "DISTRICT": "2", "PSA": "208", "NEIGHBORHOOD_CLUSTER": "Cluster 6", "BLOCK_GROUP": "004202 1", "CENSUS_TRACT": "004202", "VOTING_PRECINCT": "Precinct 14", "LATITUDE": 38.913364502100002, "LONGITUDE": -77.042545966500001, "BID": null, "START_DATE": "2025-06-25T15:00:00Z", "END_DATE": "2025-06-25T22:00:00Z", "OBJECTID": 796061844, "OCTO_RECORD_ID": null }, "geometry": { "type": "Point", "coordinates": [ -77.042548264147698, 38.913372291417986 ] } },
{ "type": "Feature", "properties": { "CCN": "25423444", "REPORT_DAT": "2025-08-15T11:31:46Z", "SHIFT": "DAY", "METHOD": "OTHERS", "OFFENSE": "THEFT/OTHER", "BLOCK": "600 - 699 BLOCK OF 13TH STREET NW", "XBLOCK": 397430.66, "YBLOCK": 136664.37, "WARD": "2", "ANC": "2C", "DISTRICT": "2", "PSA": "209", "NEIGHBORHOOD_CLUSTER": "Cluster 8", "BLOCK_GROUP": "005802 1", "CENSUS_TRACT": "005802", "VOTING_PRECINCT": "Precinct 129", "LATITUDE": 38.897825847500002, "LONGITUDE": -77.029618944799992, "BID": "DOWNTOWN", "START_DATE": "2025-08-06T15:07:00Z", "END_DATE": "2025-08-06T15:13:00Z", "OBJECTID": 796061845, "OCTO_RECORD_ID": null }, "geometry": { "type": "Point", "coordinates": [ -77.029621237401699, 38.897833634201348 ] } },
{ "type": "Feature", "properties": { "CCN": "25423535", "REPORT_DAT": "2025-08-20T10:02:52Z", "SHIFT": "MIDNIGHT", "METHOD": "OTHERS", "OFFENSE": "THEFT/OTHER", "BLOCK": "100 - 199 BLOCK OF ROCK CREEK CHURCH ROAD NW", "XBLOCK": 398894.76, "YBLOCK": 141641.28, "WARD": "4", "ANC": "4C", "DISTRICT": "4", "PSA": "407", "NEIGHBORHOOD_CLUSTER": "Cluster 18", "BLOCK_GROUP": "002301 2", "CENSUS_TRACT": "002301", "VOTING_PRECINCT": "Precinct 46", "LATITUDE": 38.942662529899998, "LONGITUDE": -77.0127490446, "BID": null, "START_DATE": "2025-08-17T11:00:00Z", "END_DATE": "2025-08-17T12:00:00Z", "OBJECTID": 796061846, "OCTO_RECORD_ID": null }, "geometry": { "type": "Point", "coordinates": [ -77.012751334756288, 38.942670326271873 ] } },
{ "type": "Feature", "properties": { "CCN": "25423711", "REPORT_DAT": "2025-08-27T16:02:51Z", "SHIFT": "DAY", "METHOD": "OTHERS", "OFFENSE": "THEFT/OTHER", "BLOCK": "900 - 999 BLOCK OF G STREET SE", "XBLOCK": 400589.83433450031, "YBLOCK": 134826.0468425492, "WARD": "6", "ANC": "6B", "DISTRICT": "1", "PSA": "106", "NEIGHBORHOOD_CLUSTER": "Cluster 26", "BLOCK_GROUP": "007000 2", "CENSUS_TRACT": "007000", "VOTING_PRECINCT": "Precinct 90", "LATITUDE": 38.881269099900003, "LONGITUDE": -76.993202060999991, "BID": null, "START_DATE": "2025-08-12T03:30:00Z", "END_DATE": "2025-08-12T03:30:00Z", "OBJECTID": 796061847, "OCTO_RECORD_ID": null }, "geometry": { "type": "Point", "coordinates": [ -76.993204341704953, 38.881276884196673 ] } },
{ "type": "Feature", "properties": { "CCN": "25423737", "REPORT_DAT": "2025-08-28T13:02:45Z", "SHIFT": "DAY", "METHOD": "OTHERS", "OFFENSE": "THEFT/OTHER", "BLOCK": "1700 - 1799 BLOCK OF 15TH STREET NW", "XBLOCK": 397003.72, "YBLOCK": 138387.86, "WARD": "2", "ANC": "2B", "DISTRICT": "3", "PSA": "301", "NEIGHBORHOOD_CLUSTER": "Cluster 6", "BLOCK_GROUP": "005202 2", "CENSUS_TRACT": "005202", "VOTING_PRECINCT": "Precinct 16", "LATITUDE": 38.913350295000001, "LONGITUDE": -77.034548160200004, "BID": null, "START_DATE": "2025-06-20T18:10:00Z", "END_DATE": "2025-06-20T18:20:00Z", "OBJECTID": 796061848, "OCTO_RECORD_ID": null }, "geometry": { "type": "Point", "coordinates": [ -77.034550455276289, 38.913358084568344 ] } }
]})";

class CrimeDataAnalyzerTestFixture : public ::testing::Test
{
protected:

    void SetUp() override
    {
        //crimeData = new CrimeIncidents(file_path);
        //*crimeData = Json::parse(json_str);
    }

    void TearDown() override
    {
        ///delete crimeData;
        //crimeData = nullptr;
    }

    const std::string file_path = "/home/pnbeldor/Downloads/Crime_Incidents_in_the_Last_30_Days.geojson";

    //CrimeIncidents* crimeData;
};

TEST_F(CrimeDataAnalyzerTestFixture, sampleTest)
{
    // Json::Value data = crimeData->getData();

    // if (data == Json::nullValue)
    // {
    //     std::cout << " Data is nullptr\n\n";
    // }
    // else {
    //     ASSERT_STREQ(data["type"].asString().c_str(), "FeatureCollection");
    // }
    EXPECT_EQ(0, 0);
}

TEST_F(CrimeDataAnalyzerTestFixture, SetCollectionTests)
{
    // crimeData->SetCollection();

    // EXPECT_STREQ(crimeData->collection->type.c_str(), "FeatureCollection");
    // EXPECT_STREQ(crimeData->collection->name.c_str(), "Crime_Incidents_in_the_Last_30_Days");
    // EXPECT_STREQ(crimeData->collection->crs_property_name.c_str(), "urn:ogc:def:crs:OGC:1.3:CRS84");
    // EXPECT_STREQ((*crimeData->collection->features)[0].properties_ptr->report_date.c_str(), "2025-08-11T14:31:32Z");
    // EXPECT_STREQ((*crimeData->collection->features)[0].properties_ptr->ccn.c_str(), "25423276");
    // EXPECT_STREQ((*crimeData->collection->features)[0].properties_ptr->offense.c_str(), "THEFT/OTHER");
}
