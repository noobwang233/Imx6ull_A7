#include "led.h"
#include "clk.h"
#include "delay.h"


void main()
{
    clk_enable();
    ledInit();

    for(;;)
    {
        ledSwitch(LED_OFF);
        delay(500);
        ledSwitch(LED_ON);
    }
}