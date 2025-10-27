
#include <gtest/gtest.h>

#include <string>

#include "CSVDataLoader.h"

class CSVDataLoaderTestFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }

};

TEST_F(CSVDataLoaderTestFixture, ConstructorTest)
{
    EXPECT_EQ(true, true);
}
