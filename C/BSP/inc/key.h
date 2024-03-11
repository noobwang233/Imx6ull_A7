#ifndef KEY_H
#define KEY_H

#include "imx6ull.h"

#define KEY_VALUE  ON
#define KEY_RELEASE OFF


void keyInit(void);
uint8_t keyRead(void);
void keyStateSet(uint8_t temp_state);
#endif