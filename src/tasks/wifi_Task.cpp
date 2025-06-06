#include "wifi_Task.h"

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
    while (1)
    {
        if (!reconnect())
        {
            vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for 1 second before retrying
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // Check every second
    }
}