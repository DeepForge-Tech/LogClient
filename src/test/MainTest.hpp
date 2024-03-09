#include <iostream>
#include "../LogClient.cpp"
#include <gtest/gtest.h>
#include <filesystem>
#include <map>
#include <gmock/gmock.h>
using namespace std;
using namespace LogClient;

Client client;

class LogClientTest : public ::testing::Test
{
public:
    LogClientTest()
    {
        client.data["title"] = "Hello, world!";
    }
};