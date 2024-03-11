#include "timer.h"
#include "int.h"
#include "led.h"
#include "key.h"
#include "gpio.h"


//value : ms
void epit1_init(unsigned int frac, unsigned int value)
{
	EPIT1->CR = 0;	/* 先清零CR寄存器 */
	
	/*
     * CR寄存器:
     * bit25:24 01 时钟源选择Peripheral clock=66MHz
     * bit15:4  frac 分频值
     * bit3:	1  当计数器到0的话从LR重新加载数值
     * bit2:	1  比较中断使能
     * bit1:    1  初始计数值来源于LR寄存器值
     * bit0:    0  先关闭EPIT1
     */
	EPIT1->CR = (1<<24 | 1<<3 | 1<<2 | 1<<1);
	
	EPIT1->LR = value * 66000;	/* 倒计数值 */
	EPIT1->CMPR	= 0;	/* 比较寄存器，当计数器值和此寄存器值相等的话就会产生中断 */

	/* 使能GIC中对应的中断 			*/
	GIC_EnableIRQ(EPIT1_IRQn);

	/* 注册中断服务函数 			*/
	system_register_irqhandler(EPIT1_IRQn, (system_irq_handler_t)epit1_irqhandler, NULL);	
}

void filtertimer_stop(void)
{
	EPIT1->CR &= ~(1<<0);	/* 关闭定时器 */
}

/*
 * @description		: 重启定时器
 * @param - value	: 定时器EPIT计数值
 * @return 			: 无
 */
void filtertimer_restart(unsigned int value)
{
	EPIT1->CR &= ~(1<<0);	/* 先关闭定时器 */
	EPIT1->LR = value * 66000;	/* 倒计数值 */
	EPIT1->CR |= (1<<0);	/* 打开定时器 		*/
}
/*
 * @description			: EPIT中断处理函数
 * @param				: 无
 * @return 				: 无
 */
void epit1_irqhandler(void)
{ 
	static unsigned char state = 0;

	state = !state;
	if(EPIT1->SR & (1<<0)) 			/* 判断比较事件发生 */
	{
        filtertimer_stop();					/* 关闭定时器 				*/
        if(gpioPinRead(GPIO1, 18) != keyRead())	/* 按键改变  */
        {
        	keyStateSet(!keyRead());
        	ledSwitch(state);
        }
	}
	
	EPIT1->SR |= 1<<0; 				/* 清除中断标志位 */
}
