#include "servo.h"

Servo myServo;
int angle = 0;
void servoSetup() {
  myServo.setPeriodHertz(50);  
  myServo.attach(SERVO_PIN, 500, 2400);  
}
void openDoor(){
  myServo.write(90);
}
void closeDoor(){
  myServo.write(0);
}