#include "key.h"
#include "led.h"
#include "clk.h"

int main()
{
    clkEnable();
    ledInit();
    keyInit();

    for(;;)
    {
        if(keyRead() == KEY_VALUE)
        {
            ledSwitch(LED_ON);
        }
        else 
        {
            ledSwitch(LED_OFF);
        }
    }

    return 0;
}