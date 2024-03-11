#ifndef LED_H
#define LED_H

#include "imx6ull.h"

#define LED_ON  ON
#define LED_OFF OFF


void ledInit(void);
void ledSwitch(uint8_t sw);

#endif