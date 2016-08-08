/*
TCM2lib - MPico TCS gen2 E-ink arduino driver
Copyright (C) 2016  OXullo Intersecans <x@brainrapers.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <TCM2.h>

#define TCM2_BUSY_PIN       2
#define TCM2_ENABLE_PIN     3

TCM2 tcm(TCM2_BUSY_PIN, TCM2_ENABLE_PIN);

char buffer[64];

void printDeviceInfo()
{
    TCM2Response res = tcm.getDeviceInfo(buffer);
    Serial.print("getDeviceInfo res=");
    Serial.print(res, HEX);
    Serial.print(" data=");
    Serial.println(buffer);
}

void printDeviceId()
{
    TCM2Response res = tcm.getDeviceId(buffer);
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
}

void printSystemInfo()
{
    TCM2Response res = tcm.getSystemInfo(buffer);
    Serial.print("getSystemInfo res=");
    Serial.print(res, HEX);
    Serial.print(" data=");
    Serial.println(buffer);
}

void printSystemVersionCode()
{
    TCM2Response res = tcm.getSystemVersionCode(buffer);
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
}

void printSensorData()
{
    TCM2Response res = tcm.getSensorData(buffer);
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
}

void printTemperature()
{
    float temperature;
    TCM2Response res = tcm.getTemperature(&temperature);
    Serial.print("getTemperature res=");
    Serial.print(res, HEX);
    Serial.print(" tempC=");
    Serial.println(temperature);
}

void printCurrentFbChecksum()
{
    uint16_t checksum;
    TCM2Response res = tcm.getChecksum(&checksum, TCM2_FRAMEBUFFER_SLOT_AUTO);
    Serial.print("getChecksum res=");
    Serial.print(res, HEX);
    Serial.print(" checksum=");
    Serial.println(checksum, HEX);
}

void setup()
{
    Serial.begin(115200);
    tcm.begin();

    printDeviceInfo();
    printDeviceId();
    printSystemInfo();
    printSystemVersionCode();
    printSensorData();
    printTemperature();
    printCurrentFbChecksum();
}

void loop()
{
}
