#include "gpio.h"
#include "imx6ull.h"



void gpioInit(GPIO_Type *base, uint8_t pin, struct gpio_pin_config *config)
{
    if(config->direction == kGPIO_DigitalInput) /* 输入 */
    {
        base->GDIR &= ~( 1 << pin);
    }
    else /* 输出 */
    {
        base->GDIR |= 1 << pin;
        gpioPinWrite(base,pin, config->outputLogic);/* 默认输出电平 */
    }
}

uint8_t gpioPinRead(GPIO_Type *base, uint8_t pin)
{
    return (((base->DR) >> pin) & 0x1);
}


void gpioPinWrite(GPIO_Type *base, uint8_t pin, uint8_t value)
{
    if (value == 0U)
    {
        base->DR &= ~(1U << pin); /* 输出低电平 */
    }
    else
    {
        base->DR |= (1U << pin); /* 输出高电平 */
    }
}