
#ifndef WIFI_HTTP_H
#define WIFI_HTTP_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <map>
#include <string>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>

class WifiHttp
{
public:
    WifiHttp();
    void connectWifi(const char *ssid, const char *password);
    void testWifiConnection(const char *serverName);
    void testWifiConnection();
    void initServerConnection(const char *serverName);
    void sendGetRequest(const char *endpoint, const char *queryParams);
    String sendGetRequest(const char *endpoint, const char *queryParams, boolean withResponse);
    void sendPostRequest(const char *endpoint, const char *queryParams, JsonObject body);
    void sendPostRequest(const char *endpoint, const JsonObject body);
    char addRequestBody(const std::string &key, const std::string &value);
    // void beginConnection();
    // void sendGetRequest();
    // void sendPostRequest();
    // void sendPutRequest();
    // void sendDeleteRequest();
    // void sendPatchRequest();
    // void sendHeadRequest();
    // void sendOptionsRequest();
    // void sendTraceRequest();
    // void sendConnectRequest();
    // void sendRequest();
    // void sendRequest(String method);
    // void sendRequest(String method, String path);
    // void sendRequest(String method, String path, String body);
    // void sendRequest(String method, String path, String body, String headers);
    // void sendRequest(String method, String path, String body, String headers, String contentType);
    // void sendRequest(String method, String path, String body, String headers, String contentType, String accept);
    // void sendRequest(String method, String path, String body, String headers, String contentType, String accept, String authorization);
    // void sendRequest(String method, String path, String body, String headers, String contentType, String accept, String authorization, String host);
    // void sendRequest(String method, String path, String body, String headers, String contentType, String accept, String authorization, String host, String userAgent);
    // void sendRequest(String method, String path, String body, String headers, String contentType, String accept, String authorization, String host, String userAgent, String contentLength);
    // void sendRequest(String method, String path, String body, String headers, String contentType, String accept, String authorization, String host, String userAgent, String contentLength, String connection);
    // void sendRequest(String method, String path, String body, String headers, String contentType, String accept, String authorization, String host, String userAgent, String contentLength, String connection, String cookie);
    // void sendRequest(String method, String path, String body, String headers, String contentType, String accept, String authorization, String host, String userAgent, String contentLength, String connection, String cookie, String origin);
    // void sendRequest(String method, String path, String body, String headers, String contentType, String accept, String authorization, String host, String userAgent, String contentLength, String connection, String cookie, String origin, String referer);
    // void sendRequest(String method, String path, String body, String headers, String contentType, String accept, String authorization, String host, String userAgent, String contentLength, String connection, String cookie, String origin, String referer, String xRequestedWith);

private:
    const char *_ssid;
    const char *_password;
    const char *_serverName;
    JsonDocument _reqBody;
    std::unique_ptr<BearSSL::WiFiClientSecure> _client;
    std::string appendQueryParams(const std::string &url, const char *queryParams);
    std::string jsonToString(const JsonObject &json);
    JsonObject stringToJson(const std::string &json);
};

#endif