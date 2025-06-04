#include "thingsboard_Task.h"

Arduino_MQTT_Client mqttClient(wifiClient);
ThingsBoard tb(mqttClient, MAX_MESSAGE_SIZE);

RPC_Response setDoorSwitchState(const RPC_Data &data) {
  Serial.println("Received Switch state");
  bool newState = data;
  Serial.print("Switch state change: ");
  Serial.println(newState);
  angle = newState ? 90 : 0;
  myServo.write(angle);
  tb.sendAttributeData("doorState", angle == 90);
  angle = (angle == 0) ? 90 : 0;
  return RPC_Response("setDoorSwitchValue", newState);
}

const std::array<RPC_Callback, 1U> callbacks = {
  RPC_Callback{"setDoorSwitchValue", setDoorSwitchState}
};

void thingsBoardTask(void *pvParameters) {
  while (true) {
    if (!tb.connected()) {
      Serial.println("Connecting to ThingsBoard...");
      if (!tb.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT)) {
        Serial.println("Failed to connect to ThingsBoard");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        continue;
      }
      Serial.println("Connected to ThingsBoard");
      Serial.println("Subscribing for RPC...");

      if (!tb.RPC_Subscribe(callbacks.cbegin(), callbacks.end()))
      {
        Serial.println("Failed to subscribe for RPC");
        vTaskDelay(pdMS_TO_TICKS(5000)); // Wait for 5 seconds before retrying
        continue;
      }
      Serial.println("Subscribed for RPC");
    }
    tb.loop();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}