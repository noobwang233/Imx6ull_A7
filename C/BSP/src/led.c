#include "led.h"
#include "gpio.h"
#include "imx6ull.h"

void ledInit(void)
{
    struct gpio_pin_config cfg;
    /* 1、初始化IO复用 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);

    /* 2、、配置GPIO1_IO03的IO属性 */
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X10B0);

    /* 3、初始化GPIO,GPIO1_IO03设置为输出*/
    /* 4、设置GPIO1_IO03输出低电平，打开LED0*/
    cfg.direction = kGPIO_DigitalOutput;
    cfg.outputLogic = 0u;
    gpioInit(GPIO1, 3u, &cfg);
}

void ledSwitch(uint8_t sw)
{
    gpioPinWrite(GPIO1, 3u, sw);
}