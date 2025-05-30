#include "web_Server_Task.h"

AsyncWebServer server(80);

void handleWiFiCredentials(AsyncWebServerRequest *request)
{
    String ssid, password;

    if (request->hasParam("ssid", true) && request->hasParam("password", true))
    {
        ssid = request->getParam("ssid", true)->value();
        password = request->getParam("password", true)->value();

        Serial.println("Received SSID: " + ssid);
        Serial.println("Received Password: " + password);

        // Gọi hàm kết nối WiFi hoặc lưu lại nếu muốn
        // connectToWiFi(ssid, password);
    }

    request->send(200, "text/html", "<h2>Đang kết nối WiFi...</h2>");
}

void webServerTask(void *pvParameters)
{
    // spiffs use for saving file into flash mem
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        vTaskDelete(NULL);
    }

    // if (SPIFFS.exists("/bootstrap.min.css"))
    // {
    //     Serial.println("index.html FOUND in SPIFFS!");
    // }
    // else
    // {
    //     Serial.println("index.html NOT FOUND in SPIFFS!");
    // }

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", "text/html"); });

    // Route to load style.css file
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", "text/css"); });

    // Route to load bootstrap
    server.on("/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/bootstrap.min.css", "text/css"); });

    // Captive Portal
    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->send(SPIFFS, "/index.html", "text/html"); });

    // save ssid and password.
    server.on("/save", HTTP_POST, handleWiFiCredentials);

    // Start server
    server.begin();
    Serial.println("[INFO] Web server started!");
    vTaskDelete(NULL);
}

void initWebServerTask()
{
    xTaskCreate(webServerTask, "webServerTask", 8192, NULL, 1, NULL);
}
