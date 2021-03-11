#include "My595.h"

My595::My595(int clockPin, int dataPin, int latchPin)
{
    this->_clockPin = clockPin;
    this->_dataPin = dataPin;
    this->_latchPin = latchPin;

    begin();
}

void My595::begin(void)
{
    pinMode(_clockPin, OUTPUT);
    digitalWrite(_clockPin, LOW);

    pinMode(_dataPin, OUTPUT);
    digitalWrite(_dataPin, LOW);

    pinMode(_latchPin, OUTPUT);
    digitalWrite(_latchPin, HIGH);
}

void My595::shiftByte(uint8_t data)
{
    for (uint8_t bit = 0; bit < 8; bit++)
    {
        digitalWrite(_clockPin, LOW);
        // delay(1);

        if ((data & (1 << bit)) != 0)
        {
            digitalWrite(_dataPin, HIGH);
            delay(1);
        }
        else
        {
            digitalWrite(_dataPin, LOW);
            delay(1);
        }

        digitalWrite(_clockPin, HIGH);
        // delay(1);
    }
}

void My595::shiftOut(uint8_t data)
{
    digitalWrite(_latchPin, LOW);
    //delay(1);

    shiftByte(data);

    digitalWrite(_latchPin, HIGH);
    // delay(1);
}

void My595::shiftOutArray(uint8_t *dataBuffer, uint8_t numberOfByte)
{
    digitalWrite(_latchPin, LOW);
    //delay(1);

    for (uint8_t byte = 0; byte < numberOfByte; byte++)
    {
        shiftByte(dataBuffer[byte]);
        //delay(1);
    }

    digitalWrite(_latchPin, HIGH);
    //delay(1);
}