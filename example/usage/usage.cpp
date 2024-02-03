#include <Arduino.h>
#include <wifi_http.h>
// instantiate the WifiHttp class
WifiHttp client;

const char *ssid = "REPLACE_WITH_YOUR_SSID";
const char *password = "REPLACE_WITH";

const char *serverName = "YOUR_SERVER_ADDRESS_(INCLUDE_THE_PORT_IF_ANY)";

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    delay(1000);
    Serial.println("Starting...");

    // Connect to Wi-Fi
    client.connectWifi(ssid, password);
    client.testWifiConnection(serverName);
}

void loop
{
    if (WiFi.status() == WL_CONNECTED)
    {
        String res = client.sendGetRequest(endpoint, queryParameters, true); // the last bool param to return response string. if you dont need it just omit

        Serial.println(res);

        delay(5000);
    }
}