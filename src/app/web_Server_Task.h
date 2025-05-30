#ifndef WEB_SERVER_TASK_H
#define WEB_SERVER_TASK_H

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

extern AsyncWebServer server;

void webServerTask(void *pvParameters);
void initWebServerTask();

#endif