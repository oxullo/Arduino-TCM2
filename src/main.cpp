
#include <Arduino.h>

#include "tcm2.h"

TCM2 tcm(2, 3, 10);

void setup()
{
    Serial.begin(115200);
    Serial.println("Good afternoon");

    tcm.begin();
    char buffer[64];

    TCM2Response res;

    res = tcm.getDeviceInfo(buffer);
    Serial.print("getDeviceInfo res=");
    Serial.print(res, HEX);
    Serial.print(" data=");
    Serial.println(buffer);

    tcm.getDeviceId(buffer);
    Serial.print("getDeviceId res=");
    Serial.print(res, HEX);
    Serial.print(" bytes: ");
    for (uint8_t i=0 ; i < TCM2_LE_GET_DEVICE_ID ; ++i) {
        Serial.print("[");
        Serial.print(i);
        Serial.print("]=");
        Serial.print(buffer[i] & 0xff, HEX);
        Serial.print(" ");
    }
    Serial.println();

    res = tcm.getSystemInfo(buffer);
    Serial.print("getSystemInfo res=");
    Serial.print(res, HEX);
    Serial.print(" data=");
    Serial.println(buffer);

    tcm.getSystemVersionCode(buffer);
    Serial.print("getSystemVersionCode res=");
    Serial.print(res, HEX);
    Serial.print(" bytes: ");
    for (uint8_t i=0 ; i < TCM2_LE_GET_SYSTEM_VERSION_CODE ; ++i) {
        Serial.print("[");
        Serial.print(i);
        Serial.print("]=");
        Serial.print(buffer[i] & 0xff, HEX);
        Serial.print(" ");
    }
    Serial.println();

    tcm.getSensorData(buffer);
    Serial.print("getSensorData res=");
    Serial.print(res, HEX);
    Serial.print(" bytes: ");
    for (uint8_t i=0 ; i < TCM2_LE_GET_SENSOR_DATA ; ++i) {
        Serial.print("[");
        Serial.print(i);
        Serial.print("]=");
        Serial.print(buffer[i] & 0xff, HEX);
        Serial.print(" ");
    }
    Serial.println();

    float temperature;
    tcm.getTemperature(&temperature);
    Serial.print("getTemperature res=");
    Serial.print(res, HEX);
    Serial.print(" tempC=");
    Serial.println(temperature);
}

void loop()
{

}
