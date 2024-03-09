#include <iostream>
#include <string>
#include "curl/curl.h"
#include "json/json.h"
#include <map>
#include <exception>

#define LOGSERVER_URL "https://enthusiastic-crow-kilt.cyclic.app/"

using namespace std;
using namespace Json;

namespace LogClient
{
    size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        ((string *) userp)->append((char *) contents, size * nmemb);
        return size * nmemb;
    }

    class Client {
    public:
        CURL *curl;
        CURLcode res;
        // string type
        string readBuffer;
        string GET_URL = "https://enthusiastic-crow-kilt.cyclic.app/";
        Value data;


        int sendRequest(string type);

        int POST();

        int GET();

        Client() {
//            curl_global_init(CURL_GLOBAL_DEFAULT);
            curl = curl_easy_init();
        }

    private:
        using funct_t = int (Client::*)(void);
        map<string, funct_t> Methods = {
                {"POST", &Client::POST},
                {"GET",  &Client::GET}};
    };

    Client client;
}