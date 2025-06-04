#include "captive_Portal.h"
DNSServer dns;
const char *ap_ssid = "ESP32_AccessPoint";
const char *ap_pass = "12345678";

volatile bool stopDNS = false;

void turnOnAP()
{
    IPAddress apIP(192, 168, 4, 1);
    IPAddress subnetMask(255, 255, 255, 0);
    WiFi.softAPConfig(apIP, apIP, subnetMask);

    // start access point
    WiFi.softAP(ap_ssid, ap_pass);
    dns.start(53, "*", apIP);
    Serial.println("Access Point started");
}

void turnOffAP()
{
    WiFi.softAPdisconnect(true);
    Serial.println("Access Point end");
}

void handleAccessPoint()
{
    uint8_t i = 0;
    for (i; i < amountWifiCred; i++)
    {
        currentSSID = ssids[i];
        currentPassword = passwords[i];
        // access wifi here
        if (initWifi())
        {
            isWifiConnected = true;
            break;
        }
    }

    // if all wifis failed --> turn on accesspoint
    if (i == amountWifiCred)
    {
        turnOnAP();
        openWebServer();
        xTaskCreate(processDNS, "processDNS", 2048, NULL, 1, NULL);
    }
}

void processDNS(void *pvParameters)
{
    while (!stopDNS)
    {
        dns.processNextRequest();
        if (isWifiConnected)
        {
            closeWebServer();
            turnOffAP();
            stopDNS = true;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}