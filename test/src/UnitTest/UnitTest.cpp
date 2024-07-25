#include <UnitTest/UnitTest.hpp>

TEST(UnitTest,PostRequest)
{
    int RESULT;
    Json::Value data;
    data["title"] = "Hello, world!";
    RESULT = client.POST(LOGSERVER_URL,data);
    EXPECT_EQ(RESULT,CURLE_OK);
}

TEST(UnitTest,GetRequest)
{
    int RESULT;
    RESULT = client.GET(LOGSERVER_URL);
    EXPECT_EQ(RESULT,CURLE_OK);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}