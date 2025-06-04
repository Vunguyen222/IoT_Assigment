#include "app/web_Server_Task.h"
#include "app/captive_Portal.h"
#include <WiFi.h>
#include "utils/global.h"
#include "tasks/gas_Detect_Task.h"

void setup()
{
    Serial.begin(115200);
    /* set pin mode for relay */
    pinMode(RELAY_PIN, OUTPUT);

    loadWiFisFromFlash();
    handleAccessPoint();
    mq2Init();
    xTaskCreate(readMQ2Sensor, "readMQ2Sensor", 4096, NULL, 1, NULL);
    // preferences.begin("wifi", false);
    // preferences.clear();
    // preferences.end();
    // preferences.begin("amountWifiCred", false);
    // preferences.clear();
    // preferences.end();
}

void loop()
{
}