#ifndef WIFI_TASK_H
#define WIFI_TASK_H
#include "utils/global.h"

extern WiFiClient wifiClient;
void wifiTask(void *pvParameters);

#endif