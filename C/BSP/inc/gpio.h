#ifndef GPIO_H
#define GPIO_H

#include "imx6ull.h"

/* 枚举类型和结构体定义 */
enum gpio_pin_direction
{
    kGPIO_DigitalInput = 0U, /* 输入 */
    kGPIO_DigitalOutput = 1U, /* 输出 */
};
enum _gpio_interrupt_mode
{
    kGPIO_NoIntmode = 0U, 				/* 无中断功能 */
    kGPIO_IntLowLevel = 1U, 			/* 低电平触发	*/
    kGPIO_IntHighLevel = 2U, 			/* 高电平触发 */
    kGPIO_IntRisingEdge = 3U, 			/* 上升沿触发	*/
    kGPIO_IntFallingEdge = 4U, 			/* 下降沿触发 */
    kGPIO_IntRisingOrFallingEdge = 5U, 	/* 上升沿和下降沿都触发 */
};

/* GPIO配置结构体 */
struct gpio_pin_config
{
    enum gpio_pin_direction direction; /* GPIO方向:输入还是输出 */
    uint8_t outputLogic; /* 如果是输出的话，默认输出电平 */
    enum _gpio_interrupt_mode interruptMode;	/* 中断方式 */
};


void gpioInit(GPIO_Type *base, uint8_t pin, struct gpio_pin_config *config);
uint8_t gpioPinRead(GPIO_Type *base, uint8_t pin);
void gpioPinWrite(GPIO_Type *base, uint8_t pin, uint8_t value);
void gpio_intconfig(GPIO_Type* base, uint8_t pin, enum _gpio_interrupt_mode pinInterruptMode);
void gpio_enableint(GPIO_Type* base, uint8_t pin);
void gpio_disableint(GPIO_Type* base, uint8_t pin);
void gpio_clearintflags(GPIO_Type* base, uint8_t pin);

#endif