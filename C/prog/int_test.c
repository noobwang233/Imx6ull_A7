#include "key.h"
#include "led.h"
#include "clk.h"
#include "int.h"
#include "exit.h"

int main()
{
    // uint8_t ledState = LED_OFF;
    int_init(); /* 初始化中断(一定要最先调用！) */
    clkInit();  /* 初始化系统时钟 			*/
    clkEnable();/* 使能所有的时钟 			*/
    ledInit();  /* 初始化led 			*/
    keyInit();  /* 初始化key 			*/
    exit_init();/* 初始化按键中断			*/
    for(;;)
    {
        // if(keyRead() == KEY_VALUE)
        // {
        //     ledState = !ledState;
        //     ledSwitch(ledState);

        // }
    }

    return 0;
}