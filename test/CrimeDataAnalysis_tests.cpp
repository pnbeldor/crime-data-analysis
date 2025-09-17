#include <gtest/gtest.h>

#include <string>

class CrimeDataTestFixture : public ::testing::Test
{
protected:

    void SetUp() override
    {
        
    }

    void TearDown() override
    {

    }
};

TEST_F(CrimeDataTestFixture, sampleTest)
{
    EXPECT_EQ(0, 0);
}
