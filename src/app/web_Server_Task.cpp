#include "web_Server_Task.h"

AsyncWebServer server(80);
volatile bool isWifiConnected = false;

void closeWebServer()
{
    Serial.println("Close web server");
    server.end();
}

void handleWiFiCredentials(AsyncWebServerRequest *request)
{
    if (request->hasParam("ssid", true) && request->hasParam("password", true))
    {
        currentSSID = request->getParam("ssid", true)->value();
        currentPassword = request->getParam("password", true)->value();

        Serial.println("Received SSID: " + currentSSID);
        Serial.println("Received Password: " + currentPassword);

        request->send(200, "text/html", "<h2>Connecting to WiFi...</h2>");
        // connect to wifi
        if (initWifi())
        {
            // success
            // check wifi exist or not
            if (!isExistWifi(currentSSID, currentPassword))
            {
                if (!saveWiFiCredential(currentSSID, currentPassword))
                {
                    request->send(403, "text/html", "<h2> Can not add more wifi </h2>");
                    // disconnect wifi
                    disconnectWifi();
                }
            }
            isWifiConnected = true;
        }
        else
        {
            // failed
            request->send(SPIFFS, "/index.html", "text/html");
        }
    }
    else
        request->send(SPIFFS, "/index.html", "text/html");
}

void openWebServer()
{
    Serial.println("Open web server");
    // spiffs use for saving file into flash mem
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    // Kiểm tra file
  if (SPIFFS.exists("/index.html")) {
    Serial.println("File exists!");
  } else {
    Serial.println("File does NOT exist.");
  }

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
}
