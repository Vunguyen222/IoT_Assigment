#include "readDHT20_Task.h"


#include "DHT20.h"
#include "Wire.h"

#define SDA_PIN 21  // Chân SDA
#define SCL_PIN 22  // Chân SCL

DHT20 dht20;

void readDHT(void *pvParameters) {
 Wire.begin(SDA_PIN, SCL_PIN);
    dht20.begin();
    while (1) {
        dht20.read();
        float temperature = dht20.getTemperature();
        float humidity = dht20.getHumidity();
        Serial.print("Temperature: ");
        Serial.println(dht20.getTemperature());
        Serial.print("Humidity: ");
        Serial.println(dht20.getHumidity());
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }

}