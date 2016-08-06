
#include <Arduino.h>

#include "tcm2.h"

TCM2 tcm(2, 3, 10);

void setup()
{
    Serial.begin(115200);
    Serial.println("Good afternoon");

    tcm.begin();
    char buffer[64];
    tcm.getDeviceInfo(buffer);

    Serial.println(buffer);
}

void loop()
{

}
