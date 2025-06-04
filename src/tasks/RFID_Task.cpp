#include "RFID_Task.h"


MFRC522 mfrc522(SS_PIN, RST_PIN);

void readRFIDTask(void *pvParameters)
{
    while (true)
    {
        // Serial.print("Enter readRFIDTask: \n");
        // Kiểm tra có thẻ mới không
        if (!mfrc522.PICC_IsNewCardPresent())
        {
            // Serial.println("No new card");
            vTaskDelay(500 / portTICK_PERIOD_MS);
            continue;
        }
        if (!mfrc522.PICC_ReadCardSerial())
        {
            Serial.println("Failed to read card");
            vTaskDelay(500 / portTICK_PERIOD_MS);
            continue;
        }

        // In UID ra serial
        // Serial.print("UID: ");
        // for (byte i = 0; i < mfrc522.uid.size; i++)
        // {
        //     Serial.printf("%02X ", mfrc522.uid.uidByte[i]);
        // }
        // Serial.println();
        if(tb.connected()){
            myServo.write(angle);
            tb.sendAttributeData("doorState", angle == 90);
            angle = (angle == 0) ? 90 : 0;
        }
        mfrc522.PICC_HaltA();                  // Dừng giao tiếp thẻ
        vTaskDelay(3000 / portTICK_PERIOD_MS); // Tránh đọc lặp quá nhanh
    }
}