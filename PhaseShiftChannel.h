#ifndef __PHASESHIFTCHANNEL_H__
#define __PHASESHIFTCHANNEL_H__

#include "Arduino.h"
#include "Hardware_Config.h"
#include "My595.h"

/*********** DataType  ***********/
typedef struct PS_Channel_struct
{
    uint8_t LED : 1;
    uint8_t SW2_CTL : 1;
    uint8_t SW1_CTL2 : 1;
    uint8_t SW1_CTL1 : 1;
    uint8_t D3 : 1;
    uint8_t D4 : 1;
    uint8_t D5 : 1;
    uint8_t D6 : 1;
} PS_Channel_t;

typedef enum
{
    Led_State_On = 0,
    Led_State_Off
} Led_State_t;

typedef enum
{
    Angle_D0 = 0,
    Angle_D22_5,
    Angle_D45,
    Angle_D90,
    Angle_D180,
    Angle_D337_5
} PhaseShiftAngle_t;

typedef enum
{
    SwitchToPA = 0,
    SwitchToLNA
} SwitchDirection_t;

class PhaseShiftChannel
{
protected:
    My595 *_reg595Left, *_reg595Right;
    PS_Channel_t *_dataPtrLeft, *_dataPtrRight;
    uint8_t _dataLeft[4], _dataRight[4];

    void gpioInit(void);

public:
    PhaseShiftChannel(void);
    void begin(void);
    void reg595Reset(void);
    void update(void);

    void setLED(uint8_t ledNumber, Led_State_t state);
    void setLED(uint8_t state);
    Led_State_t getLED(uint8_t ledNumber);
    uint8_t getLED(void);

    void setPhaseShiftAngle(uint8_t channel, PhaseShiftAngle_t angle);
    void getPhaseShiftAngle(uint8_t channel);

    void setSPDTSwitchDirection(uint8_t channel, SwitchDirection_t direction);
    void getSPDTSwitchDirection(uint8_t channel);

    void setLNASwitchDirection(uint8_t channel, SwitchDirection_t direction);
    void getLNASwitchDirection(uint8_t channel);
};

#endif /* __PHASESHIFTCHANNEL_H__ */
