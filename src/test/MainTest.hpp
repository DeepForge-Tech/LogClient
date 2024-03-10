#include <iostream>
#include "LogClient.hpp"
#include <gtest/gtest.h>
#include <filesystem>
#include <map>

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