#include "MainTest.hpp"

//TEST(LogClientTest, sendPostRequest)
//{
//    int RESULT;
//    RESULT = client.sendRequest("POST",LOGSERVER_URL);
//    EXPECT_EQ(RESULT, CURLE_OK);
//}
//
//TEST(LogClientTest,sendGetRequest)
//{
//    int RESULT;
//    RESULT = client.sendRequest("GET","gfggfggfg");
//    EXPECT_EQ(RESULT,CURLE_OK);
//}

TEST(LogClientTest,PostRequest)
{
    int RESULT;
    Json::Value data;
    data["title"] = "Hello, world!";
    RESULT = client.POST(LOGSERVER_URL,data);
    EXPECT_EQ(RESULT,CURLE_OK);
}

TEST(LogClientTest,GetRequest)
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