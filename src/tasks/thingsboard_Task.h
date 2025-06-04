#ifndef THINGSBOARD_TASK_H
#define THINGSBOARD_TASK_H

#include <ThingsBoard.h>
#include <Arduino_MQTT_Client.h>
#include <RPC_Callback.h>
#include <Shared_Attribute_Callback.h> 
#include "utils/servo.h"  
#include "wifi_Task.h"

constexpr char TOKEN[] = "69o42qcjtwnwdwnsgomy";
constexpr char THINGSBOARD_SERVER[] = "app.coreiot.io";
constexpr uint16_t THINGSBOARD_PORT = 1883U;
constexpr uint32_t MAX_MESSAGE_SIZE = 1024U;
constexpr uint32_t SERIAL_DEBUG_BAUD = 115200U;
constexpr int16_t telemetrySendInterval = 5000U;

extern Arduino_MQTT_Client mqttClient;
extern ThingsBoard tb;

extern bool attributesChanged;
extern bool ledState;  // LED status

void thingsBoardTask(void *pvParameters);

#endif
