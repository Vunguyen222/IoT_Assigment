#ifndef WEB_SERVER_TASK_H
#define WEB_SERVER_TASK_H

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "utils/global.h"

extern AsyncWebServer server;
extern volatile bool isWifiConnected;

void openWebServer();
void closeWebServer();

#endif