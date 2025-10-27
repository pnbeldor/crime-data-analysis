
#include <gtest/gtest.h>

#include <string>

#include "JsonDataLoader.h"

class JsonDataLoaderTestFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }

};

TEST_F(JsonDataLoaderTestFixture, ConstructorTest)
{
    const std::string location = "data.json";
    const DataSource source = DataSource::LOCAL_FILE;

    JsonDataLoader loader(source, location);
    EXPECT_TRUE((loader.GetLocation()).compare(location) == 0);
    EXPECT_EQ(loader.GetSource(), source);
}

TEST_F(JsonDataLoaderTestFixture, LoadDataTest)
{
    EXPECT_EQ(true, true);
}

TEST_F(JsonDataLoaderTestFixture, formatToStringTest)
{
    const std::string location = "data.json";
    const DataSource source = DataSource::LOCAL_FILE;
    JsonDataLoader loader(source, location);

    std::string format = loader.formatToString(DataFormat::JSON);
    EXPECT_EQ(format.compare("JSON"), 0);

    format = loader.formatToString(DataFormat::CSV);
    EXPECT_EQ(format.compare("CSV"), 0);

    format = loader.formatToString(DataFormat(4));
    EXPECT_EQ(format.compare("UNKNOWN"), 0);
}

TEST_F(JsonDataLoaderTestFixture, sourceToStringTest)
{
    auto loader = std::make_unique<JsonDataLoader>(DataSource::LOCAL_FILE, "");

    EXPECT_EQ((loader->sourceToString()).compare("LOCAL_FILE"), 0);

    loader = std::make_unique<JsonDataLoader>(DataSource::HTTP_REQUEST, "");

    EXPECT_EQ((loader->sourceToString()).compare("HTTP_REQUEST"), 0);

    loader = std::make_unique<JsonDataLoader>(DataSource(4), "");

    EXPECT_EQ((loader->sourceToString()).compare("UNKNOWN"), 0);
}

TEST_F(JsonDataLoaderTestFixture, GetLocationTest)
{
    EXPECT_EQ(true, true);
}

TEST_F(JsonDataLoaderTestFixture, GetSourceTest)
{
    auto loader = std::make_unique<JsonDataLoader>(DataSource::LOCAL_FILE, "");

    EXPECT_EQ(loader->GetSource(), DataSource::LOCAL_FILE);

    loader = std::make_unique<JsonDataLoader>(DataSource::HTTP_REQUEST, "");

    EXPECT_EQ(loader->GetSource(), DataSource::HTTP_REQUEST);

    //loader = std::make_unique<JsonDataLoader>(DataSource(4), "");

    //EXPECT_EQ(loader->GetSource(), DataSource::LOCAL_FILE);
}

TEST_F(JsonDataLoaderTestFixture, getDataPtrTest)
{
    EXPECT_EQ(true, true);
}

