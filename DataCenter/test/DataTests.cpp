#include <gtest/gtest.h>

#include <string>

#include "Data.h"

std::string json_str = R"(
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

std::string csv_test_str =
"X,Y,CCN,REPORT_DAT,SHIFT,METHOD,OFFENSE,BLOCK,XBLOCK,YBLOCK,WARD,ANC,DISTRICT,PSA,NEIGHBORHOOD_CLUSTER,BLOCK_GROUP,CENSUS_TRACT,VOTING_PRECINCT,LATITUDE,LONGITUDE,BID,START_DATE,END_DATE,OBJECTID,OCTO_RECORD_ID\n"
"399994.039999999,139507.420000002,25157897,2025/10/17 01:48:02+00,EVENING,GUN,ASSAULT W/DANGEROUS WEAPON,400 - 499 BLOCK OF DOUGLAS STREET NE,399994.04,139507.42,5,5F,5,502,Cluster 21,009204 1,009204,Precinct 74,38.9234407665,-77.0000687306,,2025/10/16 21:48:00+00,2025/10/17 01:00:00+00,819041639\n"
"398186.039999999,137185.329999998,25142688,2025/09/18 13:22:28+00,DAY,OTHERS,THEFT/OTHER,600 - 699 BLOCK OF K STREET NW,398186.04,137185.33,6,6E,1,101,Cluster 8,004703 2,004703,Precinct 18,38.902520725,-77.0209124198,MOUNT VERNON TRIANGLE CID,2025/09/18 12:04:00+00,2025/09/18 12:06:00+00,819043188\n"
"398764.710000001,138304.289999999,25156942,2025/10/15 12:18:54+00,DAY,OTHERS,THEFT/OTHER,200 - 299 BLOCK OF R STREET NW,398764.71,138304.29,5,5E,3,308,Cluster 21,004600 2,004600,Precinct 19,38.9126017076,-77.0142431775,,2025/10/14 22:59:00+00,2025/10/15 00:40:00+00,819044422\n"
"397003.719999999,138387.859999999,25157435,2025/10/16 00:29:40+00,EVENING,OTHERS,THEFT/OTHER,1700 - 1799 BLOCK OF 15TH STREET NW,397003.72,138387.86,2,2B,3,301,Cluster 6,005202 2,005202,Precinct 16,38.913350295,-77.0345481602,,2025/10/16 00:23:00+00,2025/10/16 00:23:00+00,819044813,\n"
"401480.719099998,135648.0198,25157795,2025/10/17 02:37:19+00,EVENING,OTHERS,THEFT F/AUTO,1500 - 1599 BLOCK OF A STREET SE,401480.719135327,135648.019803312,7,7D,1,107,Cluster 26,006801 2,006801,Precinct 87,38.8886726976,-76.9829326943,,2025/10/16 17:30:00+00,2025/10/16 19:00:00+00,819044814,\n"
"402015.079999998,133625.379999999,25158393,2025/10/17 22:54:33+00,EVENING,OTHERS,THEFT/OTHER,1900 - 2099 BLOCK OF MINNESOTA AVENUE SE,402015.08,133625.38,8,8A,6,607,Cluster 34,007601 3,007601,Precinct 133,38.8704509059,-76.9767793876,,2025/10/17 22:50:00+00,2025/10/17 22:51:00+00,819044815,\n"
;

class DataTestFixture : public ::testing::Test
{
protected:

    void SetUp() override
    {
        data = new Data();
    }

    void TearDown() override
    {
        delete data;
        data = nullptr;
    }

    const std::string file_path = "/home/pnbeldor/Downloads/Crime_Incidents_in_the_Last_30_Days.geojson";

    Data* data;
};

TEST_F(DataTestFixture, ConstructorTest)
{
    EXPECT_TRUE(data != nullptr);
}

TEST_F(DataTestFixture, GetDataCollectionTest)
{
    DataCollection* collection = nullptr;

    EXPECT_TRUE(collection == nullptr);

    collection = data->GetDataCollection();
    EXPECT_TRUE(collection != nullptr);
}

TEST_F(DataTestFixture, SetDataCollectionWithJSONStringTest)
{
    ASSERT_TRUE(json_str.compare("") != 0);

    data->SetDataCollection(json_str, DataFormat::JSON);

    DataCollection& collection = data->GetCollectionPtr();

    EXPECT_EQ(collection.type.compare("FeatureCollection"), 0);
    EXPECT_EQ(collection.name.compare("Crime_Incidents_in_the_Last_30_Days"), 0);

    EXPECT_TRUE(collection.features != nullptr);
    EXPECT_TRUE((*collection.features)[0].properties_ptr != nullptr);
    EXPECT_TRUE(((*collection.features)[0].properties_ptr->ccn).compare("25423276") == 0);
    EXPECT_TRUE(((*collection.features)[0].properties_ptr->offense).compare("THEFT/OTHER") == 0);
    EXPECT_TRUE(((*collection.features)[0].properties_ptr->block).compare("1500 - 1599 BLOCK OF CORCORAN STREET NW") == 0);
    EXPECT_TRUE(((*collection.features)[0].properties_ptr->end_date).compare("2025-06-16T16:24:00Z") == 0);
    EXPECT_TRUE(((*collection.features)[0].properties_ptr->start_date).compare("2025-06-16T16:20:00Z") == 0);
    EXPECT_DOUBLE_EQ((*collection.features)[0].properties_ptr->latitude, 38.911871100500001);
    EXPECT_DOUBLE_EQ((*collection.features)[0].properties_ptr->longitude, -77.035533729500003);

}

TEST_F(DataTestFixture, SetDataCollectionWithCSVStringTest)
{
    data->SetDataCollection(csv_test_str, DataFormat::CSV);
    DataCollection& collection = data->GetCollectionPtr();

    EXPECT_TRUE(collection.features != nullptr);
    EXPECT_TRUE((*collection.features)[0].properties_ptr != nullptr);
    EXPECT_TRUE(((*collection.features)[0].properties_ptr->ccn).compare("25157897") == 0);
    EXPECT_TRUE(((*collection.features)[0].properties_ptr->offense).compare("ASSAULT W/DANGEROUS WEAPON") == 0);
    EXPECT_TRUE(((*collection.features)[0].properties_ptr->block).compare("400 - 499 BLOCK OF DOUGLAS STREET NE") == 0);
    EXPECT_TRUE(((*collection.features)[0].properties_ptr->end_date).compare("2025/10/17 01:00:00+00") == 0);
    EXPECT_TRUE(((*collection.features)[0].properties_ptr->start_date).compare("2025/10/16 21:48:00+00") == 0);
    EXPECT_DOUBLE_EQ((*collection.features)[0].properties_ptr->latitude, 38.9234407665);
    EXPECT_DOUBLE_EQ((*collection.features)[0].properties_ptr->longitude, -77.0000687306);
}

TEST_F(DataTestFixture, SetDataInvalidJsonDataTest)
{
    data->SetDataCollection(csv_test_str, DataFormat::JSON);

    DataCollection& collection = data->GetCollectionPtr();

    ASSERT_TRUE(collection.features != nullptr);
    EXPECT_TRUE((*collection.features).size() == 0);
}

TEST_F(DataTestFixture, SetDataInvalidCSVDataTest)
{
    data->SetDataCollection("", DataFormat::CSV);

    DataCollection& collection = data->GetCollectionPtr();

    ASSERT_TRUE(collection.features != nullptr);
    EXPECT_TRUE((*collection.features).size() == 0);
}

TEST_F(DataTestFixture, SetDataEmptyStringTest)
{
    data->SetDataCollection("", DataFormat::JSON);

    DataCollection& collection = data->GetCollectionPtr();

    ASSERT_TRUE(collection.features != nullptr);
    EXPECT_TRUE((*collection.features).size() == 0);

    data->SetDataCollection("", DataFormat::CSV);
    EXPECT_TRUE((*collection.features).size() == 0);
}
