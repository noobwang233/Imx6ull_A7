#ifndef KEY_H
#define KEY_H

#include "imx6ull.h"

#define KEY_VALUE  1u
#define KEY_RELEASE 0u


void keyInit(void);
uint8_t keyRead(void);

#endif