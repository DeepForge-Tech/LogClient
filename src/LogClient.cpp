#include <LogClient/LogClient.hpp>

size_t LogClient::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string LogClient::Client::getTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

int LogClient::Client::writeLog(std::string &log_text, const char *type)
{
    if (!std::filesystem::exists(logsDir))
    {
        std::filesystem::create_directory(logsDir);
    }
    std::fstream file(logPath, std::ios::app | std::ios::binary);
    log_text = "[" + getTime() + "]::" + logInformation[to_upper(type)] + ":::" + log_text;
    file << log_text << "\n";
    file.close();
    return 0;
}

int LogClient::Client::POST(const char *url, const Json::Value &data)
{
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        std::string dataStr = data.toStyledString();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dataStr.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, "Content-Type: application/json"));
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_FILETIME, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::string LogText = "POST request failed." + (std::string)(curl_easy_strerror(res));
            writeLog(LogText, "Debug");
        }

        curl_easy_cleanup(curl);
        return res;
    }
    else
    {

        return 1;
    }
}

int LogClient::Client::GET(const char *url)
{
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, "Content-Type: application/json"));
        curl_easy_setopt(curl, CURLOPT_FILETIME, 1L);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::string LogText = "GET request failed." + (std::string)(curl_easy_strerror(res));
            writeLog(LogText, "Debug");
        }
        curl_easy_cleanup(curl);
        return res;
    }
    else
    {
        return 1;
    }
}
std::string LogClient::Client::to_upper(std::string sentence)
{
    std::string new_sentence = "";
    for (int i = 0; i < sentence.length(); i++)
    {
        char ch = sentence[i];
        // cout << ch << endl;
        ch = toupper(ch);
        new_sentence += ch;
    }
    return new_sentence;
}

// int main() {
//     Client client;
//     client.data["title"] = "Hello, world!";
//     client.sendRequest("POST");
////    LogClient::
//    client.sendRequest("GET");
//}