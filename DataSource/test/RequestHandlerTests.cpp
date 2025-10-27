
#include <gtest/gtest.h>

#include <string>

#include "RequestHandler.h"

class RequestHandlerTestFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }

};

TEST_F(RequestHandlerTestFixture, ConstructorTest)
{
    EXPECT_EQ(true, true);
}
