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

void eraseCurrentFramebuffer()
{
    TCM2Response res = tcm.imageEraseFrameBuffer();
    Serial.print("imageEraseFrameBuffer res=");
    Serial.println(res, HEX);
}

void uploadTestPattern()
{
    uint8_t testPattern[2] = {1, 34};
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
    uploadTestPattern();
    displayUpdate();
}

void loop()
{
}
