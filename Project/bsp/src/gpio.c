#include "gpio.h"
#include "imx6ull.h"
#include <stdint.h>



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
    gpio_intconfig(base, pin, config->interruptMode);	/* 中断功能配置 */
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
void gpio_intconfig(GPIO_Type* base, uint8_t pin, enum _gpio_interrupt_mode pin_int_mode)
{
	volatile uint32_t *icr;
	uint32_t icrShift;

	icrShift = pin;
	
	base->EDGE_SEL &= ~(1U << pin);

	if(pin < 16) 	/* 低16位 */
	{
		icr = &(base->ICR1);
	}
	else			/* 高16位 */
	{
		icr = &(base->ICR2);
		icrShift -= 16;
	}
	switch(pin_int_mode)
	{
		case(kGPIO_IntLowLevel):
			*icr &= ~(3U << (2 * icrShift));
			break;
		case(kGPIO_IntHighLevel):
			*icr = (*icr & (~(3U << (2 * icrShift)))) | (1U << (2 * icrShift));
			break;
		case(kGPIO_IntRisingEdge):
			*icr = (*icr & (~(3U << (2 * icrShift)))) | (2U << (2 * icrShift));
			break;
		case(kGPIO_IntFallingEdge):
			*icr |= (3U << (2 * icrShift));
			break;
		case(kGPIO_IntRisingOrFallingEdge):
			base->EDGE_SEL |= (1U << pin);
			break;
		default:
			break;
	}
}


/*
 * @description  			: 使能GPIO的中断功能
 * @param - base 			: 要使能的IO所在的GPIO组。
 * @param - pin  			: 要使能的GPIO在组内的编号。
 * @return		 			: 无
 */
void gpio_enableint(GPIO_Type* base, uint8_t pin)
{ 
    base->IMR |= (1 << pin);
}

/*
 * @description  			: 禁止GPIO的中断功能
 * @param - base 			: 要禁止的IO所在的GPIO组。
 * @param - pin  			: 要禁止的GPIO在组内的编号。
 * @return		 			: 无
 */
void gpio_disableint(GPIO_Type* base, uint8_t pin)
{ 
    base->IMR &= ~(1 << pin);
}

/*
 * @description  			: 清除中断标志位(写1清除)
 * @param - base 			: 要清除的IO所在的GPIO组。
 * @param - pin  			: 要清除的GPIO掩码。
 * @return		 			: 无
 */
void gpio_clearintflags(GPIO_Type* base, uint8_t pin)
{
    base->ISR |= (1 << pin);
}
