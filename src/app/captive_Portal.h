#ifndef CAPTIVE_PORTAL_H
#define CAPTIVE_PORTAL_H

#include <DNSServer.h>
#include "utils/global.h"
#include "web_Server_Task.h"

extern DNSServer dns;
extern const char *ap_ssid;
extern const char *ap_pass;

void handleAccessPoint();

void turnOnAP();
void turnOffAP();
void processDNS(void *pvParameters);

#endif