#include "MainTest.hpp"

TEST(LogClientTest, sendPostRequest)
{
    int RESULT;
    RESULT = client.sendRequest("POST");
    EXPECT_EQ(RESULT, CURLE_OK);
}

TEST(LogClientTest,sendGetRequest)
{
    int RESULT;
    RESULT = client.sendRequest("GET");
    EXPECT_EQ(RESULT,CURLE_OK);
}

TEST(LogClientTest,PostRequest)
{
    int RESULT;
    RESULT = client.POST();
    EXPECT_EQ(RESULT,CURLE_OK);
}

TEST(LogClientTest,GetRequest)
{
    int RESULT;
    RESULT = client.GET();
    EXPECT_EQ(RESULT,CURLE_OK);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}