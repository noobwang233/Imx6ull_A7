#include "led.h"
#include "imx6ull.h"

void ledInit(void)
{
    /* 1、初始化IO复用 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);

    /* 2、、配置GPIO1_IO03的IO属性 */
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X10B0);

    /* 3、初始化GPIO,GPIO1_IO03设置为输出*/
    GPIO1->GDIR |= (1 << 3);

    /* 4、设置GPIO1_IO03输出低电平，打开LED0*/
    GPIO1->DR &= ~(1 << 3);
    // SW_MUX_GPIO1_IO03 = 0x5;
    // SW_PAD_GPIO1_IO03 = 0X10B0;
    // GPIO1_GDIR = 0X0000008;
    // GPIO1_DR = 0X0;
}

void ledSwitch(uint8_t sw)
{
    // switch (sw) 
    // {
    //     case LED_ON:
    //         GPIO1_DR &= ~(1<<3); /* 打开LED0 */
    //         break;
    //     case LED_OFF:
    //         GPIO1_DR |= (1<<3); /* 关闭LED0 */
    //         break;
    // }
    switch (sw) 
    {
        case LED_ON:
            GPIO1->DR &= ~(1<<3); /* 打开LED0 */
            break;
        case LED_OFF:
            GPIO1->DR |= (1<<3); /* 关闭LED0 */
            break;
    }
}