#include "readDHT20_Task.h"

#define SDA_PIN 21 // Chân SDA
#define SCL_PIN 22 // Chân SCL

#define DHT_PIN 4
#define DHT_TYPE DHT22

DHT dht22(DHT_PIN, DHT_TYPE);

void readDHT(void *pvParameters)
{
    // Wire.begin(SDA_PIN, SCL_PIN);
    // dht20.begin();
    // dht22.begin();
    while (1)
    {
        // dht22.read();
        float temperature = dht22.readTemperature();
        float humidity = dht22.readHumidity();
        Serial.println(temperature);
        Serial.println(humidity);
        if (tb.connected())
        {
            tb.sendTelemetryData("temperature", temperature);
            tb.sendTelemetryData("humidity", humidity);
        }
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}