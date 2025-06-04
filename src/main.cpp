#include "./app/web_Server_Task.h"
#include <WiFi.h>
#include <DNSServer.h>
#include "tasks/RFID_Task.h"
#include "tasks/thingsboard_Task.h"
#include "utils/servo.h"
#include "tasks/wifi_Task.h"
// const char *ap_ssid = "ESP32_AccessPoint";
// const char *ap_pass = "12345678";
// DNSServer dns;

void setup()
{
    Serial.begin(115200);
    SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN);
    servoSetup();
    mfrc522.PCD_Init(); // Initialize the RFID reader
    Serial.println("RC522 init done");
    // Check version register to verify communication
    byte version = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
    if (version == 0x00 || version == 0xFF)
    {
        Serial.println("ERROR: MFRC522 not responding. Check wiring or power.");
    }
    else
    {
        Serial.print("MFRC522 detected, version: 0x");
        Serial.println(version, HEX);
    }
    // IPAddress apIP(192, 168, 4, 1);
    // IPAddress subnetMask(255, 255, 255, 0);
    // WiFi.softAPConfig(apIP, apIP, subnetMask);
    // WiFi.softAP(ap_ssid, ap_pass);
    // dns.start(53, "*", apIP);
    // Serial.println("Access Point started");
    // initWebServerTask();
    xTaskCreate( readRFIDTask, "RFID Reader", 4096, NULL, 3, NULL );
    xTaskCreate(wifiTask, "Wifi Task", 4096, NULL, 1, NULL);
    xTaskCreate(thingsBoardTask, "ThingsBoard Task", 8192, NULL, 1, NULL);
}

void loop()
{
    // dns.processNextRequest();
}