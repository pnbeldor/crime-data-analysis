
#include <gtest/gtest.h>

#include <string>

#include "DataLoaderFactory.h"

class DataLoaderFactoryTestFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }

};

TEST_F(DataLoaderFactoryTestFixture, ConstructorTest)
{
    EXPECT_EQ(true, true);
}
