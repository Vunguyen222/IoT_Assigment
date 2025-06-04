#ifndef GLOBAL_H
#define GLOBAL_H

#include <WString.h>
#include <Preferences.h>
#include <WiFi.h>
#include <MQUnifiedsensor.h>
#include <Arduino.h>

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

uint8_t initWifi();
uint8_t disconnectWifi();
uint8_t isExistWifi(const String ssid, const String password);

void saveWiFiToFlash(const String ssid, const String password);
void saveWiFiToArr(const String ssid, const String password);
uint8_t saveWiFiCredential(const String ssid, const String password);

void loadWiFisFromFlash();

void mq2Init();

#endif