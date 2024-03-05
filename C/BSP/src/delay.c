#include "imx6ull.h"
#include "delay.h"

void delay_short(volatile uint32_t n)
{
    while(n--){}
}

void delay(volatile uint32_t n)
{
    while(n--){
        delay_short(0x7ff);
    }
}