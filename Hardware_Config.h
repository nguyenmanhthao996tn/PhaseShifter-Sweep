#ifndef __HARDWARE_CONFIG_H__
#define __HARDWARE_CONFIG_H__

/*********** Project library ***********/
#include <Arduino.h>

/*********** 74HC595 Channel 1 Pins ***********/
#define REG595_CH1_DATA_PIN     8
#define REG595_CH1_SCK_PIN      6
#define REG595_CH1_RCK_PIN      A0

/*********** 74HC595 Channel 2 Pins ***********/
#define REG595_CH2_DATA_PIN     7
#define REG595_CH2_SCK_PIN      5
#define REG595_CH2_RCK_PIN      A1

/*********** 74HC595 Common Pins ***********/
#define REG595_CLR_PIN          9 // Active LOW

/*********** RGB Led - WS2812-2020 ***********/
#define RGB_DATA_IN_PIN         4

#endif /* __HARDWARE_CONFIG_H__ */
