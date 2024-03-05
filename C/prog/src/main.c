#include "led.h"
#include "clk.h"
#include "delay.h"


int main()
{
    clk_enable();
    ledInit();

    for(;;)
    {
        ledSwitch(LED_OFF);
        delay(500);
        ledSwitch(LED_ON);
        delay(500);
    }
    return 0;
}