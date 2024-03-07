#ifndef CLK_H
#define CLK_H
#include "types.h"

struct clkConfig
{
    uint16_t core_clk;

};

void clkInit(void);
void clkEnable(void);

#endif