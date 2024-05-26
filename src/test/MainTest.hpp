#include <iostream>
#include <LogClient/LogClient.hpp>
#include <gtest/gtest.h>
#include <filesystem>
#include "json/json.h"
#include <map>

using namespace std;
using namespace LogClient;

#define LOGSERVER_URL "https://enthusiastic-crow-kilt.cyclic.app/"

Client client;
//Json::Value data;
//data["title"] = "Hello";

class LogClientTest : public ::testing::Test
{
public:
//    LogClientTest()
//    {
//    }
};