#ifndef GPIO_H
#define GPIO_H

#include "imx6ull.h"
#include <stdint.h>

/* 枚举类型和结构体定义 */
enum gpio_pin_direction
{
    kGPIO_DigitalInput = 0U, /* 输入 */
    kGPIO_DigitalOutput = 1U, /* 输出 */
};


/* GPIO配置结构体 */
struct gpio_pin_config
{
    enum gpio_pin_direction direction; /* GPIO方向:输入还是输出 */
    uint8_t outputLogic; /* 如果是输出的话，默认输出电平 */
};


void gpioInit(GPIO_Type *base, uint8_t pin, struct gpio_pin_config *config);
uint8_t gpioPinRead(GPIO_Type *base, uint8_t pin);
void gpioPinWrite(GPIO_Type *base, uint8_t pin, uint8_t value);

#endif