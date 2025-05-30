#include "./app/web_Server_Task.h"
#include <WiFi.h>
#include <DNSServer.h>

const char *ap_ssid = "ESP32_AccessPoint";
const char *ap_pass = "12345678";
DNSServer dns;

void setup()
{
    Serial.begin(115200);
    IPAddress apIP(192, 168, 4, 1);
    IPAddress subnetMask(255, 255, 255, 0);
    WiFi.softAPConfig(apIP, apIP, subnetMask);
    WiFi.softAP(ap_ssid, ap_pass);
    dns.start(53, "*", apIP);

    Serial.println("Access Point started");
    initWebServerTask();
}

void loop()
{
    dns.processNextRequest();
}