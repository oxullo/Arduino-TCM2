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

#include "tcm2.h"

SPISettings TCM2::spiSettings(SPI_SPEED, MSBFIRST, SPI_MODE3);

TCM2::TCM2()
{
}

void TCM2::begin()
{
    SPI.begin();
    // pinMode(LED_PIN, OUTPUT);
    // digitalWrite(LED_PIN, HIGH);

    digitalWrite(SS_PIN, HIGH);
    pinMode(SS_PIN, OUTPUT);

    // Necessary to prepare the clock for a falling edge
    SPI.beginTransaction(spiSettings);
    SPI.endTransaction();

    // Serial.println("Waking up TCM");
    pinMode(TC_ENABLE_PIN, OUTPUT);
    digitalWrite(TC_ENABLE_PIN, LOW);
    delay(100);
    busyWait();

    // dumpLinesStates();
}

uint16_t TCM2::getDeviceInfo(char *buffer)
{
    return sendAndReadString(0x30, 0x01, 0x01, 0x00, (char *)buffer);
}

uint16_t TCM2::resetDataPointer()
{
    return sendCommand(0x20, 0x0d, 0x00);
}

uint16_t TCM2::uploadImageData(const char *buffer, uint8_t length)
{
    uint16_t rc = sendCommand(0x20, 0x01, 0x00, length, (uint8_t*)buffer);
    // ErrataSheet_rA, solution 1
    delayMicroseconds(1200);
    
    return rc;
}

uint16_t TCM2::displayUpdate()
{
    return sendCommand(0x24, 0x01, 0x00);
}

void TCM2::startTransmission()
{
    digitalWrite(SS_PIN, LOW);
    delayMicroseconds(SS_ASSERT_DELAY_US);
    SPI.beginTransaction(spiSettings);
}

void TCM2::endTransmission()
{
    SPI.endTransaction();
    delayMicroseconds(SS_DEASSERT_DELAY_US);
    digitalWrite(SS_PIN, HIGH);
}

void TCM2::busyWait()
{
    delayMicroseconds(BUSY_WAIT_DELAY_US);
    while(digitalRead(TC_BUSY_PIN) == LOW) {
        #ifdef DEBUG
        Serial.print(".");
        delay(10);
        #endif
    };
    delayMicroseconds(BUSY_RELEASE_DELAY_US);
}

uint16_t TCM2::sendCommand(uint8_t ins, uint8_t p1, uint8_t p2, uint8_t lc, uint8_t *data)
{
    #ifdef DEBUG
    Serial.print("INS=");
    Serial.print(ins, HEX);
    Serial.print(" P1=");
    Serial.print(p1, HEX);
    Serial.print(" P2=");
    Serial.print(p2, HEX);
    Serial.print(" Lc=");
    Serial.print(lc, HEX);
    Serial.print(": ");
    #endif

    startTransmission();
    SPI.transfer(ins);
    SPI.transfer(p1);
    SPI.transfer(p2);

    if (lc) {
        SPI.transfer(lc);
        SPI.transfer(data, lc);
    }
    endTransmission();
    busyWait();

    startTransmission();
    uint16_t rc = (SPI.transfer(0x00) << 8) | SPI.transfer(0x00);
    endTransmission();
    busyWait();

    #ifdef DEBUG
    if (rc != EP_SW_NORMAL_PROCESSING) {
        Serial.print(" ERR=");
        Serial.println(rc, HEX);
    } else {
        Serial.println("OK");
    }
    #endif

    return rc;
}

uint16_t TCM2::sendAndReadString(uint8_t ins, uint8_t p1, uint8_t p2, uint8_t le, char *buffer)
{
    startTransmission();
    SPI.transfer(ins);
    SPI.transfer(p1);
    SPI.transfer(p2);
    SPI.transfer(le);
    endTransmission();
    busyWait();

    startTransmission();

    char ch;
    uint8_t i=0;
    do {
        ch = SPI.transfer(0x00);
        buffer[i++] = ch;

        #ifdef DEBUG
        Serial.print("CH=");
        Serial.println(ch, HEX);
        #endif
    } while (ch);

    uint16_t rc = (SPI.transfer(0x00) << 8) | SPI.transfer(0x00);
    endTransmission();
    busyWait();

    return rc;
}

uint16_t TCM2::sendCommand(uint8_t ins, uint8_t p1, uint8_t p2)
{
    return sendCommand(ins, p1, p2, 0, NULL);
}

void TCM2::dumpLinesStates()
{
    Serial.print("SS=");
    Serial.print(digitalRead(SS_PIN));
    Serial.print(" TC_ENA=");
    Serial.print(digitalRead(TC_ENABLE_PIN));
    Serial.print(" TC_BUSY=");
    Serial.print(digitalRead(TC_BUSY_PIN));
    Serial.print(" CLK=");
    Serial.print(digitalRead(13));
    Serial.print(" MISO=");
    Serial.print(digitalRead(11));
    Serial.print(" MOSI=");
    Serial.println(digitalRead(12));
}
