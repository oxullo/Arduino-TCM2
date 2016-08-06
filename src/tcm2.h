/*
Weatherpod - WiFi E-ink weather widget
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

#ifndef TCM2_H
#define TCM2_H

#include <SPI.h>

#define SPI_SPEED           1E06

#define MAX_CHUNK_SIZE      0xfa
#define SS_PIN              7
#define TC_BUSY_PIN         2
#define TC_ENABLE_PIN       3

// #define LED_PIN             6

#define SS_ASSERT_DELAY_US      10
#define SS_DEASSERT_DELAY_US    10
#define BUSY_WAIT_DELAY_US      50
#define BUSY_RELEASE_DELAY_US   10

#define EP_SW_NORMAL_PROCESSING             0x9000
#define EP_SW_WRONG_LENGTH                  0x6700
#define EP_FRAMEBUFFER_SLOT_NOT_AVAILABLE   0x6981
#define EP_SW_INVALID_LE                    0x6c00
#define EP_SW_WRONG_PARAMETERS_P1P2         0x6a00
#define EP_FRAMEBUFFER_SLOT_OVERRUN         0x6a84
#define EP_SW_INSTRUCTION_NOT_SUPPORTED     0x6d00
#define EP_SW_GENERAL_ERROR                 0x6f00


class TCM2 {
public:
    TCM2();

    void begin();
    uint16_t getDeviceInfo(char *buffer);
    uint16_t resetDataPointer();
    uint16_t uploadImageData(const char *buffer, uint8_t length);
    uint16_t displayUpdate();

private:
    static SPISettings spiSettings;
    
    void startTransmission();
    void endTransmission();
    void busyWait();
    uint16_t sendCommand(uint8_t ins, uint8_t p1, uint8_t p2, uint8_t lc, uint8_t *data);
    uint16_t sendAndReadString(uint8_t ins, uint8_t p1, uint8_t p2, uint8_t le, char *buffer);
    uint16_t sendCommand(uint8_t ins, uint8_t p1, uint8_t p2);
    void dumpLinesStates();
};

#endif