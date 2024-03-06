#ifndef LED_H
#define LED_H

#include "imx6ull.h"

#define LED_ON  0u
#define LED_OFF 1u


void ledInit(void);
void ledSwitch(uint8_t sw);

#endif