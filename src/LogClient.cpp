#include "include/LogClient.hpp"

int LogClient::Client::POST() {
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, LOGSERVER_URL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        string dataStr = data.toStyledString();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dataStr.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, "Content-Type: application/json"));
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_FILETIME, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "POST request failed: " << curl_easy_strerror(res) << endl;
        }

        curl_easy_cleanup(curl);
        return res;
    }
    else {

        return 1;
    }
}

int LogClient::Client::GET() {
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, GET_URL.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, "Content-Type: application/json"));
        curl_easy_setopt(curl, CURLOPT_FILETIME, 1L);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "GET request failed: " << curl_easy_strerror(res) << endl;
        }
        curl_easy_cleanup(curl);
        return res;
    }
    else
    {
        return 1;
    }
}

int LogClient::Client::sendRequest(string type)
{
    try {
        int result = (client.*(Methods[type]))();
        return result;
    }
    catch (exception &error) {
        cerr << error.what() << '\n';
        return 1;
    }
}

//int main() {
//    LogClient::client.data["title"] = "Hello, world!";
//    LogClient::client.sendRequest("POST");
////    LogClient::
//    LogClient::client.sendRequest("GET");
//}