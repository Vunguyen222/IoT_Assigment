#include "app/web_Server_Task.h"
#include "app/captive_Portal.h"
#include "utils/global.h"
#include "utils/servo.h"
#include "tasks/gas_Detect_Task.h"
#include "tasks/RFID_Task.h"
#include "tasks/thingsboard_Task.h"
#include "tasks/wifi_Task.h"
#include "tasks/readDHT20_Task.h"

void setup()
{
    Serial.begin(115200);
    /* set pin mode for relay */
    pinMode(RELAY_PIN, OUTPUT);

    loadWiFisFromFlash();
    handleAccessPoint();
    while (!isWifiConnected)
    {
    }

    xTaskCreate(wifiTask, "Wifi Task", 4096, NULL, 1, NULL);
    xTaskCreate(thingsBoardTask, "ThingsBoard Task", 8192, NULL, 1, NULL);

    while (!tb.connected())
    {
    }
    readVersion();
    requestFirmwareUpdate();

    mq2Init();
    dht22.begin();

    SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN);
    servoSetup();
    mfrc522.PCD_Init();
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

    xTaskCreate(readRFIDTask, "RFID Reader", 4096, NULL, 1, NULL);
    xTaskCreate(readDHT, "read DHT", 2048, NULL, 1, NULL);
    xTaskCreate(readMQ2Sensor, "readMQ2Sensor", 4096, NULL, 1, NULL);

    // ota subscribe
    subscribeFirmwareUpdate();
}

void loop()
{
    tb.loop();
}