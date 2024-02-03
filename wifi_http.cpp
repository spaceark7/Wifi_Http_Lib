#include "wifi_http.h"

// Function Declarations

WifiHttp::WifiHttp()
{
    // Constructor
    // Serial.println("WifiHttp object created");
    _client = std::unique_ptr<BearSSL::WiFiClientSecure>(new BearSSL::WiFiClientSecure);
}

void WifiHttp::connectWifi(const char *ssid, const char *password)
{
    _ssid = ssid;
    _password = password;
    if (_ssid == NULL || _password == NULL)
    {
        Serial.println("SSID and Password are not defined");
        return;
    }
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to WiFi");
}

void WifiHttp::testWifiConnection(const char *serverName)
{
    _serverName = serverName;
    if (_serverName == NULL)
    {
        Serial.println("Server name is not defined");
        return;
    }
    _client->setInsecure();
    HTTPClient https;
    https.begin(*_client, _serverName);
    Serial.println("Testing WiFi connection ...");
    if (https.begin(*_client, _serverName))
    {
        uint16_t httpCode = https.GET();
        switch (httpCode)
        {
        case HTTP_CODE_OK:
            Serial.println("HTTP status code 200");
            break;
        case HTTP_CODE_BAD_REQUEST:
            Serial.println("HTTP status code 400");
            break;
        case HTTP_CODE_NOT_FOUND:
            Serial.println("HTTP status code 404");
            break;
        case HTTP_CODE_INTERNAL_SERVER_ERROR:
            Serial.println("HTTP status code 500");
            break;

        default:
            break;
        }
        Serial.println("Server is reachable");
    }
    else
    {
        Serial.println("WiFi connection failed");
    }
    https.end();
}
void WifiHttp::testWifiConnection()
{
    if (_serverName == NULL)
    {
        Serial.println("Server name is not defined");
        return;
    }
    _client->setInsecure();
    HTTPClient https;
    https.begin(*_client, _serverName);
    Serial.println("Testing WiFi connection ...");
    if (https.begin(*_client, _serverName))
    {
        uint16_t httpCode = https.GET();
        switch (httpCode)
        {
        case HTTP_CODE_OK:
            Serial.println("HTTP status code 200");
            break;
        case HTTP_CODE_BAD_REQUEST:
            Serial.println("HTTP status code 400");
            break;
        case HTTP_CODE_NOT_FOUND:
            Serial.println("HTTP status code 404");
            break;
        case HTTP_CODE_INTERNAL_SERVER_ERROR:
            Serial.println("HTTP status code 500");
            break;

        default:
            break;
        }
        Serial.println("Server is reachable");
    }
    else
    {
        Serial.println("WiFi connection failed");
    }
    https.end();
}

void WifiHttp::initServerConnection(const char *serverName)
{
    _serverName = serverName;
    if (_serverName == NULL)
    {
        Serial.println("Server name is not defined");
        return;
    }
    _client->setInsecure();
    HTTPClient https;
    https.begin(*_client, _serverName);
    Serial.println("Establishing Server connection ...");
    if (https.begin(*_client, _serverName))
    {
        uint16_t httpCode = https.GET();
        switch (httpCode)
        {
        case HTTP_CODE_OK:
            Serial.println("HTTP status code 200");
            break;
        case HTTP_CODE_BAD_REQUEST:
            Serial.println("HTTP status code 400");
            break;
        case HTTP_CODE_NOT_FOUND:
            Serial.println("HTTP status code 404");
            break;
        case HTTP_CODE_INTERNAL_SERVER_ERROR:
            Serial.println("HTTP status code 500");
            break;

        default:
            break;
        }
        Serial.println("Server is reachable");
    }
    else
    {
        Serial.println("WiFi connection failed");
    }
    https.end();
}

void WifiHttp::sendGetRequest(
    const char *endpoint, const char *queryParams)
{

    if (endpoint == NULL)
    {
        Serial.println("Endpoint is not defined. Exiting the function");
        // Exiting the function
        return;
    }

    _client->setInsecure();
    HTTPClient https;
    std::string url = std::string(_serverName) + endpoint;

    // Adding query parameters to the URL
    if (queryParams != NULL)
    {
        url = appendQueryParams(url.c_str(), queryParams);
    }

    // Begin the request
    https.begin(*_client, url.c_str());
    Serial.println("Sending GET request ...");

    // Send the request
    if (https.begin(*_client, _serverName))
    {
        uint16_t httpCode = https.GET();
        if (httpCode > 0)
        {
            String payload = https.getString();
            Serial.println(payload);
        }
        else
        {
            Serial.println("Error on HTTP request");
        }
    }
    else
    {
        Serial.println("Error on HTTP request");
    }
    https.end();
}

String WifiHttp::sendGetRequest(
    const char *endpoint, const char *queryParams, boolean withResponse = true)
{

    if (endpoint == NULL)
    {
        Serial.println("Endpoint is not defined. Exiting the function");
        // Exiting the function
        return String("Error: Endpoint is not defined");
    }

    _client->setInsecure();
    HTTPClient https;
    std::string url = std::string(_serverName) + endpoint;

    // Adding query parameters to the URL
    if (queryParams != NULL)
    {
        url = appendQueryParams(url.c_str(), queryParams);
    }

    // Begin the request
    https.begin(*_client, url.c_str());
    Serial.println("Sending GET request ...");

    // Send the request
    uint16_t httpCode = https.GET();
    if (httpCode > 0)
    {
        String payload = https.getString();
        Serial.println(payload);
        return payload.c_str();
    }
    else
    {
        Serial.println("Error on HTTP request");
        return String("Error: HTTP request failed").c_str();
    }
    https.end();
}
void WifiHttp::sendPostRequest(
    const char *endpoint, const char *queryParams, JsonObject body)
{
    if (endpoint == NULL)
    {
        Serial.println("Endpoint is not defined. Exiting the function");
        // Exiting the function
        return;
    }
    JsonDocument doc;
    _client->setInsecure();
    HTTPClient https;
    std::string url = std::string(_serverName) + endpoint;

    // Adding query parameters to the URL
    if (queryParams != NULL)
    {
        url = appendQueryParams(url.c_str(), queryParams);
    }

    // Begin the request
    https.begin(*_client, url.c_str());
    Serial.println("Sending POST request ...");

    // convert JsonObject to string
    std::string output = jsonToString(body);

    // Send the request
    if (https.begin(*_client, _serverName))
    {
        uint16_t httpCode = https.POST(output.c_str());
        if (httpCode > 0)
        {
            String payload = https.getString();
            Serial.println(payload);
        }
        else
        {
            Serial.println("Error on HTTP request");
        }
    }
    else
    {
        Serial.println("Error on HTTP request");
    }
    https.end();
}

void WifiHttp::sendPostRequest(
    const char *endpoint, const JsonObject body)
{
    if (endpoint == NULL)
    {
        Serial.println("Endpoint is not defined. Exiting the function");
        // Exiting the function
        return;
    }
    _client->setInsecure();
    HTTPClient https;
    std::string url = std::string(_serverName) + endpoint;

    // Begin the request
    https.begin(*_client, url.c_str());
    Serial.println("Sending POST request ...");

    // convert JsonObject to string
    std::string output = jsonToString(body);

    // Send the request
    if (https.begin(*_client, _serverName))
    {
        uint16_t httpCode = https.POST(output.c_str());
        if (httpCode > 0)
        {
            String payload = https.getString();
            Serial.println(payload);
        }
        else
        {
            Serial.println("Error on HTTP request");
        }
    }
    else
    {
        Serial.println("Error on HTTP request");
    }
    https.end();
}

char WifiHttp::addRequestBody(const std::string &key, const std::string &value)
{
    // JsonDocument reqBody;
    // reqBody[key] = value;
    // char output;
    // Serial.println("Request body: ");
    // Serial.println(output);
    // serializeJson(reqBody, output);
    return 'a';
}
/**
 * Helper funnctions
 */

std::string WifiHttp::appendQueryParams(const std::string &url, const char *queryParams)
{
    std::string urlWithParams = url;

    if (queryParams == NULL)
    {
        Serial.println("Query parameters are not defined");
        return urlWithParams;
    }

    Serial.println(("URL with query params: " + std::string(urlWithParams)).c_str());

    return urlWithParams;
};

std::string WifiHttp::jsonToString(const JsonObject &json)
{
    std::string output;
    serializeJson(json, output);
    return output;
}

JsonObject WifiHttp::stringToJson(const std::string &json)
{
    JsonObject output;
    deserializeJson(output, json);
    return output;
}
