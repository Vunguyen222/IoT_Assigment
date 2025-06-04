#ifndef RFID_TASK_H
#define RFID_TASK_H
#include <SPI.h>
#include <MFRC522.h>
#include "thingsboard_Task.h"
#include <Arduino.h>
#include "utils/servo.h"
// Pin config
#define RST_PIN  22
#define SS_PIN   21
#define SCK_PIN  18
#define MISO_PIN 19
#define MOSI_PIN 23
extern MFRC522 mfrc522;
void readRFIDTask(void *pvParameters);
#endif
