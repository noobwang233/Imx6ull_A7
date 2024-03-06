#include "key.h"
#include "led.h"
#include "clk.h"
#include "delay.h"
#include <stdint.h>

int main()
{
    uint8_t ledval = LED_ON;
    clkEnable();
    ledInit();
    keyInit();

    for(;;)
    {
        if(keyRead() == KEY_VALUE)
        {
            ledSwitch(ledval);
            ledval = !ledval;
        }
    }

    return 0;
}