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

/*

This example shows how to retrieve device information from the TCM2


Arduino Pro mini 3V3 8MHz <> MPico TCM2

2       -> /TC_BUSY
3       -> /TC_EN
10/SS   -> /TC_SS
11/MOSI -> TC_MOSI
12/MISO -> TC_MISO
13/SCK  -> TC_SCK
3.3V    -> VDDIN, VIN
GND     -> GND

Arduino MKR1000 <> MPico TCM2

2       -> /TC_BUSY
3       -> /TC_EN
7       -> /TC_SS
8/MOSI  -> TC_MOSI
9/SCK   -> TC_SCK
10/MISO -> TC_MISO
VCC     -> VDDIN, VIN
GND     -> GND

*/

#include <TCM2.h>

#define TCM2_BUSY_PIN       2
#define TCM2_ENABLE_PIN     3
// Uncomment the following if running a MKR1000
// #define TCM2_SPI_CS         7

#ifndef TCM2_SPI_CS
#define TCM2_SPI_CS         SS
#endif

TCM2 tcm(TCM2_BUSY_PIN, TCM2_ENABLE_PIN, TCM2_SPI_CS);

uint8_t buffer[64];


void printDeviceInfo()
{
    TCM2Response res = tcm.getDeviceInfo(buffer);
    Serial.print("getDeviceInfo res=");
    Serial.print(res, HEX);
    Serial.print(" data=");
    Serial.println((char *)buffer);
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
    Serial.println((char *)buffer);
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

    // Wait for the serial to be opened
    while(!Serial);

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
