#ifndef SERVO_H
#define SERVO_H
#include <Arduino.h>
#include <ESP32Servo.h>

#define SERVO_PIN 15
extern Servo myServo;
extern int angle;
void servoSetup();
void openDoor();
void closeDoor();

#endif
