#include "exit.h"
#include "gpio.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "int.h"
#include "timer.h"

void exit_init(void)
{
	struct gpio_pin_config key_config;

	/* 1、设置IO复用 */
	IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18,0);			/* 复用为GPIO1_IO18 */
	IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0xF080);

	/* 2、初始化GPIO为中断模式 */
	key_config.direction = kGPIO_DigitalInput;
	key_config.interruptMode = kGPIO_IntFallingEdge;
	key_config.outputLogic = 1;
	gpioInit(GPIO1, 18, &key_config);

	GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);				/* 使能GIC中对应的中断 */
	system_register_irqhandler(GPIO1_Combined_16_31_IRQn, (system_irq_handler_t)gpio1_io18_irqhandler, NULL);	/* 注册中断服务函数 */
	gpio_enableint(GPIO1, 18);								/* 使能GPIO1_IO18的中断功能 */
}

void gpio1_io18_irqhandler(void)
{ 
	/*
	 *采用延时消抖，中断服务函数中禁止使用延时函数！因为中断服务需要
	 *快进快出！！这里为了演示所以采用了延时函数进行消抖，后面我们会讲解
	 *定时器中断消抖法！！！
 	 */

    filtertimer_restart(10);
	// delay(10);
	// if(gpioPinRead(GPIO1, 18) == 0)	/* 按键按下了  */
	// {
	// 	keyStateSet(!keyRead());
	// 	ledSwitch(keyRead());
	// }
	
	gpio_clearintflags(GPIO1, 18); /* 清除中断标志位 */
}
