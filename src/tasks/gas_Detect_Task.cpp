#include "gas_Detect_Task.h"

float upperThreshold = 5;
float lowerThreshold = 4;
float currentGasValue = 0;

bool turnOnRelay = false;

void readMQ2Sensor(void *pvParameters)
{
    while (true)
    {
        MQ2.update();
        currentGasValue = MQ2.readSensor();
        Serial.println(currentGasValue);
        if (currentGasValue > upperThreshold && !turnOnRelay)
        {
            Serial.println("Turn on Relay");
            turnOnRelay = true;
            digitalWrite(RELAY_PIN, HIGH);
        }

        if (currentGasValue <= lowerThreshold && turnOnRelay)
        {
            Serial.println("Turn off Relay");
            turnOnRelay = false;
            digitalWrite(RELAY_PIN, LOW);
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}