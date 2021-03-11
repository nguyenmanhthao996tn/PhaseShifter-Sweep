#include "PhaseShiftChannel.h"

PhaseShiftChannel::PhaseShiftChannel(void)
{
    _reg595Left = new My595(REG595_CH1_SCK_PIN, REG595_CH1_DATA_PIN, REG595_CH1_RCK_PIN);
    _reg595Right = new My595(REG595_CH2_SCK_PIN, REG595_CH2_DATA_PIN, REG595_CH2_RCK_PIN);

    _dataPtrLeft = (PS_Channel_t *)_dataLeft;
    _dataPtrRight = (PS_Channel_t *)_dataRight;

    this->gpioInit();
    reg595Reset();
    begin();
}

void PhaseShiftChannel::gpioInit(void)
{
    pinMode(REG595_CLR_PIN, OUTPUT);
    digitalWrite(REG595_CLR_PIN, HIGH);
}

void PhaseShiftChannel::begin(void)
{
    // Set default value of channels to Tx mode, 0 deg
    setLED(0x00); // All OFF
    for (uint8_t i = 0; i < 8; i++)
    {
        setPhaseShiftAngle(i, Angle_D0); // 0 deg
        setSPDTSwitchDirection(i, SwitchToPA);
        setLNASwitchDirection(i, SwitchToPA);
    }

    update();
}

void PhaseShiftChannel::reg595Reset(void)
{
    digitalWrite(REG595_CLR_PIN, LOW);
    delay(50);
    digitalWrite(REG595_CLR_PIN, HIGH);
}

void PhaseShiftChannel::update(void)
{
    _reg595Left->shiftOutArray(_dataLeft, 4);
    _reg595Right->shiftOutArray(_dataRight, 4);
}

void PhaseShiftChannel::setLED(uint8_t ledNumber, Led_State_t state)
{
    if ((ledNumber > 3) && (ledNumber < 8))
    {
        ledNumber = 7 - ledNumber;
        _dataPtrRight[ledNumber].LED = ((state == Led_State_On) ? 0 : 1);
    }
    else
    {
        _dataPtrLeft[ledNumber].LED = ((state == Led_State_On) ? 0 : 1);
    }
}

void PhaseShiftChannel::setLED(uint8_t state)
{
    uint8_t tmp = state ^ 0xff;

    _dataPtrLeft[0].LED = (tmp & (1 << 7)) ? 1 : 0;
    _dataPtrLeft[1].LED = (tmp & (1 << 6)) ? 1 : 0;
    _dataPtrLeft[2].LED = (tmp & (1 << 5)) ? 1 : 0;
    _dataPtrLeft[3].LED = (tmp & (1 << 4)) ? 1 : 0;

    _dataPtrRight[3].LED = (tmp & (1 << 3)) ? 1 : 0;
    _dataPtrRight[2].LED = (tmp & (1 << 2)) ? 1 : 0;
    _dataPtrRight[1].LED = (tmp & (1 << 1)) ? 1 : 0;
    _dataPtrRight[0].LED = (tmp & 1) ? 1 : 0;
}

Led_State_t PhaseShiftChannel::getLED(uint8_t ledNumber)
{
    Led_State_t returnValue;
    if ((ledNumber > 3) && (ledNumber < 8))
    {
        ledNumber = 7 - ledNumber;
        returnValue = ((_dataPtrRight[ledNumber].LED == 0) ? Led_State_On : Led_State_Off);
    }
    else
    {
        returnValue = ((_dataPtrLeft[ledNumber].LED == 0) ? Led_State_On : Led_State_Off);
    }
}

uint8_t PhaseShiftChannel::getLED(void)
{
    uint8_t tmp = 0;

    tmp |= (_dataPtrLeft[0].LED << 7);
    tmp |= (_dataPtrLeft[1].LED << 6);
    tmp |= (_dataPtrLeft[2].LED << 5);
    tmp |= (_dataPtrLeft[3].LED << 4);

    tmp |= (_dataPtrRight[3].LED << 3);
    tmp |= (_dataPtrRight[2].LED << 2);
    tmp |= (_dataPtrRight[1].LED << 1);
    tmp |= _dataPtrRight[0].LED;

    tmp ^= 0xff;

    return tmp;
}

void PhaseShiftChannel::setPhaseShiftAngle(uint8_t channel, PhaseShiftAngle_t angle)
{
    PS_Channel_t *channelPtr;
    if ((channel > 3) && (channel < 8))
    {
        channel = 7 - channel;
        channelPtr = &_dataPtrRight[channel];
    }
    else
    {
        channelPtr = &_dataPtrRight[channel];
    }

    switch (angle)
    {
    case Angle_D0:
        channelPtr->D6 = 0;
        channelPtr->D5 = 0;
        channelPtr->D4 = 0;
        channelPtr->D3 = 0;
        break;
    case Angle_D22_5:
        channelPtr->D6 = 0;
        channelPtr->D5 = 0;
        channelPtr->D4 = 0;
        channelPtr->D3 = 1;
        break;
    case Angle_D45:
        channelPtr->D6 = 0;
        channelPtr->D5 = 0;
        channelPtr->D4 = 1;
        channelPtr->D3 = 0;
        break;
    case Angle_D90:
        channelPtr->D6 = 0;
        channelPtr->D5 = 1;
        channelPtr->D4 = 0;
        channelPtr->D3 = 0;
        break;
    case Angle_D180:
        channelPtr->D6 = 1;
        channelPtr->D5 = 0;
        channelPtr->D4 = 0;
        channelPtr->D3 = 0;
        break;
    case Angle_D337_5:
        channelPtr->D6 = 1;
        channelPtr->D5 = 1;
        channelPtr->D4 = 1;
        channelPtr->D3 = 1;
        break;
    default:
        break;
    }
}

void PhaseShiftChannel::getPhaseShiftAngle(uint8_t channel)
{
}

void PhaseShiftChannel::setSPDTSwitchDirection(uint8_t channel, SwitchDirection_t direction)
{
    PS_Channel_t *channelPtr;
    if ((channel > 3) && (channel < 8))
    {
        channel = 7 - channel;
        channelPtr = &_dataPtrRight[channel];
    }
    else
    {
        channelPtr = &_dataPtrRight[channel];
    }

    switch (direction)
    {
    case SwitchToPA:
        channelPtr->SW1_CTL1 = 1;
        channelPtr->SW1_CTL2 = 0;
        break;
    case SwitchToLNA:
        channelPtr->SW1_CTL1 = 0;
        channelPtr->SW1_CTL2 = 1;
        break;
    default:
        break;
    }
}

void PhaseShiftChannel::getSPDTSwitchDirection(uint8_t channel)
{
}

void PhaseShiftChannel::setLNASwitchDirection(uint8_t channel, SwitchDirection_t direction)
{
    PS_Channel_t *channelPtr;
    if ((channel > 3) && (channel < 8))
    {
        channel = 7 - channel;
        channelPtr = &_dataPtrRight[channel];
    }
    else
    {
        channelPtr = &_dataPtrRight[channel];
    }

    switch (direction)
    {
    case SwitchToPA:
        channelPtr->SW2_CTL = 0;
        break;
    case SwitchToLNA:
        channelPtr->SW2_CTL = 1;
        break;
    default:
        break;
    }
}

void PhaseShiftChannel::getLNASwitchDirection(uint8_t channel)
{
}
