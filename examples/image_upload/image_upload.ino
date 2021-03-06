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

This example shows how to upload a test image to a free framebuffer and display it
The bitmap can be generated using the tool epd_convert.py, located in the tools folder


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

#include "test_image.h"

#define TCM2_BUSY_PIN       2
#define TCM2_ENABLE_PIN     3
// Uncomment the following if running a MKR1000
// #define TCM2_SPI_CS         7

#ifndef TCM2_SPI_CS
#define TCM2_SPI_CS         SS
#endif

TCM2 tcm(TCM2_BUSY_PIN, TCM2_ENABLE_PIN, TCM2_SPI_CS);


void uploadTestImage()
{
    uint8_t buffer[TCM2_MAX_CHUNK_SIZE];
    uint8_t chunkSize;
    uint16_t offset = 0;

    while (offset < TOTAL_SIZE) {
        chunkSize = min(TOTAL_SIZE - offset, TCM2_MAX_CHUNK_SIZE);

        memcpy_P(buffer, &test_1bit[offset], chunkSize);

        TCM2Response res = tcm.uploadImageData(buffer, chunkSize);
        Serial.print("uploadImageData offs=");
        Serial.print(offset);
        Serial.print(" size=");
        Serial.print(chunkSize);
        Serial.print(" res=");
        Serial.println(res, HEX);

        offset += chunkSize;
    }
}

void displayUpdate()
{
    TCM2Response res = tcm.displayUpdate();
    Serial.print("displayUpdate res=");
    Serial.println(res, HEX);
}

void setup()
{
    Serial.begin(115200);
    tcm.begin();

    uploadTestImage();
    displayUpdate();
}

void loop()
{
}
