
#include <gtest/gtest.h>

#include <string>

#include "URLDataLoader.h"

class URLDataLoaderTestFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }

};

TEST_F(URLDataLoaderTestFixture, ConstructorTest)
{
    EXPECT_EQ(true, true);
}
