#ifndef __MY595_H__
#define __MY595_H__

#include <Arduino.h>

class My595
{
protected:
    int _clockPin, _dataPin, _latchPin;
    void shiftByte(uint8_t data);

public:
    My595(int clockPin, int dataPin, int latchPin);
    void begin(void);
    void shiftOut(uint8_t data);
    void shiftOutArray(uint8_t* dataBuffer, uint8_t numberOfByte);
};

#endif /* __MY595_H__ */
