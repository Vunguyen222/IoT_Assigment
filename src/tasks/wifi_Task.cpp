#include "wifi_Task.h"
constexpr char WIFI_SSID[] = "Không-Cho-Pass";
constexpr char WIFI_PASSWORD[] = "511aaabbbcccabc@<???###";
WiFiClient wifiClient;

bool reconnect()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        initWifi();
    }
    return WiFi.status() == WL_CONNECTED;
}
void wifiTask(void *pvParameters)
{
    Serial.println("Connecting to Wi-Fi...");
    while (1)
    {
        if (!reconnect())
        {
            vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for 1 second before retrying
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // Check every second
    }
}