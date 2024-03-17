#include "LogClient.hpp"


size_t LogClient::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}

string LogClient::Client::getTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

int LogClient::Client::writeLog(basic_string<char, char_traits<char>, allocator<char>> log_text, const char *type)
{
    if (!filesystem::exists(logsDir))
    {
        filesystem::create_directory(logsDir);
    }
    fstream  file;
    file.open(logPath,ios::app,ios::binary);
    log_text = "[" + getTime() + "]::" + logInformation[type] + ":::" + log_text;
    file << log_text << "\n";
    file.close();
    cout << log_text << "11111" << endl;
    return 0;
}

int LogClient::Client::POST(const char* url,const Json::Value& data) {
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
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
            string LogText = "POST request failed." + (string)(curl_easy_strerror(res));
            writeLog(LogText,"Debug");
        }

        curl_easy_cleanup(curl);
        return res;
    }
    else {

        return 1;
    }
}

int LogClient::Client::GET(const char* url) {
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, "Content-Type: application/json"));
        curl_easy_setopt(curl, CURLOPT_FILETIME, 1L);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            string LogText = "GET request failed." + (string)(curl_easy_strerror(res));
            writeLog(LogText,"Debug");
        }
        curl_easy_cleanup(curl);
        return res;
    }
    else
    {
        return 1;
    }
}


//int main() {
//    Client client;
//    client.data["title"] = "Hello, world!";
//    client.sendRequest("POST");
////    LogClient::
//    client.sendRequest("GET");
//}