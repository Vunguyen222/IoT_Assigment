#ifndef WIFI_TASK_H
#define WIFI_TASK_H
#include <Arduino.h>
#include <WiFi.h>

extern WiFiClient wifiClient;
void wifiTask(void *pvParameters);

#endif