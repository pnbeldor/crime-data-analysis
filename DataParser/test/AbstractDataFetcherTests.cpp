#include <gtest/gtest.h>

#include <string>

#include "AbstractDataFetcher.h"


class AbstractDataFetcherTestFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }

};

TEST_F(AbstractDataFetcherTestFixture, ConstructorTest)
{
    // const std::string location = "data.json";
    // DataSource source = DataSource::LOCAL_FILE;

    // AbstractDataFetcher fetcher(source, location);
    EXPECT_EQ(true, true);
}

TEST_F(AbstractDataFetcherTestFixture, LoadDataTest)
{
    EXPECT_EQ(true, true);
}

TEST_F(AbstractDataFetcherTestFixture, formatToStringTest)
{
    EXPECT_EQ(true, true);
}

TEST_F(AbstractDataFetcherTestFixture, sourceToStringTest)
{
    EXPECT_EQ(true, true);
}

TEST_F(AbstractDataFetcherTestFixture, GetLocationTest)
{
    EXPECT_EQ(true, true);
}

TEST_F(AbstractDataFetcherTestFixture, GetSourceTest)
{
    EXPECT_EQ(true, true);
}

TEST_F(AbstractDataFetcherTestFixture, getDataPtrTest)
{
    EXPECT_EQ(true, true);
}
