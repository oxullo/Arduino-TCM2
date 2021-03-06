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

This example shows how to use the uploadImageSetROI() method to define a Region of Interest
and then repeat a pattern inside.


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


void eraseCurrentFramebuffer()
{
    TCM2Response res = tcm.imageEraseFrameBuffer();
    Serial.print("imageEraseFrameBuffer res=");
    Serial.println(res, HEX);
}

void defineRegionOfInterest()
{
    TCM2Response res = tcm.uploadImageSetROI(80, 80, 200, 160);
    Serial.print("uploadImageSetROI TL(80, 80) -> BR(200, 160) res=");
    Serial.println(res, HEX);
}

void uploadTestPattern()
{
    uint8_t testPattern[2] = {1, 127};
    TCM2Response res = tcm.uploadImageFixVal(testPattern, 2);
    Serial.print("uploadImageFixVal res=");
    Serial.println(res, HEX);
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

    eraseCurrentFramebuffer();
    defineRegionOfInterest();
    uploadTestPattern();
    displayUpdate();
}

void loop()
{
}
