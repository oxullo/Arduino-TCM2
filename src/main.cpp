
#include <Arduino.h>

#include "tcm2.h"

TCM2 tcm(2, 3, 10);

void setup()
{
    Serial.begin(115200);
    Serial.println("Good afternoon");

    tcm.begin();
    char buffer[64];

    uint16_t rc;

    rc = tcm.getDeviceInfo(buffer);
    Serial.print("getDeviceInfo rc=");
    Serial.print(rc, HEX);
    Serial.print(" data=");
    Serial.println(buffer);

    tcm.getDeviceId(buffer);
    Serial.print("getDeviceId rc=");
    Serial.print(rc, HEX);
    Serial.print(" bytes: ");
    for (uint8_t i=0 ; i < LE_GET_DEVICE_ID ; ++i) {
        Serial.print("[");
        Serial.print(i);
        Serial.print("]=");
        Serial.print(buffer[i] & 0xff, HEX);
        Serial.print(" ");
    }
    Serial.println();

    rc = tcm.getSystemInfo(buffer);
    Serial.print("getSystemInfo rc=");
    Serial.print(rc, HEX);
    Serial.print(" data=");
    Serial.println(buffer);

    tcm.getSystemVersionCode(buffer);
    Serial.print("getSystemVersionCode rc=");
    Serial.print(rc, HEX);
    Serial.print(" bytes: ");
    for (uint8_t i=0 ; i < LE_GET_SYSTEM_VERSION_CODE ; ++i) {
        Serial.print("[");
        Serial.print(i);
        Serial.print("]=");
        Serial.print(buffer[i] & 0xff, HEX);
        Serial.print(" ");
    }
    Serial.println();

}

void loop()
{

}
