#include "global.h"

Preferences preferences;
String ssids[MAX_WIFI_CREDENT];
String passwords[MAX_WIFI_CREDENT];
String currentSSID = "";
String currentPassword = "";
int amountWifiCred = 0;
MQUnifiedsensor MQ2(BOARD, VOLTAGE_RESOLUTION, ADC_BIT_RESOLUTION, MQ2_PIN, TYPE);

uint8_t initWifi()
{
    WiFi.begin(currentSSID, currentPassword);
    uint8_t timeout = 3;
    while (WiFi.status() != WL_CONNECTED && timeout--)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        Serial.println("...");
    }
    if (timeout)
        Serial.println("Connected to " + currentSSID);
    return timeout;
}

uint8_t disconnectWifi()
{
    return WiFi.disconnect(true);
}

uint8_t isExistWifi(const String ssid, const String password)
{
    for (int i = 0; i < amountWifiCred; i++)
    {
        if (ssids[i] == ssid && passwords[i] == password)
        {
            return 1;
        }
    }
    return 0;
}

// use when user enter new wifi
void saveWiFiToFlash(const String ssid, const String password)
{
    preferences.begin("wifi", false);

    String ssidKey = "ssid" + String(amountWifiCred);
    String passKey = "pass" + String(amountWifiCred);

    preferences.putString(ssidKey.c_str(), ssid);
    preferences.putString(passKey.c_str(), password);

    preferences.end();
}

void saveWiFiToArr(const String ssid, const String password)
{
    ssids[amountWifiCred] = ssid;
    passwords[amountWifiCred] = password;
}

uint8_t saveWiFiCredential(const String ssid, const String password)
{
    if (amountWifiCred == MAX_WIFI_CREDENT)
    {
        Serial.println("Can not add more wifi");
        return 0;
    }
    saveWiFiToFlash(ssid, password);
    saveWiFiToArr(ssid, password);

    amountWifiCred++;
    preferences.begin("amountWifiCred", false);
    preferences.putInt("count", amountWifiCred);
    preferences.end();
    return 1;
}

// use when system want to automatically connect to the wifi
void loadWiFisFromFlash()
{
    preferences.begin("amountWifiCred", true);
    amountWifiCred = preferences.getInt("count");
    preferences.end();
    if (!amountWifiCred)
        return;

    preferences.begin("wifi", true);
    String ssidKey, passKey;
    for (int i = 0; i < amountWifiCred; i++)
    {
        ssidKey = "ssid" + String(i);
        passKey = "pass" + String(i);
        ssids[i] = preferences.getString(ssidKey.c_str(), "");
        passwords[i] = preferences.getString(passKey.c_str(), "");
        // Serial.println(ssids[i]);
        // Serial.println(passwords[i]);
    }
    preferences.end();
}

void mq2Init()
{
    // set method
    MQ2.setRegressionMethod(1);
    MQ2.setA(574.25);
    MQ2.setB(-2.222);

    // init sensor
    MQ2.init();

    // calibration
    Serial.print("Calibrating please wait.");
    float calcR0 = 0;
    for (int i = 1; i <= 10; i++)
    {
        MQ2.update(); // Update data, the arduino will read the voltage from the analog pin
        calcR0 += MQ2.calibrate(RATIO_MQ2_CLEAN_AIR);
        Serial.print(".");
    }
    MQ2.setR0(calcR0 / 10);
    Serial.println("Done!.");

    if (isinf(calcR0))
    {
        Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply");
        while (1)
            ;
    }
    if (calcR0 == 0)
    {
        Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply");
        while (1)
            ;
    }
    Serial.println("Waiting 20s for MQ2 to stabilize");
    delay(20000);
    Serial.println("MQ2 is now stable");
}
