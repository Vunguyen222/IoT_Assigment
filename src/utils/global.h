#ifndef GLOBAL_H
#define GLOBAL_H

#include <WString.h>
#include <Preferences.h>
#include <WiFi.h>
#include <MQUnifiedsensor.h>
#include <Arduino.h>
#include <ThingsBoard.h>
#include <Arduino_MQTT_Client.h>
#include <Espressif_Updater.h>

#define MAX_WIFI_CREDENT 100

#define BOARD "ESP-32"
#define TYPE "MQ-2"
#define VOLTAGE_RESOLUTION 3.3
#define ADC_BIT_RESOLUTION 12
#define RATIO_MQ2_CLEAN_AIR 9.83
#define MQ2_PIN 34

#define RELAY_PIN 23

extern Preferences preferences;

extern String ssids[MAX_WIFI_CREDENT];
extern String passwords[MAX_WIFI_CREDENT];
extern String currentSSID;
extern String currentPassword;
extern int amountWifiCred;

extern MQUnifiedsensor MQ2;

extern TaskHandle_t mq2TaskHandle;
extern TaskHandle_t rfidTaskHandle;

// constexpr char TOKEN[] = "69o42qcjtwnwdwnsgomy";
constexpr char TOKEN[] = "7l23s5snln10k419oc0n";
constexpr char THINGSBOARD_SERVER[] = "app.coreiot.io";
constexpr uint16_t THINGSBOARD_PORT = 1883U;
constexpr uint32_t MAX_MESSAGE_SIZE = 1024U;
constexpr uint32_t SERIAL_DEBUG_BAUD = 115200U;
constexpr int16_t telemetrySendInterval = 5000U;

extern WiFiClient wifiClient;
extern Arduino_MQTT_Client mqttClient;
extern ThingsBoard tb;

extern const char CURRENT_FIRMWARE_TITLE[32];
extern char CURRENT_FIRMWARE_VERSION[32];
extern const uint8_t FIRMWARE_FAILURE_RETRIES;
extern const uint16_t FIRMWARE_PACKET_SIZE;

extern Espressif_Updater updater;

extern bool currentFWSent;
extern bool updateRequestSent;
extern bool updateSubscribeSent;
extern bool subscribed;
extern std::array<const char *, 1U> REQUESTED_SHARED_ATTRIBUTES;
extern const Attribute_Request_Callback sharedCallback;

uint8_t
initWifi();
uint8_t disconnectWifi();
uint8_t isExistWifi(const String ssid, const String password);

void saveWiFiToFlash(const String ssid, const String password);
void saveWiFiToArr(const String ssid, const String password);
uint8_t saveWiFiCredential(const String ssid, const String password);

void loadWiFisFromFlash();

void mq2Init();

void subscribeSharedAttributes();

void requestFirmwareUpdate();
void subscribeFirmwareUpdate();

void processSharedAttributeRequest(const Shared_Attribute_Data &data);
void processSharedAttributeUpdate(const Shared_Attribute_Data &data);

void progressCallback(const size_t &currentChunk, const size_t &totalChuncks);
void updatedCallback(const bool &success);

void readVersion();
void writeVersion();
#endif