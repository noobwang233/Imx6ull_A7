#ifndef LED_H
#define LED_H

#include "imx6ull.h"

// #define SW_MUX_GPIO1_IO03 *((volatile unsigned int *)0X020E0068)
// #define SW_PAD_GPIO1_IO03 *((volatile unsigned int *)0X020E02F4)

// #define GPIO1_DR *((volatile unsigned int *)0X0209C000)
// #define GPIO1_GDIR *((volatile unsigned int *)0X0209C004)
// #define GPIO1_PSR *((volatile unsigned int *)0X0209C008)
// #define GPIO1_ICR1 *((volatile unsigned int *)0X0209C00C)
// #define GPIO1_ICR2 *((volatile unsigned int *)0X0209C010)
// #define GPIO1_IMR *((volatile unsigned int *)0X0209C014)
// #define GPIO1_ISR *((volatile unsigned int *)0X0209C018)
// #define GPIO1_EDGE_SEL *((volatile unsigned int *)0X0209C01C)

#define LED_ON  1u
#define LED_OFF 0u


void ledInit(void);
void ledSwitch(uint8_t sw);

#endif