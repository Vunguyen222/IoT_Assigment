#include "shared_Attributes_Task.h"

constexpr std::array<const char *, 6U> SUBSCRIBED_SHARED_ATTRIBUTES = {FW_CHKS_KEY, FW_CHKS_ALGO_KEY, FW_SIZE_KEY, "fw_tag", FW_TITLE_KEY, FW_VER_KEY};
const Shared_Attribute_Callback callback(&processSharedAttributeUpdate, SUBSCRIBED_SHARED_ATTRIBUTES.cbegin(), SUBSCRIBED_SHARED_ATTRIBUTES.cend());
void shared_Attributes_Task(void *pvParameters)
{
    Serial.println("Shared Attributes Task started");
    while (true)
    {
        if (!subscribed && tb.connected())
        {
            Serial.println("Subscribing for shared attribute updates...");
            // Shared attributes we want to request from the server

            if (!tb.Shared_Attributes_Subscribe(callback))
            {
                Serial.println("Failed to subscribe for shared attribute updates");
            }
            else
            {
                Serial.println("Subscribe done");
                subscribed = true;
            }
        }

        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}