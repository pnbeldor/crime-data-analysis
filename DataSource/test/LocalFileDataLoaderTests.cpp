
#include <gtest/gtest.h>

#include <string>

#include "LocalFileDataLoader.h"

class LocalFileDataLoaderTestFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }

};

TEST_F(LocalFileDataLoaderTestFixture, ConstructorTest)
{
    EXPECT_EQ(true, true);
}
